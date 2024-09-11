#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

int globalMax = INT_MIN;

// 辅助函数，用于递归计算最大路径和
int maxPathSumHelper(TreeNode *root) {
    if (!root)
        return 0;

    int leftMax = maxPathSumHelper(root->left);
    int rightMax = maxPathSumHelper(root->right);

    int maxSingle = root->val;
    if (root->left)
        maxSingle += (leftMax < 0 ? 0 : leftMax);
    if (root->right)
        maxSingle += (rightMax < 0 ? 0 : rightMax);

    globalMax = (globalMax < maxSingle ? maxSingle : globalMax);

    return (leftMax > 0 && rightMax > 0
                ? root->val + leftMax + rightMax
                : (root->val + (leftMax > rightMax ? leftMax : rightMax)));
}

int maxPathSum(TreeNode *root) {
    globalMax = INT_MIN;
    maxPathSumHelper(root);
    return globalMax;
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
    root->left->left = newNode(-1);
    root->left->right = newNode(3);
    root->right->right = newNode(2);
    assert(maxPathSum(root) == 6);
    freeTree(root);

    root = newNode(5);
    root->left = newNode(4);
    root->right = newNode(8);
    root->left->left = newNode(11);
    root->left->right = newNode(7);
    root->right->left = newNode(4);
    root->right->right = newNode(5);
    assert(maxPathSum(root) == 23);
    freeTree(root);

    printf("All tests passed.\n");
}

int main() {
    test();
    return 0;
}