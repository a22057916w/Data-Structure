#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 2    // small size to force collisions

typedef struct Node {
    char* key;
    int value;
    struct Node* next;
} Node;

typedef struct HashTable HashTable;

typedef struct {
    void (*insert)(HashTable*, const char*, int);
    int (*get)(HashTable*, const char*);
    void (*delete)(HashTable*, const char*);
    void (*display)(HashTable*);
    void (*destroy)(HashTable*);
} HashTableMethods;

struct HashTable {
    Node* buckets[TABLE_SIZE];
    HashTableMethods* ops;
} ;



// djb2 hash function
unsigned int hash(const char* key) {
    unsigned long h = 5381;
    int c;
    while(c = *key++) 
        h = ((h << 5) + h) + c; // h * 32 + h + c
    return h % TABLE_SIZE;
}

void insert(HashTable* self, const char* key, int value) {
    unsigned int index = hash(key);
    Node* curr = self->buckets[index];

    // update existing key
    while(curr) {
        if(strcmp(curr->key, key) == 0) {
            curr->value = value; // update existing
            return;
        }
        curr = curr->next;
    }

    // insert new key as head
    Node* newNode = malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->value = value;
    newNode->next = self->buckets[index];
    self->buckets[index] = newNode;
}

int get(HashTable* self, const char* key) {
    unsigned int index = hash(key);
    Node* curr = self->buckets[index];

    while(curr) {
        if(strcmp(curr->key, key) == 0) {
            return curr->value; // found
        }
        curr = curr->next;
    }
    return -1; // not found
}

void delete(HashTable* self, const char* key) {
    unsigned int index = hash(key);
    Node* curr = self->buckets[index];
    Node* prev = NULL;

    while(curr) {
        if(strcmp(curr->key, key) == 0) {
            if(prev)
                prev->next = curr->next;
            else
                self->buckets[index] = curr->next;
            free(curr->key);
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    return;
}

void display(HashTable* self) {
    for(int i = 0; i < TABLE_SIZE; i++) {
        Node* curr = self->buckets[i];
        if(curr)
            printf("Bucket %d:\n", i);
        while(curr) {
            printf("Key: %s, Value: %d\n", curr->key, curr->value);
            curr = curr->next;
        }
    }
    return;
}

void destroy(HashTable* self) {
    for(int i = 0; i < TABLE_SIZE; i++) {
        Node* curr = self->buckets[i];
        while(curr) {
            Node* temp = curr;
            curr = curr->next;
            free(temp->key);
            free(temp);
        }
        free(self->ops);
        free(self);
    }
    return;
}

HashTable* createHashTable() {
    HashTable* ht = malloc(sizeof(HashTable));
    for(int i = 0; i < TABLE_SIZE; i++)
        ht->buckets[i] = NULL;
    ht->ops = malloc(sizeof(HashTableMethods));
    ht->ops->insert = insert;
    ht->ops->get = get;
    ht->ops->delete = delete;
    ht->ops->display = display;
    return ht;
}

int main() {
    HashTable* ht = createHashTable();

    ht->ops->insert(ht, "apple", 1);
    ht->ops->insert(ht, "banana", 2);
    ht->ops->insert(ht, "orange", 3);

    printf("apple: %d\n", ht->ops->get(ht, "apple"));
    printf("banana: %d\n", ht->ops->get(ht, "banana"));
    printf("orange: %d\n\n", ht->ops->get(ht, "orange"));

    ht->ops->display(ht);

    ht->ops->delete(ht, "orange");
    printf("\noragne after deletion: %d\n", ht->ops->get(ht, "orange"));
    ht->ops->display(ht);

    return 0;
}