#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 辅助函数，用于递归计算树的最大深度
int maxDepth(TreeNode *root) {
    if (root == NULL) {
        return 0;
    }
    int leftDepth = maxDepth(root->left);
    int rightDepth = maxDepth(root->right);
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

// 辅助函数，用于创建新节点
TreeNode *newNode(int val) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 辅助函数，用于释放树内存
void freeTree(TreeNode *root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void test() {
    TreeNode *root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    assert(maxDepth(root) == 3);
    freeTree(root);

    root = newNode(1);
    assert(maxDepth(root) == 1);
    freeTree(root);

    root = NULL;
    assert(maxDepth(root) == 0);

    printf("All tests passed.\n");
}

int main() {
    test();
    return 0;
}