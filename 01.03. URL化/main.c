#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

#define MAX_LENGTH 500000

void replaceSpaces(char* S, int length) {
    if (S == NULL || length <= 0) {
        return;
    }

    int spaceCount = 0;
    for (int i = 0; i < length; i++) {
        if (S[i] == ' ') {
            spaceCount++;
        }
    }

    int newLength = length + spaceCount * 2;
    int j = newLength - 1;

    // Null-terminate the new string
    S[newLength] = '\0';

    // Start from the end of the original string
    for (int i = length - 1; i >= 0; i--) {
        if (S[i] == ' ') {
            S[j--] = '0';
            S[j--] = '2';
            S[j--] = '%';
        } else {
            S[j--] = S[i];
        }
    }
}

void test_replaceSpaces() {
    char s1[] = "Mr John Smith    ";
    replaceSpaces(s1, 13);
    assert(strcmp(s1, "Mr%20John%20Smith") == 0);

    char s2[] = "               ";
    replaceSpaces(s2, 5);
    assert(strcmp(s2, "%20%20%20%20%20") == 0);

    char s3[] = "a b c     ";
    replaceSpaces(s3, 5);
    assert(strcmp(s3, "a%20b%20c") == 0);

    char s4[] = "";
    replaceSpaces(s4, 0);
    assert(strcmp(s4, "") == 0);

    printf("All test cases passed!\n");
}

void performance_test() {
    char* long_string = (char*)malloc(MAX_LENGTH * 3 + 1); // Allocate enough space for worst case
    if (long_string == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    for (int i = 0; i < MAX_LENGTH; i++) {
        long_string[i] = i % 5 == 0 ? ' ' : 'a';
    }
    long_string[MAX_LENGTH] = '\0';

    clock_t start = clock();
    replaceSpaces(long_string, MAX_LENGTH);
    clock_t end = clock();

    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Performance test: %f seconds\n", cpu_time_used);

    free(long_string);
}

int main() {
    test_replaceSpaces();
    performance_test();
    return 0;
}
