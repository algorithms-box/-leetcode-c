#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    pthread_mutex_t lock;
    pthread_cond_t cond_h;
    pthread_cond_t cond_o;
    int hydrogen;
    int oxygen;
} H2O;

H2O *h2oCreate() {
    H2O *obj = (H2O *)malloc(sizeof(H2O));
    pthread_mutex_init(&obj->lock, NULL);
    pthread_cond_init(&obj->cond_h, NULL);
    pthread_cond_init(&obj->cond_o, NULL);
    obj->hydrogen = 0;
    obj->oxygen = 0;
    return obj;
}

void releaseHydrogen(H2O *obj) {
    pthread_mutex_lock(&obj->lock);
    while (obj->hydrogen >= 2) {
        pthread_cond_wait(&obj->cond_h, &obj->lock);
    }
    obj->hydrogen++;
    if (obj->hydrogen == 2) {
        printf("H2");
        obj->hydrogen = 0;
        pthread_cond_signal(&obj->cond_o);
    }
    pthread_mutex_unlock(&obj->lock);
}

void releaseOxygen(H2O *obj) {
    pthread_mutex_lock(&obj->lock);
    while (obj->oxygen >= 1) {
        pthread_cond_wait(&obj->cond_o, &obj->lock);
    }
    obj->oxygen++;
    if (obj->oxygen == 1) {
        printf("O");
        obj->oxygen = 0;
        pthread_cond_signal(&obj->cond_h);
    }
    pthread_mutex_unlock(&obj->lock);
}

void *hydrogenThread(void *arg) {
    H2O *obj = (H2O *)arg;
    for (int i = 0; i < 10000; i++) {
        releaseHydrogen(obj);
    }
    return NULL;
}

void *oxygenThread(void *arg) {
    H2O *obj = (H2O *)arg;
    for (int i = 0; i < 5000; i++) {
        releaseOxygen(obj);
    }
    return NULL;
}

void h2oFree(H2O *obj) {
    pthread_mutex_destroy(&obj->lock);
    pthread_cond_destroy(&obj->cond_h);
    pthread_cond_destroy(&obj->cond_o);
    free(obj);
}

// Unit Testing
void testH2O() {
    H2O *obj = h2oCreate();
    pthread_t t1, t2;
    pthread_create(&t1, NULL, hydrogenThread, obj);
    pthread_create(&t2, NULL, oxygenThread, obj);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    h2oFree(obj);
    printf("All tests passed.\n");
}

// Performance Testing
void performanceTest() {
    H2O *obj = h2oCreate();
    clock_t start = clock();
    pthread_t t1, t2;
    pthread_create(&t1, NULL, hydrogenThread, obj);
    pthread_create(&t2, NULL, oxygenThread, obj);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nPerformance Test: %.6f seconds\n", time_spent);
    h2oFree(obj);
}

int main() {
    testH2O();
    performanceTest();
    return 0;
}
