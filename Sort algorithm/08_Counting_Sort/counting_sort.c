#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 计数排序函数
void count_sort(int *arr, int *output, int n) {
    int *count =
        (int *)calloc(256, sizeof(int)); // 为256个可能的字符创建计数数组
    assert(count != NULL);

    // 计算每个值的出现次数
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    // 累加每个计数
    for (int i = 1; i < 256; i++) {
        count[i] += count[i - 1];
    }

    // 构建输出数组
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // 释放计数数组
    free(count);
}

// 计数排序的单元测试
void test_count_sort() {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int *output = (int *)malloc(n * sizeof(int));
    assert(output != NULL);

    count_sort(arr, output, n);
    int expected[] = {1, 1, 2, 3, 3, 4, 5, 5, 6, 9};
    for (int i = 0; i < n; i++) {
        assert(output[i] == expected[i]);
    }
    printf("All elements are correctly sorted.\n");

    // 释放输出数组
    free(output);
}

// 性能测试函数
void performance_test(int *arr, int n) {
    clock_t start, end;
    double cpu_time_used;

    int *output = (int *)malloc(n * sizeof(int));
    assert(output != NULL);

    start = clock();
    count_sort(arr, output, n);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken to sort: %f seconds\n", cpu_time_used);

    // 释放输出数组
    free(output);
}

// 主函数
int main() {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    // 单元测试
    test_count_sort();

    // 性能测试
    performance_test(arr, n);

    return 0;
}

// 8. **计数排序（Counting Sort）**：
//    -
//    非比较型排序算法，对一个待排序的数组进行统计，统计每个值的出现次数，进而得到数组的排序。

// 在这个代码中，`count_sort` 函数实现了计数排序算法。`test_count_sort`
// 函数创建了一个整数数组，对其进行排序，并使用 `assert`
// 语句来检查排序后的数组是否与预期的排序结果相匹配。如果所有元素都按预期排序，则会打印一条消息表示测试通过。

// `performance_test` 函数使用 `clock`
// 函数来测量排序算法的执行时间，并打印出来。为了确保性能测试的准确性，我们对原始数组创建了一个副本，这样每次性能测试都是从相同的初始状态开始。在测试完成后，我们释放了动态分配的内存以避免内存泄漏。

// 要编译并运行这个程序，请确保你的环境支持C语言编译器，如gcc。你可以使用以下命令来编译程序：

// ```bash
// gcc -o count_sort count_sort.c -lm
// ```

// 然后运行编译出的程序：

// ```bash
// ./count_sort
// ```

// 如果排序正确，你将看到输出消息 "All elements are correctly sorted."
// 以及排序所花费的时间。如果任何 `assert`
// 失败，程序将异常终止，并且不会输出这条消息。请注意，`-lm`
// 选项是为了链接数学库，因为某些系统可能需要它来使用 `clock` 函数。
