#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NODES 1000

typedef struct {
    int u, v;
    int weight;
} Edge;

typedef struct {
    int parent;
    int rank;
} Node;

Node nodes[MAX_NODES];
Edge edges[MAX_NODES * (MAX_NODES - 1) / 2];
int edge_count = 0;

// 路径压缩的查找操作
int find(int i) {
    if (nodes[i].parent != i)
        nodes[i].parent = find(nodes[i].parent);
    return nodes[i].parent;
}

// 按秩合并的并集操作
void union_set(int a, int b) {
    int x = find(a);
    int y = find(b);
    if (x == y)
        return;
    if (nodes[x].rank < nodes[y].rank)
        nodes[x].parent = y;
    else if (nodes[x].rank > nodes[y].rank)
        nodes[y].parent = x;
    else {
        nodes[y].parent = x;
        nodes[x].rank++;
    }
}

// 用于qsort的比较函数
int compare_edges(const void *a, const void *b) {
    return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

int minimum_spanning_tree(int n) {
    // 初始化并查集
    for (int i = 0; i < n; i++) {
        nodes[i].parent = i;
        nodes[i].rank = 0;
    }

    qsort(edges, edge_count, sizeof(Edge), compare_edges);

    int total_cost = 0;
    int edges_used = 0;

    for (int i = 0; i < edge_count && edges_used < n - 1; i++) {
        if (find(edges[i].u) != find(edges[i].v)) {
            union_set(edges[i].u, edges[i].v);
            total_cost += edges[i].weight;
            edges_used++;
            printf("Added edge: %d - %d (weight: %d)\n", edges[i].u, edges[i].v,
                   edges[i].weight);
        }
    }

    assert(edges_used == n - 1); // 确保MST有n-1条边
    return total_cost;
}

void add_edge(int u, int v, int weight) {
    edges[edge_count].u = u;
    edges[edge_count].v = v;
    edges[edge_count++].weight = weight;
}

#ifdef MAIN_TEST
int main() {
    int n = 4;
    edge_count = 0; // 重置边计数

    add_edge(0, 1, 1);
    add_edge(1, 2, 2);
    add_edge(2, 3, 3);
    add_edge(0, 3, 4);
    add_edge(0, 2, 5);
    add_edge(1, 3, 6);

    printf("Edges:\n");
    for (int i = 0; i < edge_count; i++) {
        printf("%d - %d: %d\n", edges[i].u, edges[i].v, edges[i].weight);
    }

    int total_cost = minimum_spanning_tree(n);
    printf("Total cost: %d\n", total_cost);
    assert(total_cost == 6); // 最小生成树的总成本应该是6

    printf("Test passed successfully!\n");
    return 0;
}
#endif

#ifdef MAIN_PERFORMANCE
int main() {
    srand(time(NULL)); // 初始化随机数生成器
    int n = 1000;      // 增加节点数以进行更严格的性能测试

    // 生成完全图
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            add_edge(i, j, rand() % 1000 + 1); // 权重范围1-1000
        }
    }

    clock_t start = clock();
    int total_cost = minimum_spanning_tree(n);
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Nodes: %d\n", n);
    printf("Edges: %d\n", edge_count);
    printf("Total cost: %d\n", total_cost);
    printf("Time spent: %f seconds\n", time_spent);

    return 0;
}
#endif