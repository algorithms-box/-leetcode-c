#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char *longestCommonPrefix(char **strs, int strsSize) {
    if (strsSize == 0) {
        return "";
    }

    int minLength = strlen(strs[0]);
    for (int i = 1; i < strsSize; i++) {
        int len = strlen(strs[i]);
        if (len < minLength) {
            minLength = len;
        }
    }

    char *prefix = malloc(minLength + 1);
    prefix[minLength] = '\0';

    for (int i = 0; i < minLength; i++) {
        char c = strs[0][i];
        for (int j = 1; j < strsSize; j++) {
            if (strs[j][i] != c) {
                prefix[i] = '\0';
                return prefix;
            }
        }
        prefix[i] = c;
    }

    return prefix;
}

void testLongestCommonPrefix() {
    char *strs[] = {"flower", "flow", "flight"};
    char *result = longestCommonPrefix(strs, 3);
    assert(strcmp(result, "fl") == 0);
    printf("Test passed for 'flower', 'flow', 'flight'\n");
    free(result);

    strs[0] = "dog";
    strs[1] = "racecar";
    strs[2] = "car";
    result = longestCommonPrefix(strs, 3);
    assert(strcmp(result, "") == 0);
    printf("Test passed for 'dog', 'racecar', 'car'\n");
    free(result);

    strs[0] = "aa";
    strs[1] = "aabbcc";
    strs[2] = "aabbccdd";
    result = longestCommonPrefix(strs, 3);
    assert(strcmp(result, "aa") == 0);
    printf("Test passed for 'aa', 'aabbcc', 'aabbccdd'\n");
    free(result);
}

void performanceTestLongestCommonPrefix() {
    int n = 10000;
    char **strs = malloc(n * sizeof(char *));
    for (int i=0; i<n; i++){
	int length = rand() % 10 + 1;
	strs[i] = malloc(length + 1);
	for (int j = 0; j < length; j++){
	    strs[i][j] = 'a' + rand() % 26;
	}
	strs[i][length] = '\0';
    }

    char *result = longestCommonPrefix(strs, n);
    assert(strlen(result) == 0);
    printf("Performance Test passed\n");
    free(strs);
}

int main() {
    testLongestCommonPrefix();
    performanceTestLongestCommonPrefix();
    return 0;
}
