描述
首先输入要输入的整数个数n，然后输入n个整数。输出为n个整数中负数的个数，和所有正整数的平均值，结果保留一位小数。
0即不是正整数，也不是负数，不计入计算。如果没有正数，则平均值为0。

数据范围： 1≤n≤2000，输入的整数都满足∣val∣≤ 1000

输入描述：
首先输入一个正整数n，
然后输入n个整数。

输出描述：
输出负数的个数，和所有正整数的平均值。

Example 1:

Input:
11 
1 2 3 4 5 6 7 8 9 0 -1

Output:
1 5.0


Example 2:
Input:
3
0 0 0 

Output:
0 0.0




#include <stdio.h>

int main() {
    int a, b;
    while (scanf("%d %d", &a, &b) != EOF) { // 注意 while 处理多个 case
        // 64 位输出请用 printf("%lld") to 
        printf("%d\n", a + b);
    }
    return 0;
}
