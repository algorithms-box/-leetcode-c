#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// 定义一个栈结构
// Stack 结构体定义了一个栈，包含一个整数数组 stack 来存储栈内的元素，一个整数
// top 来指示栈顶的位置（栈为空时 top 为 -1），以及一个整数 capacity
// 来存储栈的最大容量。
typedef struct {
    int *stack;
    int top;
    int capacity;
} Stack;

// 初始化栈
// initStack 函数用于初始化一个栈，为其分配内存，并设置栈顶位置和容量。
void initStack(Stack *s, int size) {
    s->stack = (int *)malloc(size * sizeof(int));
    s->top = -1;
    s->capacity = size;
}

// 判断栈是否为空
// initStack 函数用于初始化一个栈，为其分配内存，并设置栈顶位置和容量。
int isEmpty(Stack *s) { return s->top == -1; }

// 判断栈是否已满
// isFull 函数用于检查栈是否已满。
int isFull(Stack *s) { return s->top == s->capacity - 1; }

// 压栈
// push 函数用于将一个元素压入栈顶。如果栈已满，则不进行操作。
void push(Stack *s, int value) {
    if (isFull(s)) {
        return;
    }
    s->stack[++(s->top)] = value;
}

// 弹栈
// push 函数用于将一个元素压入栈顶。如果栈已满，则不进行操作。
int pop(Stack *s) {
    if (isEmpty(s)) {
        return 0;
    }
    return s->stack[(s->top)--];
}

// 释放栈内存
// freeStack 函数用于释放栈的内存，并将栈的指针和指标重置。
void freeStack(Stack *s) {
    free(s->stack);
    s->stack = NULL;
    s->top = -1;
    s->capacity = 0;
}

// 陨石碰撞函数
// 碰撞逻辑
// 函数遍历每个陨石，对于每个陨石，如果栈不为空且栈顶陨石向右移动（正数）而当前陨石向左移动（负数），则可能发生碰撞。
// 如果两个陨石大小相等，则它们相互抵消，都从栈中移除。
// 如果当前陨石较大，则摧毁栈顶的陨石，继续检查下一个栈顶元素。
// 如果当前陨石较小或没有发生碰撞，则将当前陨石压入栈中。
int *asteroidCollision(int *asteroids, int asteroidsSize, int *returnSize) {
    Stack s;
    initStack(&s, asteroidsSize);

    for (int i = 0; i < asteroidsSize; ++i) {
        bool destroyed = false;
        while (!isEmpty(&s) && asteroids[i] < 0 && s.stack[s.top] > 0) {
            if (abs(asteroids[i]) == abs(s.stack[s.top])) {
                pop(&s);
                destroyed = true;
                break;
            } else if (abs(asteroids[i]) > abs(s.stack[s.top])) {
                pop(&s);
            } else {
                destroyed = true;
                break;
            }
        }
        if (!destroyed) {
            push(&s, asteroids[i]);
        }
    }

    // 计算返回数组的大小
    *returnSize = s.top + 1;
    int *result = (int *)malloc(*returnSize * sizeof(int));
    for (int i = 0; i < *returnSize; ++i) {
        result[i] = s.stack[i];
    }
    freeStack(&s);
    return result;
}

// 单元测试
void test() {
    int asteroids1[] = {5, 10, -5};
    int returnSize1;
    int *result1 = asteroidCollision(asteroids1, 3, &returnSize1);
    for (int i = 0; i < returnSize1; i++) {
        printf("%d ", result1[i]);
    }
    printf("\n");
    free(result1);

    int asteroids2[] = {8, -8};
    int returnSize2;
    int *result2 = asteroidCollision(asteroids2, 2, &returnSize2);
    for (int i = 0; i < returnSize2; i++) {
        printf("%d ", result2[i]);
    }
    printf("\n");
    free(result2);

    int asteroids3[] = {10, 2, -5};
    int returnSize3;
    int *result3 = asteroidCollision(asteroids3, 3, &returnSize3);
    for (int i = 0; i < returnSize3; i++) {
        printf("%d ", result3[i]);
    }
    printf("\n");
    free(result3);
}

int main() {
    test();
    return 0;
}

// ### 代码解释
// 1. **栈结构**: 使用一个栈来模拟陨石的碰撞过程。
// 2. **函数`asteroidCollision`**:
// 遍历每个陨石，使用栈来处理碰撞。如果当前陨石与栈顶陨石碰撞，根据规则处理碰撞。
// 3. **内存管理**: 使用 `malloc` 分配内存，并在函数结束时使用 `free`
// 释放内存，避免内存泄漏。
// 4. **单元测试**: `test` 函数用于验证 `asteroidCollision` 函数的正确性。

// 这个实现考虑了效率（使用栈来处理碰撞），内存泄漏（正确分配和释放内存），以及单元测试（验证函数的正确性）。
