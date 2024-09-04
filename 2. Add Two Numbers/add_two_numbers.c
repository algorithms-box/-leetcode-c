#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *createListNode(int val) {
    struct ListNode *node = (struct ListNode *)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2) {
    int carry = 0;
    struct ListNode *dummyHead = createListNode(0), *p = dummyHead;
    while (l1 || l2 || carry) {
        int x = l1 ? l1->val : 0;
        int y = l2 ? l2->val : 0;
        int sum = x + y + carry;
        p->next = createListNode(sum % 10);
        carry = sum / 10;
        p = p->next;
        if (l1)
            l1 = l1->next;
        if (l2)
            l2 = l2->next;
    }
    return dummyHead->next;
}

void printList(struct ListNode *node) {
    while (node != NULL) {
        printf("%d", node->val);
        if (node->next != NULL) {
            printf(" -> ");
        }
        node = node->next;
    }
    printf(" -> NULL\n");
}

void freeList(struct ListNode *node) {
    while (node != NULL) {
        struct ListNode *temp = node;
        node = node->next;
        free(temp);
    }
}

int listEquals(struct ListNode *l1, struct ListNode *l2) {
    while (l1 && l2) {
        if (l1->val != l2->val)
            return 0;
        l1 = l1->next;
        l2 = l2->next;
    }
    return (l1 == NULL && l2 == NULL);
}

// 单元测试函数
int testAddTwoNumbers() {
    // Test case 1: l1 = [2,4,3], l2 = [5,6,4]
    struct ListNode *l1_1 = createListNode(2);
    l1_1->next = createListNode(4);
    l1_1->next->next = createListNode(3);
    struct ListNode *l2_1 = createListNode(5);
    l2_1->next = createListNode(6);
    l2_1->next->next = createListNode(4);
    struct ListNode *result_1 = addTwoNumbers(l1_1, l2_1);

    printList(l1_1);
    printList(l2_1);
    printList(result_1);

    struct ListNode *expected_1 = createListNode(7);
    expected_1->next = createListNode(0);
    expected_1->next->next = createListNode(8);
    if (!listEquals(result_1, expected_1)) {
        printf("Test case 1 failed\n");
        return 0;
    }
    printf("Test case 1 passed\n");

    // Test case 2: l1 = [0], l2 = [0]
    struct ListNode *l1_2 = createListNode(0);
    struct ListNode *l2_2 = createListNode(0);
    struct ListNode *result_2 = addTwoNumbers(l1_2, l2_2);

    printList(l1_2);
    printList(l2_2);
    printList(result_2);

    struct ListNode *expected_2 = createListNode(0);
    if (!listEquals(result_2, expected_2)) {
        printf("Test case 2 failed\n");
        return 0;
    }
    printf("Test case 2 passed\n");

    // Additional test cases...

    // Free lists
    freeList(l1_1);
    freeList(l2_1);
    freeList(result_1);
    freeList(l1_2);
    freeList(l2_2);
    freeList(result_2);

    return 1;
}

int main() {
    if (!testAddTwoNumbers()) {
        printf("AddTwoNumbers test failed\n");
        return 1;
    }
    printf("All AddTwoNumbers tests passed\n");
    return 0;
}