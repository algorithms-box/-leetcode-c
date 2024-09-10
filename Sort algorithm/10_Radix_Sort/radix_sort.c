#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10 // 假设最大位数为10

// 辅助函数，用于获取数字的第d位
int get_digit(int n, int d) {
    int temp = 1;
    for (int i = 0; i < d; i++) {
        temp *= 10;
    }
    return (n / temp) % 10;
}

// 辅助函数，用于对桶内元素进行排序
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

// 基数排序函数
void radix_sort(int *arr, int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    int exp = 1;
    while (max / exp > 0) {
        int *temp = (int *)malloc(n * sizeof(int));
        assert(temp != NULL);
        int *count = (int *)calloc(10, sizeof(int));
        assert(count != NULL);
        int *output = (int *)malloc(n * sizeof(int));
        assert(output != NULL);

        // 计算每个桶中元素的数量
        for (int i = 0; i < n; i++) {
            count[get_digit(arr[i], exp)]++;
        }

        // 累加每个桶中元素的数量
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        // 从后向前收集元素
        for (int i = n - 1; i >= 0; i--) {
            output[count[get_digit(arr[i], exp)] - 1] = arr[i];
            count[get_digit(arr[i], exp)]--;
        }

        // 复制回原数组
        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }

        // 释放内存
        free(temp);
        free(count);
        free(output);

        exp *= 10;
    }
}

// 基数排序的单元测试
void test_radix_sort() {
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {2, 24, 45, 66, 75, 90, 170, 802};
    radix_sort(arr, n);
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
    radix_sort(arr_copy, n);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken to sort: %f seconds\n", cpu_time_used);

    free(arr_copy); // 释放动态分配的内存
}

// 主函数
int main() {
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);

    // 单元测试
    test_radix_sort();

    // 性能测试
    performance_test(arr, n);

    return 0;
}

// 10. **基数排序（Radix Sort）**：
//     -
//     按照低位先排序，然后收集；再按照高位排序，然后再收集，以此类推，直到最高位。有时候有些属性是有优先顺序的，先按低优先级排序，再按高优先级排序。

// 在这个代码中，`radix_sort` 函数实现了基数排序算法。`get_digit`
// 函数用于获取数字的第 `d` 位，`insertion_sort`
// 函数用于对桶内元素进行排序，虽然在这个示例中我们没有使用它，因为基数排序假设输入是均匀分布的，每个桶只需要通过简单的收集操作来排序。`test_radix_sort`
// 函数创建了一个整数数组，对其进行排序，并使用 `assert`
// 语句来检查排序后的数组是否与预期的排序结果相匹配。如果所有元素都按预期排序，则会打印一条消息表示测试通过。

// `performance_test` 函数使用 `clock`
// 函数来测量排序算法的执行时间，并打印出来。为了确保性能测试的准确性，我们对原始数组创建了一个副本，这样每次性能测试都是从相同的初始状态开始。在测试完成后，我们释放了动态分配的内存以避免内存泄漏。

// 要编译并运行这个程序，请确保你的环境支持C语言编译器，如gcc。你可以使用以下命令来编译程序：

// ```bash
// gcc -o radix_sort radix_sort.c -lm
// ```

// 然后运行编译出的程序：

// ```bash
// ./radix_sort
// ```

// 如果排序正确，你将看到输出消息 "All elements are correctly sorted."
// 以及排序所花费的时间。如果任何 `assert`
// 失败，程序将异常终止，并且不会输出这条消息。请注意，`-lm`
// 选项是为了链接数学库，因为某些系统可能需要它来使用 `clock` 函数。
