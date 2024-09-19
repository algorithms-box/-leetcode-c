#include <chrono>
#include <iostream>

// 递归计算斐波那契数
long fibonacciRecursive(int n) {
    if (n <= 1)
        return n;
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

int main() {
    int n = 40; // 递归深度，避免太大的n值导致栈溢出
    auto start = std::chrono::high_resolution_clock::now();
    long result = fibonacciRecursive(n);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_spent = end - start;
    std::cout << "Recursive C++: Fibonacci(" << n << ") = " << result
              << ", Time = " << time_spent.count() << " seconds" << std::endl;
    return 0;
}