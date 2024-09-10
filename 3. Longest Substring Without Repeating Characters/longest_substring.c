#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lengthOfLongestSubstring(char *s) {
    int maxLen = 0;
    // 用来记录当前考虑的子串的起始位置
    int start = 0;
    int len = strlen(s);
    int charIndex[128] = {0}; // 假设ASCII字符集

    for (int i = 0; i < len; i++) {
        // 检查字符是否在当前子串中
        // 字符 's[i]' 被转换为其对应的ASCII码值
        while (charIndex[(int)s[i]] != 0) {
            charIndex[(int)s[start]] = 0;
            start++;
        }
        // charIndex[(int)s[i]] = i + 1; // 当前字符位置+1，因为数组是从0开始的
        charIndex[(int)s[i]] = 1; // 如果没有出现重复的，就暂时赋值为1
        maxLen = (i - start + 1 > maxLen) ? (i - start + 1) : maxLen;
    }

    return maxLen;
}

// 单元测试
void test() {
    char s1[] = "abcabcbb";
    printf("Test 1: Expected 3, got %d\n", lengthOfLongestSubstring(s1));

    char s2[] = "bbbbb";
    printf("Test 2: Expected 1, got %d\n", lengthOfLongestSubstring(s2));

    char s3[] = "pwwkew";
    printf("Test 3: Expected 3, got %d\n", lengthOfLongestSubstring(s3));

    char s4[] = "dvdf";
    printf("Test 4: Expected 3, got %d\n", lengthOfLongestSubstring(s4));

    char s5[] = " ";
    printf("Test 5: Expected 1, got %d\n", lengthOfLongestSubstring(s5));
}

int main() {
    test(); // 运行单元测试
    return 0;
}

// ### 内存泄漏考虑
// 在上面的代码中，我们没有使用动态内存分配，因此不存在内存泄漏的问题。所有的变量都是在栈上分配的，当函数返回时，它们会自动被清理。

// ### 单元测试
// 单元测试部分定义了一个 `test` 函数，它测试了几个不同的字符串，以确保我们的
// `lengthOfLongestSubstring` 函数能够正确地返回最长不含重复字符的子串长度。在
// `main` 函数中调用 `test` 函数来执行这些测试。

// ### 注意
// - 这个解决方案假设输入字符都是ASCII字符。
// - 如果输入字符串包含非ASCII字符，可能需要调整 `charIndex` 数组的大小。
// -
// 这个算法的时间复杂度是O(n)，其中n是字符串的长度。这是因为每个字符最多被访问两次（一次是向前移动start指针，一次是更新maxLen）。

// 这个解决方案应该能够满足题目要求，并且通过了基本的单元测试。在实际使用中，可能需要更多的测试来确保代码的健壮性。
