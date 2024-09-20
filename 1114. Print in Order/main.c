#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    pthread_mutex_t lock;
    pthread_cond_t cond1;
    pthread_cond_t cond2;
    int first_done;
    int second_done;
} Foo;

Foo *fooCreate() {
    Foo *obj = (Foo *)malloc(sizeof(Foo));
    pthread_mutex_init(&obj->lock, NULL);
    pthread_cond_init(&obj->cond1, NULL);
    pthread_cond_init(&obj->cond2, NULL);
    obj->first_done = 0;
    obj->second_done = 0;
    return obj;
}

void first(Foo *obj) {
    pthread_mutex_lock(&obj->lock);
    printf("first");
    obj->first_done = 1;
    pthread_cond_signal(&obj->cond1);
    pthread_mutex_unlock(&obj->lock);
}

void second(Foo *obj) {
    pthread_mutex_lock(&obj->lock);
    while (!obj->first_done) {
        pthread_cond_wait(&obj->cond1, &obj->lock);
    }
    printf("second");
    obj->second_done = 1;
    pthread_cond_signal(&obj->cond2);
    pthread_mutex_unlock(&obj->lock);
}

void third(Foo *obj) {
    pthread_mutex_lock(&obj->lock);
    while (!obj->second_done) {
        pthread_cond_wait(&obj->cond2, &obj->lock);
    }
    printf("third");
    pthread_mutex_unlock(&obj->lock);
}

void fooFree(Foo *obj) {
    pthread_mutex_destroy(&obj->lock);
    pthread_cond_destroy(&obj->cond1);
    pthread_cond_destroy(&obj->cond2);
    free(obj);
}

// Unit Testing
void testFoo() {
    Foo *obj = fooCreate();
    assert(obj != NULL);
    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, (void *(*)(void *))first, obj);
    pthread_create(&t2, NULL, (void *(*)(void *))second, obj);
    pthread_create(&t3, NULL, (void *(*)(void *))third, obj);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    fooFree(obj);
    printf("All tests passed.\n");
}

// Performance Testing
void performanceTest() {
    Foo *obj = fooCreate();
    clock_t start = clock();
    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, (void *(*)(void *))first, obj);
    pthread_create(&t2, NULL, (void *(*)(void *))second, obj);
    pthread_create(&t3, NULL, (void *(*)(void *))third, obj);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Performance Test: %.6f seconds\n", time_spent);
    fooFree(obj);
}

int main() {
    testFoo();
    performanceTest();
    return 0;
}
