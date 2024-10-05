#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int count;
} Foo;

void first(Foo *obj);
void second(Foo *obj);
void third(Foo *obj);
void *thread_func(void *arg);

Foo *fooCreate() {
    Foo *obj = (Foo *)malloc(sizeof(Foo));
    if (obj == NULL) {
        return NULL;
    }
    pthread_mutex_init(&obj->mutex, NULL);
    pthread_cond_init(&obj->cond, NULL);
    obj->count = 0;
    return obj;
}

void printFirst() { printf("first"); }

void printSecond() { printf("second"); }

void printThird() { printf("third"); }

void first(Foo *obj) {
    pthread_mutex_lock(&obj->mutex);
    printFirst();
    obj->count++;
    pthread_cond_signal(&obj->cond);
    pthread_mutex_unlock(&obj->mutex);
    printf("Thread 1 finished\n");
}

void second(Foo *obj) {
    pthread_mutex_lock(&obj->mutex);
    while (obj->count < 1) {
        pthread_cond_wait(&obj->cond, &obj->mutex);
    }
    printSecond();
    obj->count++;
    pthread_cond_signal(&obj->cond);
    pthread_mutex_unlock(&obj->mutex);
    printf("Thread 2 finished\n");
}

void third(Foo *obj) {
    pthread_mutex_lock(&obj->mutex);
    while (obj->count < 2) {
        pthread_cond_wait(&obj->cond, &obj->mutex);
    }
    printThird();
    pthread_mutex_unlock(&obj->mutex);
    printf("Thread 3 finished\n");
}

void fooFree(Foo *obj) {
    if (obj != NULL) {
        pthread_mutex_destroy(&obj->mutex);
        pthread_cond_destroy(&obj->cond);
        free(obj);
    }
}

void *thread_func(void *arg) {
    int *id = (int *)arg;
    Foo *foo = fooCreate();
    assert(foo != NULL);

    switch (*id) {
    case 1:
        first(foo);
        break;
    case 2:
        second(foo);
        break;
    case 3:
        third(foo);
        break;
    }

    fooFree(foo);
    free(id);
    return NULL;
}

void test_print_in_order(bool is_test) {
    pthread_t threads[3];
    for (int i = 0; i < 3; i++) {
        int *id = malloc(sizeof(int));
        assert(id != NULL);
        *id = i + 1;
        assert(pthread_create(&threads[i], NULL, thread_func, id) == 0);
    }

    for (int i = 0; i < 3; i++) {
        assert(pthread_join(threads[i], NULL) == 0);
    }

    if (is_test) {
        printf("Test passed!\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "test") == 0) {
            test_print_in_order(true);
        } else {
            int iterations = atoi(argv[1]);
            for (int i = 0; i < iterations; i++) {
                test_print_in_order(false);
            }
        }
    } else {
        test_print_in_order(true);
    }
    return 0;
}