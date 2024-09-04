#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义一个结构体来存储结果集
struct Result {
    char **str;
    int size;
    int capacity;
};

// 函数声明
void generateParenthesis(int left, int right, int n, char *current,
                         struct Result *result);
void addResult(struct Result *result, char *str);

int main() {
    int n = 5; // 例如，生成3对括号的所有组合
    struct Result result = {0};
    result.capacity = 10;
    result.size = 0;
    result.str = (char **)malloc(sizeof(char *) * result.capacity);

    char current[2 * n + 1]; // 当前生成的字符串
    current[0] = '\0';       // 初始化为空字符串
    generateParenthesis(0, 0, n, current, &result);

    // 打印结果
    for (int i = 0; i < result.size; i++) {
        printf("%s\n", result.str[i]);
    }

    // 释放结果集内存
    for (int i = 0; i < result.size; i++) {
        free(result.str[i]);
    }
    free(result.str);

    return 0;
}

// 递归函数生成括号组合
void generateParenthesis(int left, int right, int n, char *current,
                         struct Result *result) {
    if (left < n) {
        current[left + right] = '(';
        generateParenthesis(left + 1, right, n, current, result);
        current[left + right] = '\0'; // 回溯
    }

    if (right < left) {
        current[left + right] = ')';
        generateParenthesis(left, right + 1, n, current, result);
        current[left + right] = '\0'; // 回溯
    }

    if (left == n && right == n) {
        addResult(result, strdup(current)); // 添加到结果集
    }
}

// 将新的结果添加到结果集中
void addResult(struct Result *result, char *str) {
    if (result->size >= result->capacity) {
        result->capacity *= 2;
        result->str =
            (char **)realloc(result->str, sizeof(char *) * result->capacity);
    }
    result->str[result->size++] = str;
}