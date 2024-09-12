#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int key;
    int value;
    struct ListNode *prev;
    struct ListNode *next;
} ListNode;

typedef struct {
    ListNode *head;
    ListNode *tail;
    int size;
} LRUList;

typedef struct {
    int *keys;        // Array of keys
    int *values;      // Array of values
    int capacity;     // Maximum capacity of cache
    LRUList *lruList; // LRU list
    // Assuming a simple hash size of capacity
    int hashSize;
    int *hashTable; // Hash table to store node pointers
} LRUCache;

LRUCache *lRUCacheCreate(int capacity) {
    if (capacity <= 0)
        return NULL;

    LRUCache *cache = (LRUCache *)malloc(sizeof(LRUCache));
    if (!cache)
        return NULL;

    cache->capacity = capacity;
    cache->hashSize = capacity;
    cache->keys = (int *)malloc(capacity * sizeof(int));
    cache->values = (int *)malloc(capacity * sizeof(int));
    cache->hashTable = (int *)calloc(capacity, sizeof(int));

    if (!cache->keys || !cache->values || !cache->hashTable) {
        free(cache->keys);
        free(cache->values);
        free(cache->hashTable);
        free(cache);
        return NULL;
    }

    cache->lruList = (LRUList *)malloc(sizeof(LRUList));
    if (!cache->lruList) {
        free(cache->keys);
        free(cache->values);
        free(cache->hashTable);
        free(cache);
        return NULL;
    }

    cache->lruList->head = NULL;
    cache->lruList->tail = NULL;
    cache->lruList->size = 0;

    return cache;
}

void lRUCacheFree(LRUCache *obj) {
    if (obj) {
        LRUList *list = obj->lruList;
        ListNode *node = list->head;
        while (node) {
            ListNode *tmp = node;
            node = node->next;
            free(tmp);
        }
        free(obj->keys);
        free(obj->values);
        free(obj->hashTable);
        free(obj->lruList);
        free(obj);
    }
}

void addToHead(LRUList *list, ListNode *node) {
    if (list->head == NULL) {
        list->head = list->tail = node;
    } else {
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
    list->size++;
}

void removeNode(LRUList *list, ListNode *node) {
    if (node->prev)
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;
    if (node == list->head)
        list->head = node->next;
    if (node == list->tail)
        list->tail = node->prev;
    list->size--;
}

ListNode *addOrGet(LRUCache *cache, int key, int value) {
    int index = key % cache->hashSize;
    ListNode *node = (ListNode *)cache->hashTable[index];

    if (node) {
        if (node->key == key) {
            node->value = value;
            addToHead(cache->lruList, node);
            return node;
        }
        removeNode(cache->lruList, node);
    } else {
        node = (ListNode *)malloc(sizeof(ListNode));
        if (!node)
            return NULL;
        node->key = key;
        node->value = value;
    }

    node->next = NULL;
    node->prev = NULL;
    addToHead(cache->lruList, node);
    cache->hashTable[index] = (int)(intptr_t)node;

    if (cache->lruList->size > cache->capacity) {
        node = cache->lruList->tail;
        removeNode(cache->lruList, node);
        index = node->key % cache->hashSize;
        cache->hashTable[index] = 0;
        free(node);
    }

    return node;
}

int get(LRUCache *obj, int key) {
    int index = key % obj->hashSize;
    ListNode *node = (ListNode *)obj->hashTable[index];

    if (node && node->key == key) {
        addOrGet(obj, key, node->value);
        return node->value;
    }

    return -1; // Return -1 if the key is not found
}

void testLRUCache() {
    LRUCache *cache = lRUCacheCreate(2);
    printf("Get 1: %d\n", get(cache, 1)); // returns -1
    addOrGet(cache, 1, 1);
    printf("Get 1: %d\n", get(cache, 1)); // returns 1
    addOrGet(cache, 2, 2);
    printf("Get 2: %d\n", get(cache, 2)); // returns 2
    addOrGet(cache, 3, 3);                // evicts key 1
    printf("Get 1: %d\n", get(cache, 1)); // returns -1
    addOrGet(cache, 4, 4);                // evicts key 2
    printf("Get 2: %d\n", get(cache, 2)); // returns -1
    printf("Get 3: %d\n", get(cache, 3)); // returns 3
    printf("Get 4: %d\n", get(cache, 4)); // returns 4
    lRUCacheFree(cache);
}

// Example usage
int main() {
    LRUCache *cache = lRUCacheCreate(2);
    addOrGet(cache, 1, 1);
    printf("Get 1: %d\n", get(cache, 1)); // returns 1
    addOrGet(cache, 2, 2);
    printf("Get 2: %d\n", get(cache, 2)); // returns 2
    addOrGet(cache, 3, 3);                // evicts key 1
    printf("Get 1: %d\n", get(cache, 1)); // returns -1 (not found)
    addOrGet(cache, 4, 4);                // evicts key 2
    printf("Get 2: %d\n", get(cache, 2)); // returns -1 (not found)
    printf("Get 3: %d\n", get(cache, 3)); // returns 3
    printf("Get 4: %d\n", get(cache, 4)); // returns 4
    lRUCacheFree(cache);

    testLRUCache();
    return 0;
}
