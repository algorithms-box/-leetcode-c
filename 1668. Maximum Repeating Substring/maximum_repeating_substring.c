#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>


int maxRepeating(char* sequence, char* word) {
    int seq_len = strlen(sequence);
    int word_len = strlen(word);
    if (seq_len == 0 || word_len == 0 || word_len > seq_len) {
	return 0;
    }

    int max_repeat = 0;
    char* buffer = (char*)malloc((seq_len + 1) * sizeof(char));
    if (buffer == NULL) {
	return 0;  // Memory allocation failed
    }

    for (int i = 0; i < seq_len; i++) {
	int count = 0;
	strcpy(buffer, word);
	while (strncmp(sequence + i, buffer, strlen(buffer)) == 0) {
	    count++;
	    strcat(buffer, word);
	}
	if (count > max_repeat) {
	    max_repeat = count;
	}
    }

    free(buffer);
    return max_repeat;
}

void test_maxRepeating() {
    assert(maxRepeating("ababc", "ab") == 2);
    assert(maxRepeating("ababc", "ba") == 1);
    assert(maxRepeating("ababc", "ac") == 0);
    assert(maxRepeating("aaabaaaabaaabaaaabaaaabaaaaba", "aaaba") == 4);
    assert(maxRepeating("", "a") == 0);
    assert(maxRepeating("a", "") == 0);
    printf("All tests passed!\n");
}

void performance_test() {
    const int SEQ_LEN = 1000000;
    const int WORD_LEN = 100000;

    char* long_sequence = (char*)malloc((SEQ_LEN + 1) * sizeof(char));
    if (long_sequence == NULL) {
	printf("Memory allocation failed for long_sequence in performance test\n");
	return;
    }

    char* long_word = (char*)malloc((WORD_LEN + 1) * sizeof(char));
    if (long_word == NULL) {
	printf("Memory allocation failed for long_word in performance test\n");
	free(long_sequence);
	return;
    }

    // Fill long_sequence with 'a's and long_word with 'a's
    memset(long_sequence, 'a', SEQ_LEN);
    long_sequence[SEQ_LEN] = '\0';
    memset(long_word, 'a', WORD_LEN);
    long_word[WORD_LEN] = '\0';

    clock_t start = clock();
    int result = maxRepeating(long_sequence, long_word);
    clock_t end = clock();

    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Performance test result: %d\n", result);
    printf("Time taken: %f seconds\n", cpu_time_used);

    free(long_sequence);
    free(long_word);
}

int main() {
    test_maxRepeating();
    performance_test();
    return 0;
}
