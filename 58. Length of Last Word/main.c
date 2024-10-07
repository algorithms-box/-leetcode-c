#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>

int lengthofLastWord(char *s){
    int len = strlen(s);
    int count = 0;
    int inWord = 0;

    for(int i = len - 1 ; i >=0; i--){
	if (s[i] != ' '){
	    inWord = 1;
	    count++;
	}else if (s[i] == ' ' && inWord){
	    break;
	}
    }

    return count ? count : 0;
}

void test(){
    assert(lengthofLastWord("Hello world") == 5);
    assert(lengthofLastWord("    file asjdifo  asdojfjao    world") == 5);
    assert(lengthofLastWord("sdjfoa   wld   ") == 3);
    assert(lengthofLastWord("a") == 1);
    assert(lengthofLastWord("") == 0);
    assert(lengthofLastWord("    ") == 0);
    printf("All tests passed.\n");

}

void performanceTest(){
    char longStr[1000000];
    for( int i = 0; i < 999999; i++){
	longStr[i] = 'a';
    }
    longStr[999999] = '\0';

    clock_t start = clock();
    lengthofLastWord(longStr);
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Performance Test Time: %f seconds.\n", time_spent);
}

int main(){
    test();
    performanceTest();
    return 0;
}
