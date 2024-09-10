#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 冒泡排序函数
void bubble_sort(int *arr, int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // 交换相邻元素
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// 冒泡排序的单元测试
void test_bubble_sort() {
    int arr[] = {95, 45, 48, 98, 485, 65, 54, 65, 99, 1000, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int expected[] = {1, 45, 48, 54, 65, 65, 95, 98, 99, 485, 1000};
    bubble_sort(arr, n);
    for (int i = 0; i < n; i++) {
        assert(arr[i] == expected[i]);
    }
    printf("All elements are correctly sorted.\n");
}

// 性能测试函数
void performance_test(int *arr, int n) {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    bubble_sort(arr, n);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken to sort: %f seconds\n", cpu_time_used);
}

// 主函数
int main() {
    int arr[] = {95, 45, 48, 98, 485, 65, 54, 65, 99, 1000, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    // 单元测试
    test_bubble_sort();

    // 性能测试
    performance_test(arr, n);

    return 0;
}

// 1. **冒泡排序（Bubble Sort）**：
//    -
//    通过重复遍历待排序序列，比较每对相邻元素，如果顺序错误就交换它们。过程像气泡慢慢浮到水面一样，故名冒泡排序。

// 在这个代码中，`bubble_sort` 函数实现了冒泡排序算法。`test_bubble_sort`
// 函数创建了一个整数数组，对其进行排序，并使用 `assert`
// 语句来检查排序后的数组是否与预期的排序结果相匹配。如果所有元素都按预期排序，则会打印一条消息表示测试通过。

// `performance_test` 函数使用 `clock`
// 函数来测量排序算法的执行时间，并打印出来。这可以帮助我们了解算法的性能。

// 要编译并运行这个程序，请确保你的环境支持C语言编译器，如gcc。你可以使用以下命令来编译程序：

// ```bash
// gcc -o bubble_sort bubble_sort.c -lm
// ```

// 然后运行编译出的程序：

// ```bash
// ./bubble_sort
// ```

// 如果排序正确，你将看到输出消息 "All elements are correctly sorted."
// 以及排序所花费的时间。如果任何 `assert`
// 失败，程序将异常终止，并且不会输出这条消息。请注意，`-lm`
// 选项是为了链接数学库，因为某些系统可能需要它来使用 `clock` 函数。
