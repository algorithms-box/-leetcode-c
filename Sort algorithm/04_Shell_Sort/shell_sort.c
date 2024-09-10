#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 希尔排序函数
void shell_sort(int *arr, int n) {
    int gap, i, j, temp;
    for (gap = n / 2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i += 1) {
            temp = arr[i];
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

// 希尔排序的单元测试
void test_shell_sort() {
    int arr[] = {12, 34, 54, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {2, 3, 12, 34, 54};
    shell_sort(arr, n);
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
    shell_sort(arr_copy, n);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken to sort: %f seconds\n", cpu_time_used);

    free(arr_copy); // 释放动态分配的内存
}

// 主函数
int main() {
    int arr[] = {12, 34, 54, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    // 单元测试
    test_shell_sort();

    // 性能测试
    performance_test(arr, n);

    return 0;
}

// 4. **希尔排序（Shell Sort）**：
//    -
//    是插入排序的一种更高效的改进版本。希尔排序通过将记录按不同的步长分组，对每组使用直接插入排序算法排序，随着步长逐渐缩小，整个序列向有序状态演进。

// 在这个代码中，`shell_sort` 函数实现了希尔排序算法。`test_shell_sort`
// 函数创建了一个整数数组，对其进行排序，并使用 `assert`
// 语句来检查排序后的数组是否与预期的排序结果相匹配。如果所有元素都按预期排序，则会打印一条消息表示测试通过。

// `performance_test` 函数使用 `clock`
// 函数来测量排序算法的执行时间，并打印出来。为了确保性能测试的准确性，我们对原始数组创建了一个副本，这样每次性能测试都是从相同的初始状态开始。在测试完成后，我们释放了动态分配的内存以避免内存泄漏。

// 要编译并运行这个程序，请确保你的环境支持C语言编译器，如gcc。你可以使用以下命令来编译程序：

// ```bash
// gcc -o shell_sort shell_sort.c -lm
// ```

// 然后运行编译出的程序：

// ```bash
// ./shell_sort
// ```

// 如果排序正确，你将看到输出消息 "All elements are correctly sorted."
// 以及排序所花费的时间。如果任何 `assert`
// 失败，程序将异常终止，并且不会输出这条消息。请注意，`-lm`
// 选项是为了链接数学库，因为某些系统可能需要它来使用 `clock` 函数。
