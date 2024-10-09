#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

int removeDuplicates(int* nums, int numSize) {
    if (numSize == 0 || numSize == 1) {
	return numSize;
    }

    int slow = 1;
    for (int fast = 1; fast < numSize; ++fast) {
	if(nums[fast] != nums[slow - 1]) {
	    nums[slow] = nums[fast];
	    slow++;
	}
    }
    return slow;
}

void testRemoveDuplicates() {
    int nums1[] = {1, 1, 2};
    int size1 = sizeof(nums1) / sizeof(nums1[0]);
    assert(removeDuplicates(nums1, size1) == 2);
    assert(nums1[0] == 1 && nums1[1] == 2);

    int nums2[] = {0, 0, 3, 3, 3, 3, 3};
    int size2 = sizeof(nums2) / sizeof(nums2[0]);
    assert(removeDuplicates(nums2, size2) == 2);
    assert(nums2[0] == 0 && nums2[1] == 3);

    printf("All tests passed.\n");
}

// Performance test function
void performanceTest() {
    const int SIZE = 10000000;
    int* nums = (int*)malloc(SIZE * sizeof(int));
    for (int i = 0; i < SIZE - 1; ++i) {
	nums[i] = i % 10; // Duplicates every 10 numbers
	nums[i + 1] = nums[i];
    }
    nums[SIZE - 1] = 9; // Last element is unique

    clock_t start = clock();
    int newSize = removeDuplicates(nums, SIZE);
    clock_t end = clock();

    printf("Performance test completed. New size: %d, Time taken: %lf seconds\n", newSize, (double)(end - start) / CLOCKS_PER_SEC);

    free(nums);
}

int main(){
    testRemoveDuplicates();
    performanceTest();
    return 0;
}
