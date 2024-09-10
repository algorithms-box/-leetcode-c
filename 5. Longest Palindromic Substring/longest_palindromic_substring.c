#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 检查从left到right的子串是否是回文
int isPalindrome(const char *s, int left, int right) {
    while (left < right) {
        if (s[left] != s[right]) {
            return 0;
        }
        left++;
        right--;
    }
    return 1;
}

// 从中心扩展，寻找最长回文子串
int expandAroundCenter(const char *s, int left, int right) {
    while (left >= 0 && right < strlen(s) && s[left] == s[right]) {
        left--;
        right++;
    }
    return right - left - 1;
}

// 寻找最长回文子串
char *longestPalindrome(const char *s) {
    int len = strlen(s);
    int maxLen = 0;
    int start = 0;
    char *result = NULL;

    for (int i = 0; i < len; i++) {
        // 以s[i]为中心扩展
        int len1 = expandAroundCenter(s, i, i);
        int len2 = expandAroundCenter(s, i, i + 1);
        int len = (len1 > len2) ? len1 : len2;
        if (len > maxLen) {
            maxLen = len;
            start = i - (len - 1) / 2;
            free(result); // 释放之前的结果
            result = (char *)malloc(len + 1);
            if (result == NULL) {
                perror("malloc failed");
                exit(EXIT_FAILURE);
            }
            strncpy(result, s + start, len);
            result[len] = '\0';
        }
    }
    return result;
}

// 单元测试
void test() {
    char *s1 = "babad";
    char *result1 = longestPalindrome(s1);
    printf("Test 1: Expected 'bab' or 'aba', got '%s'\n", result1);
    free(result1);

    char *s2 = "cbbd";
    char *result2 = longestPalindrome(s2);
    printf("Test 2: Expected 'bb', got '%s'\n", result2);
    free(result2);

    char *s3 = "a";
    char *result3 = longestPalindrome(s3);
    printf("Test 3: Expected 'a', got '%s'\n", result3);
    free(result3);

    char *s4 = "";
    char *result4 = longestPalindrome(s4);
    printf("Test 4: Expected '', got '%s'\n", result4);
    free(result4);

    char *s5 = "racecar";
    char *result5 = longestPalindrome(s5);
    printf("Test 5: Expected 'racecar', got '%s'\n", result5);
    free(result5);
}

int main() {
    test(); // 运行单元测试
    return 0;
}

// ### 代码解释

// 1. `isPalindrome` 函数用于检查从 `left` 到 `right` 的子串是否是回文。
// 2. `expandAroundCenter` 函数用于从中心向两侧扩展，寻找最长的回文子串。
// 3. `longestPalindrome` 函数是主要的函数，它遍历字符串
// `s`，寻找最长的回文子串。它使用 `expandAroundCenter`
// 函数来从每个可能的中心向两侧扩展。
// 4. `test` 函数包含了几个测试用例，用于验证 `longestPalindrome` 函数的正确性。
// 5. `main` 函数调用 `test` 函数来执行单元测试。

// ### 内存泄漏考虑

// - 使用 `malloc` 分配内存时，如果后续不再需要，应该使用 `free` 函数释放内存。
// - 在 `longestPalindrome`
// 函数中，每次找到更长的回文子串时，都会释放之前分配的内存，以避免内存泄漏。

// ### 注意事项

// - 这个解决方案假设输入字符串是非空的。
// - 由于回文的定义，这个解决方案只考虑了奇数长度和偶数长度的回文子串。
// - 在实际使用中，可能需要更多的测试来确保代码的健壮性。
