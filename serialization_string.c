#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *encode(char **strs, int count) {
    int total_length = 1; // 为第一个分隔符预留空间
    for (int i = 0; i < count; ++i) {
        int len = strlen(strs[i]);
        total_length += len + 1; // 为每个字符串和后面的分隔符预留空间
    }

    char *encoded_string = (char *)malloc(total_length);
    if (encoded_string == NULL) {
        return NULL; // 内存分配失败
    }
    encoded_string[0] = '\0'; // 初始化为空字符串

    char *p = encoded_string;
    for (int i = 0; i < count; ++i) {
        strcat(p, strs[i]); // 追加字符串
        p += strlen(strs[i]);
        if (i < count - 1) {
            *p = ','; // 字符串之间用逗号分隔
            p++;
        }
    }

    return encoded_string;
}

char **decode(const char *s, int *count) {
    int num_strings = 0;
    const char *p = s;
    while (*p) {
        if (*p == ',') {
            num_strings++;
        }
        p++;
    }
    num_strings++; // 最后一个字符串不会导致逗号计数增加

    char **strs = (char **)malloc(num_strings * sizeof(char *));
    if (strs == NULL) {
        *count = 0;
        return NULL; // 内存分配失败
    }

    p = s;
    char *q;
    for (int i = 0; i < num_strings; ++i) {
        strs[i] = (char *)malloc(strlen(p) + 1);
        if (strs[i] == NULL) {
            // 内存分配失败，清理已分配的内存
            for (int j = 0; j < i; ++j) {
                free(strs[j]);
            }
            free(strs);
            *count = 0;
            return NULL;
        }
        q = strs[i];
        while (*p != ',' && *p != '\0') {
            *q = *p;
            p++;
            q++;
        }
        *q = '\0';
        if (*p == ',') {
            p++;
        }
    }

    *count = num_strings;
    return strs;
}

// 用于释放解码后的字符串数组内存
void free_decoded_strings(char **strs, int count) {
    for (int i = 0; i < count; ++i) {
        free(strs[i]);
    }
    free(strs);
}

// 单元测试
void test_encode_decode() {
    char *strs[] = {"Hello", "World", "C", "Programming", "Language"};
    int count = sizeof(strs) / sizeof(strs[0]);
    char *encoded = encode(strs, count);
    assert(encoded != NULL);

    int decoded_count;
    char **decoded = decode(encoded, &decoded_count);
    assert(decoded_count == count);

    for (int i = 0; i < count; ++i) {
        assert(strcmp(strs[i], decoded[i]) == 0);
        free(decoded[i]); // 释放解码后的字符串
    }
    free(decoded);
    free(encoded);

    printf("All tests passed.\n");
}

int main() {
    test_encode_decode();
    return 0;
}