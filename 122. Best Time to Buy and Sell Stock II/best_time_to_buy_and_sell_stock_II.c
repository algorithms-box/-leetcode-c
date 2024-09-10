#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) { return a > b ? b : a; }
int max(int a, int b) { return a > b ? a : b; }

int maxProfit(int *prices, int pricesSize) {
    int minPrice = prices[0];
    int maxPro = 0;

    for (int i = 0; i < pricesSize; i++) {
        minPrice = min(minPrice, prices[i]);
        maxPro = max(maxPro, prices[i] - minPrice);
        printf("%d\t%d\t%d\n", i, minPrice, maxPro);
    }

    return maxPro;
}

void testMaxProfit() {
    int prices1[] = {7, 1, 5, 3, 6, 4};
    assert(maxProfit(prices1, sizeof(prices1) / sizeof(prices1[0])) == 5);

    int prices2[] = {7, 6, 4, 3, 1};
    assert(maxProfit(prices2, sizeof(prices2) / sizeof(prices2[0])) == 0);

    int prices3[] = {1, 2, 3, 4, 5};
    assert(maxProfit(prices3, sizeof(prices3) / sizeof(prices3[0])) == 4);

    printf("All tests passed.\n");
}

int main() {
    testMaxProfit();
    return 0;
}