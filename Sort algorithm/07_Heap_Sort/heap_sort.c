#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 交换两个元素
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 堆化过程
void heapify(int *arr, int n, int i) {
    int largest = i;       // 假设根（父节点）是最大的
    int left = 2 * i + 1;  // 左子节点
    int right = 2 * i + 2; // 右子节点

    // 如果左子节点比根大，将左子节点设为最大
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // 如果右子节点比最大值还要大，将其设为最大
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // 如果最大值不是根元素，将其与根元素交换，然后继续堆化
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// 堆排序函数
void heap_sort(int *arr, int n) {
    // 建立堆
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // 从堆中一个接一个地提取元素
    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

// 堆排序的单元测试
void test_heap_sort() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {5, 6, 7, 11, 12, 13};
    heap_sort(arr, n);
    for (int i = 0; i < n; i++) {
        assert(arr[i] == expected[i]);
    }
    printf("All elements are correctly sorted.\n");
}

// 性能测试函数
void performance_test(int *arr, int n) {
    clock_t start, end;
    double cpu_time_used;

    int *arr_copy = (int *)malloc(n * sizeof(int));
    assert(arr_copy != NULL); // 检查内存分配是否成功

    // 复制数组内容
    for (int i = 0; i < n; i++) {
        arr_copy[i] = arr[i];
    }

    start = clock();
    heap_sort(arr_copy, n);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken to sort: %f seconds\n", cpu_time_used);

    free(arr_copy); // 释放动态分配的内存
}

// 主函数
int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    // 单元测试
    test_heap_sort();

    // 性能测试
    performance_test(arr, n);

    return 0;
}

// 7. **堆排序（Heap Sort）**：
//    -
//    利用堆这种数据结构所设计的一种排序算法。堆积是一个近似完全二叉树的结构，并同时满足堆积的性质：即子节点的键值或索引总是小于（或者大于）它的父节点。

// 在这个代码中，`heap_sort` 函数实现了堆排序算法，`heapify`
// 函数用于确保子树满足堆的性质。`test_heap_sort`
// 函数创建了一个整数数组，对其进行排序，并使用 `assert`
// 语句来检查排序后的数组是否与预期的排序结果相匹配。如果所有元素都按预期排序，则会打印一条消息表示测试通过。

// `performance_test` 函数使用 `clock`
// 函数来测量排序算法的执行时间，并打印出来。为了确保性能测试的准确性，我们对原始数组创建了一个副本，这样每次性能测试都是从相同的初始状态开始。在测试完成后，我们释放了动态分配的内存以避免内存泄漏。

// 要编译并运行这个程序，请确保你的环境支持C语言编译器，如gcc。你可以使用以下命令来编译程序：

// ```bash
// gcc -o heap_sort heap_sort.c -lm
// ```

// 然后运行编译出的程序：

// ```bash
// ./heap_sort
// ```

// 如果排序正确，你将看到输出消息 "All elements are correctly sorted."
// 以及排序所花费的时间。如果任何 `assert`
// 失败，程序将异常终止，并且不会输出这条消息。请注意，`-lm`
// 选项是为了链接数学库，因为某些系统可能需要它来使用 `clock` 函数。
