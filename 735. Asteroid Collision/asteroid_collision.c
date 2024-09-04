#include <stdio.h>
#include <stdlib.h>

// 定义小行星的结构体
typedef struct Asteroid {
    int val;
    struct Asteroid *next;
} Asteroid;

// 创建一个新的小行星节点
Asteroid *createAsteroid(int val) {
    Asteroid *newAsteroid = (Asteroid *)malloc(sizeof(Asteroid));
    if (newAsteroid == NULL) {
        return NULL;
    }
    newAsteroid->val = val;
    newAsteroid->next = NULL;
    return newAsteroid;
}

// 释放小行星链表
void freeAsteroids(Asteroid *head) {
    while (head != NULL) {
        Asteroid *temp = head;
        head = head->next;
        free(temp);
    }
}

// 处理小行星碰撞
void asteroidCollision(Asteroid **head) {
    Asteroid *current = *head;
    Asteroid *prev = NULL;

    while (current != NULL && current->next != NULL) {
        if (current->val < 0 && current->next->val > 0) {
            // 碰撞发生
            if (current->val + current->next->val < 0) {
                // 当前小行星爆炸
                Asteroid *toFree = current->next;
                current->next = current->next->next;
                free(toFree);
            } else if (current->val + current->next->val > 0) {
                // 下一个小行星爆炸
                Asteroid *toFree = current->next;
                current->next = current->next->next;
                free(toFree);
            } else {
                // 两者都爆炸
                Asteroid *toFree = current->next;
                current->next = current->next->next;
                free(toFree);
                prev->next = current->next;
                free(current);
                current = prev->next;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
    *head = prev; // 更新头指针
}

// 单元测试
void testAsteroidCollision() {
    Asteroid *head = createAsteroid(5);
    head->next = createAsteroid(10);
    head->next->next = createAsteroid(-5);

    asteroidCollision(&head);

    // 打印结果
    for (Asteroid *p = head; p != NULL; p = p->next) {
        printf("%d ", p->val);
    }
    printf("\n");

    // 释放小行星链表
    freeAsteroids(head);
}

int main() {
    testAsteroidCollision();
    return 0;
}