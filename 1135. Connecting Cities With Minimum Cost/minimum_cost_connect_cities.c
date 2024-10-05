#if defined(__GNUC__) || defined(__clang__)
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CITIES 1001

typedef struct {
    int city1;
    int city2;
    int cost;
} Connection;

int parent[MAX_CITIES];
int rank[MAX_CITIES];

void init(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    int px = find(x), py = find(y);
    if (px == py)
        return;
    if (rank[px] < rank[py]) {
        parent[px] = py;
    } else {
        parent[py] = px;
        if (rank[px] == rank[py]) {
            rank[px]++;
        }
    }
}

int compare(const void *a, const void *b) {
    return ((Connection *)a)->cost - ((Connection *)b)->cost;
}

int minimumCost(int n, int **connections, int connectionsSize,
                UNUSED int *connectionsColSize) {
    if (connectionsSize < n - 1)
        return -1;

    Connection *conns =
        (Connection *)malloc(connectionsSize * sizeof(Connection));
    for (int i = 0; i < connectionsSize; i++) {
        conns[i].city1 = connections[i][0];
        conns[i].city2 = connections[i][1];
        conns[i].cost = connections[i][2];
    }

    qsort(conns, connectionsSize, sizeof(Connection), compare);

    init(n);

    int total_cost = 0;
    int connected_cities = 0;

    for (int i = 0; i < connectionsSize && connected_cities < n - 1; i++) {
        int city1 = conns[i].city1;
        int city2 = conns[i].city2;
        if (find(city1) != find(city2)) {
            unite(city1, city2);
            total_cost += conns[i].cost;
            connected_cities++;
        }
    }

    free(conns);

    return (connected_cities == n - 1) ? total_cost : -1;
}

// Unit tests
void test_minimumCost() {
    int n1 = 3;
    int connections1[][3] = {{1, 2, 5}, {1, 3, 6}, {2, 3, 1}};
    int *conn_ptrs1[3];
    for (int i = 0; i < 3; i++)
        conn_ptrs1[i] = connections1[i];
    int colSize1 = 3;
    assert(minimumCost(n1, conn_ptrs1, 3, &colSize1) == 6);

    int n2 = 4;
    int connections2[][3] = {{1, 2, 3}, {3, 4, 4}};
    int *conn_ptrs2[2];
    for (int i = 0; i < 2; i++)
        conn_ptrs2[i] = connections2[i];
    int colSize2 = 3;
    assert(minimumCost(n2, conn_ptrs2, 2, &colSize2) == -1);

    printf("All tests passed!\n");
}

// Performance test
void performance_test() {
    int n = 1000;
    int connectionsSize = 100000;
    int **connections = (int **)malloc(connectionsSize * sizeof(int *));
    for (int i = 0; i < connectionsSize; i++) {
        connections[i] = (int *)malloc(3 * sizeof(int));
        connections[i][0] = rand() % n + 1;
        connections[i][1] = rand() % n + 1;
        connections[i][2] = rand() % 1000 + 1;
    }
    int colSize = 3;

    clock_t start = clock();
    int result = minimumCost(n, connections, connectionsSize, &colSize);
    clock_t end = clock();

    printf("Performance test result: %d\n", result);
    printf("Performance test Time taken: %f seconds\n",
           (double)(end - start) / CLOCKS_PER_SEC);

    for (int i = 0; i < connectionsSize; i++) {
        free(connections[i]);
    }
    free(connections);
}

int main() {
    test_minimumCost();
    performance_test();
    return 0;
}