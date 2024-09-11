#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Interval {
    int start;
    int end;
} Interval;

// 比较函数，用于排序区间
int compare(const void *a, const void *b) {
    Interval *intervalA = (Interval *)a;
    Interval *intervalB = (Interval *)b;
    return intervalA->start - intervalB->start;
}

// 合并区间
int **merge(int **intervals, int intervalsSize, int *intervalsColSize,
            int *returnSize, int **returnColumnSizes) {
    int maxColSize = *intervalsColSize;
    *returnSize = 0;
    if (intervalsSize == 0) {
        *returnColumnSizes = malloc(1 * sizeof(int));
        (*returnColumnSizes)[0] = 2;
        return NULL;
    }

    // 首先对区间按照起始位置进行排序
    for (int i = 0; i < intervalsSize; i++) {
        qsort(intervals[i], maxColSize, sizeof(int), compare);
    }

    int **merged = malloc(sizeof(int *) * intervalsSize);
    *returnColumnSizes = malloc(sizeof(int) * intervalsSize);

    int mergedCount = 0;
    merged[mergedCount] = intervals[0];
    (*returnColumnSizes)[mergedCount] = maxColSize;
    mergedCount++;

    for (int i = 1; i < intervalsSize; i++) {
        int *current = merged[mergedCount - 1];
        int *next = intervals[i];

        if (current[maxColSize * (mergedCount - 1) + 1] > next[0]) { // 检查重叠
            current[maxColSize * (mergedCount - 1)] =
                fmin(current[maxColSize * (mergedCount - 1)], next[0]);
            current[maxColSize * (mergedCount - 1) + 1] =
                fmax(current[maxColSize * (mergedCount - 1) + 1], next[1]);
        } else {
            merged[mergedCount] = next;
            (*returnColumnSizes)[mergedCount] = maxColSize;
            mergedCount++;
        }
    }

    *returnSize = mergedCount;
    return merged;
}

void test() {
    int intervals1[][2] = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    int intervalsSize1 = 4;
    int intervalsColSize1 = 2;
    int returnSize1;
    int *returnColumnSizes1;
    int **result1 = merge(intervals1, intervalsSize1, &intervalsColSize1,
                          &returnSize1, &returnColumnSizes1);
    for (int i = 0; i < returnSize1; i++) {
        printf("[");
        for (int j = 0; j < returnColumnSizes1[i]; j++) {
            printf("%d ", result1[i][j]);
        }
        printf("]\n");
    }
    free(result1);
    free(returnColumnSizes1);

    assert(returnSize1 == 2);
    assert(returnColumnSizes1[0] == 2 && result1[0][0] == 1 &&
           result1[0][1] == 6);
    assert(returnColumnSizes1[1] == 2 && result1[1][0] == 8 &&
           result1[1][1] == 18);

    int intervals2[][2] = {{1, 4}, {4, 5}};
    int intervalsSize2 = 2;
    int intervalsColSize2 = 2;
    int returnSize2;
    int *returnColumnSizes2;
    int **result2 = merge(intervals2, intervalsSize2, &intervalsColSize2,
                          &returnSize2, &returnColumnSizes2);
    assert(returnSize2 == 1);
    assert(returnColumnSizes2[0] == 2 && result2[0][0] == 1 &&
           result2[0][1] == 5);

    printf("All tests passed.\n");
}

int main() {
    test();
    return 0;
}