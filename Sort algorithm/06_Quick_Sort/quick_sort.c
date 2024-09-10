#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 快速排序的分区函数
int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

// 快速排序函数
void quick_sort(int *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// 快速排序的单元测试
void test_quick_sort() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {1, 5, 7, 8, 9, 10};
    quick_sort(arr, 0, n - 1);
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
    quick_sort(arr_copy, 0, n - 1);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken to sort: %f seconds\n", cpu_time_used);

    free(arr_copy); // 释放动态分配的内存
}

// 主函数
int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    // 单元测试
    test_quick_sort();

    // 性能测试
    performance_test(arr, n);

    return 0;
}

// 6. **快速排序（Quick Sort）**：
//    -
//    通过一个基准值将数组分为两个部分，其中一部分的所有数据都比另一部分的所有数据要小，然后再递归地对这两部分数据分别进行快速排序，整个排序过程可以递归进行，以达到整个数据变成有序序列。

// 在这个代码中，`quick_sort` 函数实现了快速排序算法，`partition`
// 函数用于在每次递归中分区数组。`test_quick_sort`
// 函数创建了一个整数数组，对其进行排序，并使用 `assert`
// 语句来检查排序后的数组是否与预期的排序结果相匹配。如果所有元素都按预期排序，则会打印一条消息表示测试通过。

// `performance_test` 函数使用 `clock`
// 函数来测量排序算法的执行时间，并打印出来。为了确保性能测试的准确性，我们对原始数组创建了一个副本，这样每次性能测试都是从相同的初始状态开始。在测试完成后，我们释放了动态分配的内存以避免内存泄漏。

// 要编译并运行这个程序，请确保你的环境支持C语言编译器，如gcc。你可以使用以下命令来编译程序：

// ```bash
// gcc -o quick_sort quick_sort.c -lm
// ```

// 然后运行编译出的程序：

// ```bash
// ./quick_sort
// ```

// 如果排序正确，你将看到输出消息 "All elements are correctly sorted."
// 以及排序所花费的时间。如果任何 `assert`
// 失败，程序将异常终止，并且不会输出这条消息。请注意，`-lm`
// 选项是为了链接数学库，因为某些系统可能需要它来使用 `clock` 函数。
