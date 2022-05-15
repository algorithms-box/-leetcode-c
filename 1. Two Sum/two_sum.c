#include <stdio.h>
#include <stdlib.h>

struct vectorToMap {
    int val;
    int index;
};

static int compare(const void *a, const void *b) {
    return ((struct vectorToMap *) a)->val - ((struct vectorToMap *) b)->val;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int i, j;
    struct vectorToMap *vm = malloc(numsSize * sizeof(*vm));
    for(i = 0; i<numsSize; i++) {
        vm[i].val = nums[i];
        vm[i].index = i;
    }

    qsort(vm, numsSize, sizeof(*vm), compare);

    int *results = malloc(2 * sizeof(int));

    i = 0;
    j = numsSize -1;
    while(i<j) {
        int sum = vm[i].val + vm[j].val;
        if (sum < target) {
            i++;
        } else if (sum > target) {
            j--;
        } else {
            results[0] = vm[i].index;
            results[1] = vm[j].index;
            *returnSize = 2;
            return results;
        }
    }
    return NULL;
}


int main(void) {
    int nums[] = {3,2,3};
    int size = sizeof(nums) / sizeof(*nums);
    int target = 6;
    int count = 0;
    int *indexes = twoSum(nums, size, target,&count);
    if(indexes != NULL) {
        printf("%d %d\n", indexes[0], indexes[1]);
    } else {
        printf("Not found\n");
    }

    return 0;
}
