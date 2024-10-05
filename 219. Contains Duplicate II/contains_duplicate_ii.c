#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TABLE_SIZE 10007

typedef struct Node {
    int key;
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *table[TABLE_SIZE];
} HashMap;

int hash(int key) { return abs(key) % TABLE_SIZE; }

void insert(HashMap *map, int key, int value) {
    int index = hash(key);
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = map->table[index];
    map->table[index] = newNode;
}

Node *find(HashMap *map, int key) {
    int index = hash(key);
    Node *current = map->table[index];
    while (current) {
        if (current->key == key) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void freeMap(HashMap *map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = map->table[i];
        while (current) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
}

bool containsNearbyDuplicate(int *nums, int numsSize, int k) {
    HashMap map = {0};
    for (int i = 0; i < numsSize; i++) {
        Node *node = find(&map, nums[i]);
        if (node && i - node->value <= k) {
            freeMap(&map);
            return true;
        }
        insert(&map, nums[i], i);
    }
    freeMap(&map);
    return false;
}

// Unit tests
void runTests() {
    int nums1[] = {1, 2, 3, 1};
    assert(containsNearbyDuplicate(nums1, 4, 3) == true);

    int nums2[] = {1, 0, 1, 1};
    assert(containsNearbyDuplicate(nums2, 4, 1) == true);

    int nums3[] = {1, 2, 3, 1, 2, 3};
    assert(containsNearbyDuplicate(nums3, 6, 2) == false);

    printf("All tests passed!\n");
}

// Performance test
void performanceTest() {
    int size = 1000000;
    int *nums = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        nums[i] = rand() % 100000;
    }

    clock_t start = clock();
    bool result = containsNearbyDuplicate(nums, size, 10000);
    clock_t end = clock();

    printf("Performance test result: %s\n", result ? "true" : "false");
    printf("Time taken: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(nums);
}

int main() {
    runTests();
    performanceTest();
    return 0;
}