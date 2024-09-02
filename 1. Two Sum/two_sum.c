#include <stdio.h>
#include <stdlib.h>

struct map {
    int index;
    int val;
};

static int compare(const void *a, const void *b) {
    return ((struct map *)a)->val - ((struct map *)b)->val;
}

int *twosum(int *nums, int numsSize, int target, int *returnSize) {
    int i, j;
    struct map *mp = malloc(numsSize * sizeof(*mp));
    for (i = 0; i < numsSize; i++) {
        mp[i].index = i;
        mp[i].val = nums[i];
    }
    qsort(mp, numsSize, sizeof(*mp), compare);

    int *results = malloc(2 * sizeof(int));
    i = 0;
    j = numsSize - 1;
    while (i < j) {
        int sum = mp[i].val + mp[j].val;
        if (sum < target) {
            i++;
        } else if (sum > target) {
            j--;
        } else {
            results[0] = mp[i].index;
            results[1] = mp[j].index;
            *returnSize = 2;
            return results;
        }
    }

    return NULL;
}

int main(void) {
    int nums[] = {3, 2, 3, 5, 7, 1, 2, 9};
    int size = sizeof(nums) / sizeof(*nums);
    int target = 9;
    int count = 0;
    int *indexes = twosum(nums, size, target, &count);
    if (indexes != NULL) {
        printf("%d %d\n", indexes[0], indexes[1]);
    } else {
        printf("Not found\n");
    }

    return 0;
}