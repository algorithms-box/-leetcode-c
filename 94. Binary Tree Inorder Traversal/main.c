#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#define MAX_SIZE 10000

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
	int* result = malloc(sizeof(int) * MAX_SIZE);
	*returnSize = 0;

	if (!root) return result;

	struct TreeNode* stack[MAX_SIZE];
	int top = -1;
	struct TreeNode* current = root;

	while (current ||  top >=0) {
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

struct TreeNode* newNode(int val) {
	struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	node->val = val;
	node->left = NULL;
	node->right = NULL;
	return node;
}

void freeTree(struct TreeNode* root) {
	if (root) {
		freeTree(root->left);
		freeTree(root->right);
		free(root);
	}
}

void testInorderTraversal() {
	struct TreeNode* 
}
