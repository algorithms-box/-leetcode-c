#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <time.h>

char* toLowerCase(char* s){
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
	if (s[i] >= 'A' && s[i] <= 'Z') {
	    s[i] = s[i] + 'a' - 'A';
	}
    }
    return s;
}

void test() {
    char str1[] = "Hello";
    toLowerCase(str1);
    assert(strcmp(str1, "hello") == 0);

    char str2[] = "world";
    toLowerCase(str2);
    assert(strcmp(str2, "world") == 0);

    char str3[] = "LeetCode";
    toLowerCase(str3);
    assert(strcmp(str3, "leetcode") == 0);

    printf("All test passed.\n");
}

void performanceTest() {
    char* longStr = (char*)malloc(1000000 * sizeof(char));
    for (int i = 0; i < 999999; i++) {
	longStr[i] = 'A';
    }
    longStr[999999] = '\0';

    clock_t start = clock();
    toLowerCase(longStr);
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Performance Test Time: %f seconds\n", time_spent);

    free(longStr);
}

int main() {
    test();
    performanceTest();
    return 0;
}

