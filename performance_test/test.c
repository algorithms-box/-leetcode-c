#include <stdio.h>
#include <time.h>

// 递归计算斐波那契数
long fibonacciRecursive(int n) {
    if (n <= 1)
        return n;
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

int main() {
    int n = 40; // 递归深度，避免太大的n值导致栈溢出
    clock_t start = clock();
    long result = fibonacciRecursive(n);
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Recursive C: Fibonacci(%d) = %ld, Time = %f seconds\n", n, result,
           time_spent);
    return 0;
}