#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

void reverseString(char* s, int sSize){
    int left = 0;
    int right = sSize - 1;

    while(left < right){
	char tmp = s[left];
	s[left] = s[right];
	s[right] = tmp;

	left++;
	right--;
    }
}

void test(){
    char str1[] = "hello";
    reverseString(str1, strlen(str1));
    assert(strcmp(str1, "olleh") == 0);

    char str2[] = "a";
    reverseString(str2, strlen(str2));
    assert(strcmp(str2, "a") == 0);

    char str3[] = "   ";
    reverseString(str3, strlen(str3));
    assert(strcmp(str3, "   ") == 0);

    printf("All tests passed.\n");
}

void performanceTest(){
    char* longStr = (char*)malloc(1000000 * sizeof(char));
    for(int i=0; i< 999999; i++){
	longStr[i] = 'a';
    }
    longStr[999999] = '\0';

    clock_t start = clock();
    reverseString(longStr, strlen(longStr));
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("performance testing time: %f seconds.\n", time_spent);

    free(longStr);
}

int main(){
    test();
    performanceTest();
    return 0;
}
