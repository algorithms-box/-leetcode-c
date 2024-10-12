#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

void process_numbers(int n, int *numbers, int *negative_count, double *positive_average);
void run_unit_tests();
void run_performance_test();

int main() {
    int n;
    scanf("%d", &n);

    int *numbers = (int *)malloc(n * sizeof(int));
    if (numbers == NULL) {
	fprintf(stderr, "Memory allocation failed\n");
	return 1;
    }

    for (int i = 0; i < n; i++) {
	scanf("%d", &numbers[i]);  // Fixed: Added & before numbers[i]
    }

    int negative_count = 0;
    double positive_average = 0.0;

    process_numbers(n, numbers, &negative_count, &positive_average);

    printf("%d %.1f\n", negative_count, positive_average);  // Fixed: positive_average is now double

    free(numbers);

    // Run tests
    run_unit_tests();
    run_performance_test();

    return 0;
}

void process_numbers(int n, int *numbers, int *negative_count, double *positive_average) {
    int positive_count = 0;
    int positive_sum = 0;
    *negative_count = 0;

    for (int i = 0; i < n; i++) {
	if (numbers[i] < 0) {
	    (*negative_count)++;
	} else if (numbers[i] > 0) {
	    positive_count++;
	    positive_sum += numbers[i];
	}
    }

    *positive_average = (positive_count > 0) ? (double)positive_sum / positive_count : 0.0;
}

void run_unit_tests() {
    int test_numbers1[] = {1, -2, 3, 0, -4, 5};
    int negative_count1 = 0;
    double positive_average1 = 0.0;
    process_numbers(6, test_numbers1, &negative_count1, &positive_average1);
    assert(negative_count1 == 2);
    assert(positive_average1 == 3.0);

    int test_numbers2[] = {-1, -2, -3};
    int negative_count2 = 0;
    double positive_average2 = 0.0;
    process_numbers(3, test_numbers2, &negative_count2, &positive_average2);
    assert(negative_count2 == 3);
    assert(positive_average2 == 0.0);

    int test_numbers3[] = {0, 0, 0};
    int negative_count3 = 0;
    double positive_average3 = 0.0;
    process_numbers(3, test_numbers3, &negative_count3, &positive_average3);
    assert(negative_count3 == 0);
    assert(positive_average3 == 0.0);

    printf("All unit tests passed!\n");
}

void run_performance_test() {
    const int TEST_SIZE = 2000;
    int *large_test = (int *)malloc(TEST_SIZE * sizeof(int));
    if (large_test == NULL) {
	fprintf(stderr, "Memory allocation failed in performance test\n");
	return;
    }

    for (int i = 0; i < TEST_SIZE; i++) {
	large_test[i] = rand() % 2001 - 1000;  // Random numbers between -1000 and 1000
    }

    clock_t start = clock();
    int negative_count;
    double positive_average;
    for (int i = 0; i < 1000; i++) {  // Run the function 1000 times
	process_numbers(TEST_SIZE, large_test, &negative_count, &positive_average);
    }
    clock_t end = clock();

    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Performance test: %f seconds for 1000 iterations with 2000 numbers each\n", cpu_time_used);

    free(large_test);
}

