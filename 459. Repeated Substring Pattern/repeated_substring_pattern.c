#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

bool repeatedSubstringPattern(char* s) {
    int len = strlen(s);
    for (int i = 1; i <= len / 2; i++) {
        if (len % i == 0) {
            // 创建子串
            char *substr = (char*)malloc(i + 1);
            if (substr == NULL) {
                // 处理内存分配失败
                return false;
            }
            strncpy(substr, s, i);
            substr[i] = '\0';
            
            // 创建重复的子串
            char *doubled = (char*)malloc((len / i) * i + 1);
            if (doubled == NULL) {
                // 处理内存分配失败
                free(substr);
                return false;
            }
            doubled[0] = '\0';
            for (int j = 0; j < len / i; j++) {
                strcat(doubled, substr);
            }
            
            // 检查是否匹配
            bool result = strcmp(doubled, s) == 0;
            
            free(substr);
            free(doubled);
            if (result) {
                return true;
            }
        }
    }
    return false;
}

void testRepeatedSubstringPattern() {
    assert(repeatedSubstringPattern("abab") == true);
    assert(repeatedSubstringPattern("aba") == false);
    assert(repeatedSubstringPattern("abcabcabcabc") == true);
    assert(repeatedSubstringPattern("abc") == false);
    printf("All tests passed!\n");
}

int main() {
    testRepeatedSubstringPattern();
    return 0;
}
