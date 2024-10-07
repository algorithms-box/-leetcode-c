#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#define MAX_LENGTH 100

int minimizedStringLength(char* s) {
    int char_set[26] = {0};
    int len = 0;
    
    for (int i = 0; s[i] != '\0'; i++) {
        if (char_set[s[i] - 'a'] == 0) {
            char_set[s[i] - 'a'] = 1;
            len++;
        }
    }
    
    return len;
}

void test_minimizedStringLength() {
    char s1[] = "aaabc";
    assert(minimizedStringLength(s1) == 3);
    
    char s2[] = "cbbd";
    assert(minimizedStringLength(s2) == 3);
    
    char s3[] = "dddaaa";
    assert(minimizedStringLength(s3) == 2);
    
    char s4[] = "abcdefghijklmnopqrstuvwxyz";
    assert(minimizedStringLength(s4) == 26);
    
    char s5[] = "";
    assert(minimizedStringLength(s5) == 0);
    
    char s6[] = "aabbccddeffghh";
    assert(minimizedStringLength(s6) == 8);
    
    printf("All test cases passed!\n");
}

void performance_test() {
    char long_string[MAX_LENGTH + 1];
    for (int i = 0; i < MAX_LENGTH; i++) {
        long_string[i] = 'a' + (i % 26);
    }
    long_string[MAX_LENGTH] = '\0';
    
    clock_t start = clock();
    for (int i = 0; i < 1000000; i++) {
        minimizedStringLength(long_string);
    }
    clock_t end = clock();
    
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Performance test: %f seconds\n", cpu_time_used);
}

int main() {
    test_minimizedStringLength();
    performance_test();
    return 0;
}
