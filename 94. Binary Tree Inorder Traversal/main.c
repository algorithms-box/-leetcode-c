#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

#define MAX_SIZE 10000

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    int* result = malloc(sizeof(int) * MAX_SIZE);
    *returnSize = 0;

    if (!root) return result;

    struct TreeNode* stack[MAX_SIZE];
    int top = -1;
    struct TreeNode* current = root;

    while (current || top >= 0) {
	while (current) {
	    stack[++top] = current;
	    current = current->left;
	}

	current = stack[top--];
	result[(*returnSize)++] = current->val;
	current = current->right;
    }

    return result;
}

// Helper function to create a new node
struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Helper function to free the tree
void freeTree(struct TreeNode* root) {
    if (root) {
	freeTree(root->left);
	freeTree(root->right);
	free(root);
    }
}

// Unit test function
void testInorderTraversal() {
    struct TreeNode* root = newNode(1);
    root->right = newNode(2);
    root->right->left = newNode(3);

    int returnSize;
    int* result = inorderTraversal(root, &returnSize);

    assert(returnSize == 3);
    assert(result[0] == 1);
    assert(result[1] == 3);
    assert(result[2] == 2);

    free(result);
    freeTree(root);

    printf("Unit test passed successfully!\n");
}

// Performance test function
void performanceTest() {
    clock_t start, end;
    double cpu_time_used;
    int returnSize;

    // Create a large balanced binary tree
    struct TreeNode* root = newNode(1);
    struct TreeNode* current = root;
    for (int i = 2; i <= 10000; i++) {
	if (i % 2 == 0) {
	    current->left = newNode(i);
	    current = current->left;
	} else {
	    current->right = newNode(i);
	    current = current->right;
	}
    }

    start = clock();
    int* result = inorderTraversal(root, &returnSize);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Performance test: processed %d nodes in %f seconds\n", returnSize, cpu_time_used);

    free(result);
    freeTree(root);
}

int main() {
    testInorderTraversal();
    performanceTest();
    return 0;
}

