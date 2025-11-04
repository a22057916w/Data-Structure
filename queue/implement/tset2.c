#define PACKET_HASH_SIZE 4096
#define DEST_HASH_SIZE 4096

typedef struct {
    int source;
    int destination;
    int timestamp;
} Packet;

typedef struct PacketSetNode {
    Packet packet;
    struct PacketSetNode* next;
} PacketSetNode;

typedef struct {
    PacketSetNode** table;
    int size;
} PacketSet;

unsigned int hashPacket(Packet* p, int mod) {
    unsigned int h = 17;
    h = h * 31 + p->source;
    h = h * 31 + p->destination;
    h = h * 31 + p->timestamp;
    return h % mod;
}

PacketSet* packetSetCreate(int size) {
    PacketSet* set = malloc(sizeof(PacketSet));
    set->size = size;
    set->table = calloc(size, sizeof(PacketSetNode*));
    return set;
}

bool packetSetContains(PacketSet* set, Packet* p) {
    unsigned int idx = hashPacket(p, set->size);
    PacketSetNode* node = set->table[idx];
    while (node) {
        if (node->packet.source == p->source &&
            node->packet.destination == p->destination &&
            node->packet.timestamp == p->timestamp)
            return true;
        node = node->next;
    }
    return false;
}

void packetSetAdd(PacketSet* set, Packet* p) {
    unsigned int idx = hashPacket(p, set->size);
    PacketSetNode* node = malloc(sizeof(PacketSetNode));
    node->packet = *p;
    node->next = set->table[idx];
    set->table[idx] = node;
}

void packetSetRemove(PacketSet* set, Packet* p) {
    unsigned int idx = hashPacket(p, set->size);
    PacketSetNode* node = set->table[idx];
    PacketSetNode* prev = NULL;
    while (node) {
        if (node->packet.source == p->source &&
            node->packet.destination == p->destination &&
            node->packet.timestamp == p->timestamp) {
            if (prev)
                prev->next = node->next;
            else
                set->table[idx] = node->next;
            free(node);
            return;
        }
        prev = node;
        node = node->next;
    }
}

void packetSetFree(PacketSet* set) {
    for (int i = 0; i < set->size; i++) {
        PacketSetNode* node = set->table[i];
        while (node) {
            PacketSetNode* tmp = node;
            node = node->next;
            free(tmp);
        }
    }
    free(set->table);
    free(set);
}

typedef struct Pair {
    int* timestamps;
    int size;
    int capacity;
    int head;
} Pair;

typedef struct DestNode {
    int destination;
    Pair pair;
    struct DestNode* next;
} DestNode;

typedef struct {
    int memoryLimit;
    int packetCount;
    Packet* queue;
    int head, tail;
    PacketSet* packetSet;
    DestNode** destTable;
} Router;

unsigned int hashDest(int destination) { return destination % DEST_HASH_SIZE; }

Pair* getPair(Router* obj, int destination) {
    unsigned int idx = hashDest(destination);
    DestNode* node = obj->destTable[idx];
    while (node) {
        if (node->destination == destination) return &node->pair;
        node = node->next;
    }
    node = malloc(sizeof(DestNode));
    node->destination = destination;
    node->pair.timestamps = NULL;
    node->pair.size = 0;
    node->pair.capacity = 0;
    node->pair.head = 0;
    node->next = obj->destTable[idx];
    obj->destTable[idx] = node;
    return &node->pair;
}

int lowerBound(int* nums, int size, int target, int left) {
    int right = size;
    while (left < right) {
        int mid = (left + right) / 2;
        if (nums[mid] >= target)
            right = mid;
        else
            left = mid + 1;
    }
    return right;
}

Router* routerCreate(int memoryLimit) {
    Router* obj = malloc(sizeof(Router));
    obj->memoryLimit = memoryLimit;
    obj->packetCount = 0;
    obj->queue = malloc(sizeof(Packet) * memoryLimit);
    obj->head = obj->tail = 0;
    obj->packetSet = packetSetCreate(PACKET_HASH_SIZE);
    obj->destTable = calloc(DEST_HASH_SIZE, sizeof(DestNode*));
    return obj;
}

int* routerForwardPacket(Router* obj, int* retSize) {
    *retSize = 0;
    if (obj->packetCount == 0) return NULL;

    Packet packet = obj->queue[obj->head];
    obj->head = (obj->head + 1) % obj->memoryLimit;
    obj->packetCount--;

    packetSetRemove(obj->packetSet, &packet);

    Pair* pair = getPair(obj, packet.destination);
    pair->head++;

    int* res = malloc(sizeof(int) * 3);
    res[0] = packet.source;
    res[1] = packet.destination;
    res[2] = packet.timestamp;
    *retSize = 3;
    return res;
}

bool routerAddPacket(Router* obj, int source, int destination, int timestamp) {
    Packet p = {source, destination, timestamp};

    if (packetSetContains(obj->packetSet, &p)) return false;

    if (obj->packetCount == obj->memoryLimit) {
        int retSize;
        routerForwardPacket(obj, &retSize);
    }

    obj->queue[obj->tail] = p;
    obj->tail = (obj->tail + 1) % obj->memoryLimit;
    obj->packetCount++;

    packetSetAdd(obj->packetSet, &p);

    Pair* pair = getPair(obj, destination);
    if (pair->size == pair->capacity) {
        pair->capacity = pair->capacity == 0 ? 4 : pair->capacity * 2;
        pair->timestamps =
            realloc(pair->timestamps, sizeof(int) * pair->capacity);
    }
    pair->timestamps[pair->size++] = timestamp;

    return true;
}

int routerGetCount(Router* obj, int destination, int startTime, int endTime) {
    Pair* pair = getPair(obj, destination);
    if (!pair || pair->size == 0) return 0;
    int left = lowerBound(pair->timestamps, pair->size, startTime, pair->head);
    int right =
        lowerBound(pair->timestamps, pair->size, endTime + 1, pair->head);
    return right - left;
}

void routerFree(Router* obj) {
    free(obj->queue);
    packetSetFree(obj->packetSet);
    for (int i = 0; i < DEST_HASH_SIZE; i++) {
        DestNode* node = obj->destTable[i];
        while (node) {
            free(node->pair.timestamps);
            DestNode* tmp = node;
            node = node->next;
            free(tmp);
        }
    }
    free(obj->destTable);
    free(obj);
}