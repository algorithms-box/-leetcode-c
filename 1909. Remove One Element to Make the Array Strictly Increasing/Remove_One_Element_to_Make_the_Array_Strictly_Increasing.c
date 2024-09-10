#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool validStrictIncreasing(int *nums, int numSize) {
    for (int i = 1; i < numSize; i++) {
        if (nums[i - 1] >= nums[i]) {
            return false;
        }
    }
    return true;
}

int *removeElement(int *nums, int numSize, int removeIndex, int *returnSize) {
    if (removeIndex < 0 || removeIndex >= numSize) {
        *returnSize = numSize;
        return nums;
    }

    int *newArr = (int *)malloc(sizeof(int) * (numSize - 1));
    if (!newArr) {
        *returnSize = 0;
        return NULL;
    }

    int j = 0;
    for (int i = 0; i < numSize; i++) {
        if (i != removeIndex) {
            newArr[j++] = nums[i];
        }
    }
    *returnSize = numSize - 1;
    return newArr;
}

bool canBeIncreasing(int *nums, int numsSize) {
    if (numsSize <= 1) {
        return true;
    }

    bool existFlag = false;
    for (int i = 1; i < numsSize; i++) {
        int returnSize = 0;
        int *newArr = removeElement(nums, numsSize, i, &returnSize);
        existFlag = validStrictIncreasing(newArr, returnSize);
        if (existFlag) {
            return true;
        }
    }
    return false;
}

void test() {
    assert(canBeIncreasing((int[]){1, 2, 10, 3, 4}, 5) == true);
    assert(canBeIncreasing((int[]){4, 2, 3}, 3) == false);
    assert(canBeIncreasing((int[]){1, 2, 3, 4, 5}, 5) == true);
    assert(canBeIncreasing((int[]){2, 3, 3, 4, 6}, 5) == true);
    printf("All tests passed.\n");
}

int main() {
    test();
    return 0;
}