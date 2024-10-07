#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <time.h>

bool canConstruct(char* ransomNote, char* magazine){
    int count[256] = {0};
    int rnLen = strlen(ransomNote);
    int mgLen = strlen(magazine);

    for(int i =0; i< mgLen; i++){
	count[(char)magazine[i]]++;
    }

    for(int i =0; i< rnLen; i++){
	if (count[(char)ransomNote[i]] == 0){
	    return false;
	}
	count[(char)ransomNote[i]]--;
    }

    return true;
}

void test() {
    assert(canConstruct("a", "b") == false);
    assert(canConstruct("aa", "ab") == false);
    assert(canConstruct("aa", "aab") == true);

    printf("All tests passed.\n");
}

void performanTest() {
    char* longRansomNote = (char*)malloc(1000000 * sizeof(char));
    char* longMagazine = (char*)malloc(1100000 * sizeof(char));

    for(int i=0; i< 1000000; i++){
	longRansomNote[i] = 'a';
    }
    longRansomNote[1000000] = '\0';

    for(int i=0; i< 1100000; i++){
	longMagazine[i] = 'a';
    }
    longMagazine[1100000] = '\0';

    clock_t start = clock();
    canConstruct(longRansomNote, longMagazine);
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Performance Test Time: %f seconds\n", time_spent);

    free(longRansomNote);
    free(longMagazine);
}

int main(){
    test();
    performanTest();
    return 0;
}
