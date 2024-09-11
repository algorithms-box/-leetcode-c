#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) { return a > b ? a : b; }

int maxProfit(int *prices, int pricesSize) {
    if (pricesSize < 2)
        return 0;
    int n = pricesSize;
    int **dp = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        dp[i] = (int *)malloc(2 * sizeof(int));
        dp[i][0] = -prices[0]; // 第一天买入
        dp[i][1] = 0;          // 第一天不持股票
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j == 0) {
                dp[i][j] = max(dp[i][j], dp[i - 1][1] - prices[i]);
            } else {
                dp[i][j] = max(dp[i][j], dp[i - 1][0] + prices[i]);
            }
        }
    }

    int result = dp[n - 1][1];
    for (int i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

void test() {
    int prices1[] = {3, 2, 6, 5, 0, 3};
    assert(maxProfit(prices1, sizeof(prices1) / sizeof(prices1[0])) == 7);

    int prices2[] = {1, 2, 3, 4, 5};
    assert(maxProfit(prices2, sizeof(prices2) / sizeof(prices2[0])) == 4);

    int prices3[] = {7, 6, 4, 3, 1};
    assert(maxProfit(prices3, sizeof(prices3) / sizeof(prices3[0])) == 0);

    printf("All tests passed.\n");
}

int main() {
    test();
    return 0;
}