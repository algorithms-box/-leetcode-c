#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) { return a > b ? a : b; }

int maxProfit(int *prices, int pricesSize, int k) {
    if (pricesSize <= 1)
        return 0;
    int max_k = (pricesSize + 1) / 2; // 最大交易次数
    if (k > max_k)
        k = max_k;

    int **dp = (int **)malloc(pricesSize * sizeof(int *));
    for (int i = 0; i < pricesSize; i++) {
        dp[i] = (int *)malloc((k + 1) * sizeof(int));
        for (int j = 0; j <= k; j++) {
            dp[i][j] = 0;
        }
    }

    for (int j = 1; j <= k; j++) {
        int maxDiff = -prices[0];
        for (int i = 1; i < pricesSize; i++) {
            dp[i][j] = max(dp[i - 1][j], prices[i] + maxDiff);
            maxDiff = max(maxDiff, dp[i - 1][j - 1] - prices[i]);
        }
    }

    int result = 0;
    for (int i = 0; i < pricesSize; i++) {
        result = max(result, dp[i][k]);
    }

    for (int i = 0; i < pricesSize; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

void test() {
    int prices1[] = {7, 1, 5, 3, 6, 4};
    assert(maxProfit(prices1, sizeof(prices1) / sizeof(prices1[0]), 2) == 7);

    int prices2[] = {1, 2, 3, 4, 5};
    assert(maxProfit(prices2, sizeof(prices2) / sizeof(prices2[0]), 1) == 4);

    int prices3[] = {7, 6, 4, 3, 1};
    assert(maxProfit(prices3, sizeof(prices3) / sizeof(prices3[0]), 2) == 0);

    printf("All tests passed.\n");
}

int main() {
    test();
    return 0;
}