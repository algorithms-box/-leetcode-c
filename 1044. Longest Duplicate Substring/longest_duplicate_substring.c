#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MOD 1000000007
#define BASE 26

typedef unsigned long long ull;

char *longestDupSubstring(char *s) {
    int n = strlen(s);
    ull *hash = (ull *)malloc(sizeof(ull) * (n + 1));
    ull *power = (ull *)malloc(sizeof(ull) * (n + 1));

    // Check for malloc failure
    if (!hash || !power) {
        free(hash);
        free(power);
        return NULL;
    }

    // Precompute hash values and powers
    hash[0] = 0;
    power[0] = 1;
    for (int i = 1; i <= n; i++) {
        hash[i] = (hash[i - 1] * BASE + (s[i - 1] - 'a')) % MOD;
        power[i] = (power[i - 1] * BASE) % MOD;
    }

    int left = 1, right = n;
    int start = 0, max_len = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int found = 0;

        for (int i = 0; i + mid <= n; i++) {
            ull curr_hash = (hash[i + mid] - hash[i] + MOD) % MOD;
            if (i > 0) {
                curr_hash = (curr_hash + MOD * power[mid]) % MOD;
            }
            for (int j = i + 1; j + mid <= n; j++) {
                ull next_hash = (hash[j + mid] - hash[j] + MOD) % MOD;
                if (curr_hash == next_hash && strncmp(s + i, s + j, mid) == 0) {
                    found = 1;
                    if (mid > max_len) {
                        max_len = mid;
                        start = i;
                    }
                    break;
                }
            }
            if (found)
                break;
        }

        if (found) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    free(hash);
    free(power);

    if (max_len == 0)
        return "";

    char *result = (char *)malloc(sizeof(char) * (max_len + 1));
    if (!result)
        return NULL; // Check for malloc failure

    strncpy(result, s + start, max_len);
    result[max_len] = '\0';
    return result;
}

void runTests() {
    char *result;

    result = longestDupSubstring("banana");
    assert(strcmp(result, "ana") == 0);
    free(result);

    result = longestDupSubstring("abcd");
    assert(strcmp(result, "") == 0);
    free(result);

    result = longestDupSubstring("aaaaa");
    assert(strcmp(result, "aaaa") == 0);
    free(result);

    printf("All tests passed!\n");
}

void performanceTest() {
    int size = 100000;
    char *s = (char *)malloc(sizeof(char) * (size + 1));
    if (!s)
        return; // Check for malloc failure

    for (int i = 0; i < size; i++) {
        s[i] = 'a' + (rand() % 26);
    }
    s[size] = '\0';

    clock_t start = clock();
    char *result = longestDupSubstring(s);
    clock_t end = clock();

    if (result) {
        printf("Performance test result length: %lu\n", strlen(result));
        free(result);
    }
    printf("Time taken: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(s);
}

int main() {
    runTests();
    performanceTest();
    return 0;
}