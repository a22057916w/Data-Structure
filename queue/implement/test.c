// ========================= Hash Function =========================
// Common hash function for all tables (mod by tableSize)
static inline int hash(int key, int tableSize) {
    if (key < 0) key = -key;
    return key % tableSize;
}

// ========================= HashTable ==============================
// Used for duplicate checking (key = source)

typedef struct HashNode {
    int key;    // source
    int dest;
    int time;
    struct HashNode* next;
} HashNode;

typedef struct HashTable {
    HashNode** bucket;
    int tableSize;
} HashTable;

HashTable* hashTable_create(int memoryLimit) {
    HashTable* ht = malloc(sizeof(HashTable));
    ht->bucket = calloc(memoryLimit, sizeof(HashNode*));
    ht->tableSize = memoryLimit;
    return ht;
}

bool hashTable_is_duplicate(HashTable* ht, int key, int dest, int time) {
    int index = hash(key, ht->tableSize);
    HashNode* curr = ht->bucket[index];
    while (curr) {
        if (curr->key == key && curr->dest == dest && curr->time == time)
            return true;
        curr = curr->next;
    }
    return false;
}

bool hashTable_insert(HashTable* ht, int key, int dest, int time) {
    int index = hash(key, ht->tableSize);
    HashNode* newNode = malloc(sizeof(HashNode));
    newNode->key = key;
    newNode->dest = dest;
    newNode->time = time;
    newNode->next = ht->bucket[index];
    ht->bucket[index] = newNode;
    return true;
}

bool hashTable_delete(HashTable* ht, int key, int dest, int time) {
    int index = hash(key, ht->tableSize);
    HashNode* curr = ht->bucket[index];
    HashNode* prev = NULL;

    while (curr) {
        if (curr->key == key && curr->dest == dest && curr->time == time) {
            if (prev) prev->next = curr->next;
            else ht->bucket[index] = curr->next;
            free(curr);
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

void hashTable_free(HashTable* ht) {
    for (int i = 0; i < ht->tableSize; ++i) {
        HashNode* curr = ht->bucket[i];
        while (curr) {
            HashNode* next = curr->next;
            free(curr);
            curr = next;
        }
    }
    free(ht->bucket);
    free(ht);
}

// ========================= Queue ==============================
// Global FIFO buffer for packets

typedef struct QueueNode {
    int src;
    int dest;
    int time;
} QueueNode;

typedef struct Queue {
    QueueNode* data;
    int front, rear;
    int capacity, size;
} Queue;

Queue* queue_create(int memoryLimit) {
    Queue* q = malloc(sizeof(Queue));
    q->data = malloc(sizeof(QueueNode) * memoryLimit);
    q->front = 0;
    q->rear = -1;
    q->capacity = memoryLimit;
    q->size = 0;
    return q;
}

bool queue_is_empty(Queue* q) { return q->size == 0; }
bool queue_is_full(Queue* q) { return q->size == q->capacity; }

bool queue_enqueue(Queue* q, int src, int dest, int time) {
    if (queue_is_full(q)) return false;
    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = (QueueNode){src, dest, time};
    q->size++;
    return true;
}

QueueNode queue_dequeue(Queue* q) {
    if (queue_is_empty(q)) return (QueueNode){0};
    QueueNode packet = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return packet;
}

void queue_free(Queue* q) {
    free(q->data);
    free(q);
}

// ========================= Destination Table ==============================
// Stores timestamps per destination for fast range counting

typedef struct DestNode {
    int dest;
    int* times;
    int head;
    int count;
    int capacity;
    struct DestNode* next;
} DestNode;

typedef struct DestTable {
    DestNode** bucket;
    int tableSize;
    int maxPerDest;
} DestTable;

DestTable* destTable_create(int tableSize, int maxPerDest) {
    DestTable* t = malloc(sizeof(DestTable));
    t->bucket = calloc(tableSize, sizeof(DestNode*));
    t->tableSize = tableSize;
    t->maxPerDest = maxPerDest;
    return t;
}

static inline int timeAt(const DestNode* n, int i) {
    int idx = (n->head + i) % n->capacity;
    return n->times[idx];
}

DestNode* destTable_get(DestTable* t, int dest) {
    int index = hash(dest, t->tableSize);
    DestNode* curr = t->bucket[index];
    while (curr) {
        if (curr->dest == dest)
            return curr;
        curr = curr->next;
    }

    // Create new node
    DestNode* node = malloc(sizeof(DestNode));
    node->dest = dest;
    node->times = malloc(sizeof(int) * t->maxPerDest);
    node->head = 0;
    node->count = 0;
    node->capacity = t->maxPerDest;
    node->next = t->bucket[index];
    t->bucket[index] = node;
    return node;
}

void destTable_insert(DestTable* t, int dest, int time) {
    DestNode* n = destTable_get(t, dest);
    if (n->count < n->capacity)
        n->times[(n->head + n->count++) % n->capacity] = time;
    else {
        // Overwrite oldest if over capacity
        n->times[n->head] = time;
        n->head = (n->head + 1) % n->capacity;
    }
}

void destTable_delete(DestTable* t, int dest, int time) {
    DestNode* n = destTable_get(t, dest);
    if (n->count > 0 && n->times[n->head] == time) {
        n->head = (n->head + 1) % n->capacity;
        n->count--;
    }
}

// ======= Unified binary search + count =======
int destTable_count(DestTable* t, int dest, int start, int end) {
    DestNode* n = destTable_get(t, dest);
    if (!n || n->count == 0 || start > end)
        return 0;

    int l, r, m;

    // lower_bound
    l = 0;
    r = n->count;
    while (l < r) {
        m = (l + r) / 2;
        if (timeAt(n, m) < start)
            l = m + 1;
        else
            r = m;
    }
    int lb = l;

    // upper_bound_inclusive
    l = -1;
    r = n->count - 1;
    while (l < r) {
        m = (l + r + 1) / 2;
        if (timeAt(n, m) <= end)
            l = m;
        else
            r = m - 1;
    }
    int ub = l;

    if (lb > ub) return 0;
    return ub - lb + 1;
}

void destTable_free(DestTable* t) {
    for (int i = 0; i < t->tableSize; ++i) {
        DestNode* curr = t->bucket[i];
        while (curr) {
            DestNode* next = curr->next;
            free(curr->times);
            free(curr);
            curr = next;
        }
    }
    free(t->bucket);
    free(t);
}

// ========================= Router ==============================

typedef struct {
    HashTable* ht;
    DestTable* dt;
    Queue* q;
} Router;

Router* routerCreate(int memoryLimit) {
    Router* r = malloc(sizeof(Router));
    r->ht = hashTable_create(memoryLimit);
    r->dt = destTable_create(memoryLimit, memoryLimit);
    r->q  = queue_create(memoryLimit);
    return r;
}

bool routerAddPacket(Router* obj, int source, int destination, int timestamp) {
    if (hashTable_is_duplicate(obj->ht, source, destination, timestamp))
        return false;

    if (queue_is_full(obj->q)) {
        QueueNode old = queue_dequeue(obj->q);
        hashTable_delete(obj->ht, old.src, old.dest, old.time);
        destTable_delete(obj->dt, old.dest, old.time);
    }

    hashTable_insert(obj->ht, source, destination, timestamp);
    queue_enqueue(obj->q, source, destination, timestamp);
    destTable_insert(obj->dt, destination, timestamp);
    return true;
}

int* routerForwardPacket(Router* obj, int* retSize) {
    if (queue_is_empty(obj->q)) {
        *retSize = 0;
        return NULL;
    }

    QueueNode pkt = queue_dequeue(obj->q);
    hashTable_delete(obj->ht, pkt.src, pkt.dest, pkt.time);
    destTable_delete(obj->dt, pkt.dest, pkt.time);

    *retSize = 3;
    int* res = malloc(sizeof(int) * 3);
    res[0] = pkt.src;
    res[1] = pkt.dest;
    res[2] = pkt.time;
    return res;
}

int routerGetCount(Router* obj, int destination, int startTime, int endTime) {
    return destTable_count(obj->dt, destination, startTime, endTime);
}

void routerFree(Router* obj) {
    hashTable_free(obj->ht);
    destTable_free(obj->dt);
    queue_free(obj->q);
    free(obj);
}

/*
Example usage:
Router* obj = routerCreate(memoryLimit);
routerAddPacket(obj, 1, 3, 3);
routerAddPacket(obj, 4, 3, 5);
int count = routerGetCount(obj, 3, 2, 5);
routerFree(obj);
*/
