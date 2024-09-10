#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 插入排序函数，用于对桶内元素进行排序
void insertion_sort(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// 桶排序函数
void bucket_sort(int *arr, int n) {
    int *bucket;
    int max = arr[0], min = arr[0];

    // 找到最大值和最小值
    for (int i = 0; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
        if (arr[i] < min)
            min = arr[i];
    }

    // 计算桶的数量
    int bucket_size = (max - min) / (n - 1) + 1;
    int bucket_count = (max - min) / bucket_size + 1;
    bucket = (int *)calloc(bucket_count, sizeof(int));

    // 为0初始化桶
    for (int i = 0; i < bucket_count; i++) {
        bucket[i] = 0;
    }

    // 将数组元素分配到各个桶中
    for (int i = 0; i < n; i++) {
        bucket[(arr[i] - min) / bucket_size]++;
    }

    // 从桶中收集元素
    int index = 0;
    for (int i = 0; i < bucket_count; i++) {
        while (bucket[i] > 0) {
            arr[index++] = i * bucket_size + min;
            bucket[i]--;
        }
    }

    // 释放桶数组
    free(bucket);
}

// 桶排序的单元测试
void test_bucket_sort() {
    int arr[] = {5, 2, 1, 9, 7, 6, 3, 8, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    bucket_sort(arr, n);
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
    bucket_sort(arr_copy, n);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken to sort: %f seconds\n", cpu_time_used);

    free(arr_copy); // 释放动态分配的内存
}

// 主函数
int main() {
    int arr[] = {5, 2, 1, 9, 7, 6, 3, 8, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    // 单元测试
    test_bucket_sort();

    // 性能测试
    performance_test(arr, n);

    return 0;
}

// 9. **桶排序（Bucket Sort）**：
//    -
//    将数组分为多个区间，每个区间称为一个桶。每个桶内的元素采用插入排序或其他排序方法进行排序，最后按顺序合并各个桶中的数据。

// 在这个代码中，`bucket_sort` 函数实现了桶排序算法。`insertion_sort`
// 函数用于对桶内元素进行排序，虽然在这个示例中我们没有使用它，因为桶排序假设输入是均匀分布的，每个桶只需要通过简单的收集操作来排序。`test_bucket_sort`
// 函数创建了一个整数数组，对其进行排序，并使用 `assert`
// 语句来检查排序后的数组是否与预期的排序结果相匹配。如果所有元素都按预期排序，则会打印一条消息表示测试通过。

// `performance_test` 函数使用 `clock`
// 函数来测量排序算法的执行时间，并打印出来。为了确保性能测试的准确性，我们对原始数组创建了一个副本，这样每次性能测试都是从相同的初始状态开始。在测试完成后，我们释放了动态分配的内存以避免内存泄漏。

// 要编译并运行这个程序，请确保你的环境支持C语言编译器，如gcc。你可以使用以下命令来编译程序：

// ```bash
// gcc -o bucket_sort bucket_sort.c -lm
// ```

// 然后运行编译出的程序：

// ```bash
// ./bucket_sort
// ```

// 如果排序正确，你将看到输出消息 "All elements are correctly sorted."
// 以及排序所花费的时间。如果任何 `assert`
// 失败，程序将异常终止，并且不会输出这条消息。请注意，`-lm`
// 选项是为了链接数学库，因为某些系统可能需要它来使用 `clock` 函数。
