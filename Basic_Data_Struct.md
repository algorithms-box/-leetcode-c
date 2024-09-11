在C语言中，数据结构通常需要手动实现。以下是一些基本的数据结构的C语言实现和初始化示例：

1. **数组**:

```c
#include <stdio.h>

int main() {
    int array[5] = {1, 2, 3, 4, 5}; // 初始化数组
    for (int i = 0; i < 5; i++) {
        printf("%d ", array[i]);
    }
    return 0;
}
```

2. **哈希表（HashMap）**:
C语言没有内置的哈希表，但可以使用结构体和数组来模拟。

```c
#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

typedef struct {
    int key;
    int value;
} Entry;

typedef struct {
    Entry *table[TABLE_SIZE];
} HashMap;

void initHashMap(HashMap *map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        map->table[i] = NULL;
    }
}

int hash(int key) {
    return key % TABLE_SIZE;
}

void insert(HashMap *map, int key, int value) {
    int index = hash(key);
    Entry *entry = map->table[index];
    if (entry == NULL) {
        entry = (Entry *)malloc(sizeof(Entry));
        entry->key = key;
        entry->value = value;
        map->table[index] = entry;
    } else {
        // Handle collision
    }
}

int main() {
    HashMap map;
    initHashMap(&map);
    insert(&map, 1, 100);
    insert(&map, 2, 200);
    // Access and print values...
    return 0;
}
```

3. **单链表**:

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void append(Node **head, int data) {
    Node *newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void printList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
}

int main() {
    Node *head = NULL;
    append(&head, 1);
    append(&head, 2);
    append(&head, 3);
    printList(head);
    return 0;
}
```

4. **双链表**:

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void append(Node **head, int data) {
    Node *newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
    }
}

void printList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
}

int main() {
    Node *head = NULL;
    append(&head, 1);
    append(&head, 2);
    append(&head, 3);
    printList(head);
    return 0;
}
```

5. **队列**:

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Queue {
    int *elements;
    int front;
    int rear;
    int size;
} Queue;

Queue* createQueue(int size) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->elements = (int *)malloc(size * sizeof(int));
    q->front = -1;
    q->rear = -1;
    q->size = size;
    return q;
}

void enqueue(Queue *q, int data) {
    if (q->rear == q->size - 1) {
        printf("Queue is full\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->elements[q->rear] = data;
}

int dequeue(Queue *q) {
    if (q->front == -1) {
        printf("Queue is empty\n");
        return -1;
    }
    int data = q->elements[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return data;
}

int main() {
    Queue *q = createQueue(5);
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    printf("%d ", dequeue(q));
    printf("%d ", dequeue(q));
    return 0;
}
```

6. **栈**:

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    int *elements;
    int top;
    int size;
} Stack;

Stack* createStack(int size) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->elements = (int *)malloc(size * sizeof(int));
    s->top = -1;
    s->size = size;
    return s;
}

void push(Stack *s, int data) {
    if (s->top == s->size - 1) {
        printf("Stack is full\n");
        return;
    }
    s->top++;
    s->elements[s->top] = data;
}

int pop(Stack *s) {
    if (s->top == -1) {
        printf("Stack is empty\n");
        return -1;
    }
    int data = s->elements[s->top];
    s->top--;
    return data;
}

int main() {
    Stack *s = createStack(5);
    push(s, 1);
    push(s, 2);
    push(s, 3);
    printf("%d ", pop(s));
    printf("%d ", pop(s));
    return 0;
}
```

7. **堆**:
C语言没有内置的堆数据结构，但可以使用数组来模拟。

```c
#include <stdio.h>
#include <stdlib.h>

void heapify(int *arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void buildHeap(int *arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

int main() {
    int arr[] = {1, 12, 9, 5, 6, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    buildHeap(arr, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}
```

8. **二叉树**:

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* createNode(int data) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void insert(TreeNode **root, int data) {
    if (*root == NULL) {
        *root = createNode(data);
    } else {
        if (data < (*root)->data) {
            insert(&((*root)->left), data);
        } else {
            insert(&((*root)->right), data);
        }
    }
}

void printInOrder(TreeNode *root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("%
d ", root->data);
        printInOrder(root->right);
    }
}

int main() {
    TreeNode *root = NULL;
    insert(&root, 8);
    insert(&root, 3);
    insert(&root, 10);
    insert(&root, 1);
    insert(&root, 6);
    insert(&root, 4);
    insert(&root, 7);
    insert(&root, 14);
    insert(&root, 13);
    printInOrder(root);
    return 0;
}
```

9. **完美二叉树**:
完美二叉树通常是指满二叉树，每个节点都有两个子节点。在C语言中，可以通过二叉树的特定实现来创建完美二叉树。

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* createPerfectTree(int data[], int index, int n) {
    if (index >= n) {
        return NULL;
    }
    TreeNode *node = createNode(data[index]);
    node->left = createPerfectTree(data, 2 * index + 1, n);
    node->right = createPerfectTree(data, 2 * index + 2, n);
    return node;
}

void printInOrder(TreeNode *root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("%d ", root->data);
        printInOrder(root->right);
    }
}

int main() {
    int data[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(data) / sizeof(data[0]);
    TreeNode *root = createPerfectTree(data, 0, n);
    printInOrder(root);
    return 0;
}
````

请注意，这些代码示例仅用于演示目的，实际应用中可能需要更多的错误检查和内存管理。
