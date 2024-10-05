#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond1;
    pthread_cond_t cond2;
    int state;
} Foo;

Foo *fooCreate() {
    Foo *obj = (Foo *)malloc(sizeof(Foo));
    pthread_mutex_init(&obj->mutex, NULL);
    pthread_cond_init(&obj->cond1, NULL);
    pthread_cond_init(&obj->cond2, NULL);
    obj->state = 0;
    return obj;
}

void printFirst(Foo *obj) {
    pthread_mutex_lock(&obj->mutex);
    printf("first");
    obj->state = 1;
    pthread_cond_signal(&obj->cond1);
    pthread_mutex_unlock(&obj->mutex);
}

void printSecond(Foo *obj) {
    pthread_mutex_lock(&obj->mutex);
    while (obj->state != 1) {
        pthread_cond_wait(&obj->cond1, &obj->mutex);
    }
    printf("second");
    obj->state = 2;
    pthread_cond_signal(&obj->cond2);
    pthread_mutex_unlock(&obj->mutex);
}

void printThird(Foo *obj) {
    pthread_mutex_lock(&obj->mutex);
    while (obj->state != 2) {
        pthread_cond_wait(&obj->cond2, &obj->mutex);
    }
    printf("third");
    obj->state = 0;
    pthread_cond_signal(&obj->cond2);
    pthread_mutex_unlock(&obj->mutex);
}

void first(Foo *obj) { printFirst(obj); }

void second(Foo *obj) { printSecond(obj); }

void third(Foo *obj) { printThird(obj); }

void fooFree(Foo *obj) {
    pthread_mutex_destroy(&obj->mutex);
    pthread_cond_destroy(&obj->cond1);
    pthread_cond_destroy(&obj->cond2);
    free(obj);
}

void testFoo() {
    Foo *obj = fooCreate();
    first(obj);
    second(obj);
    third(obj);
    fooFree(obj);
    assert(1); // Always true, replace with actual assertions
}

#ifdef MAIN_TEST
int main() {
    testFoo();
    return 0;
}
#endif

#ifdef MAIN_PERFORMANCE
int main() {
    Foo *obj = fooCreate();
    for (int i = 0; i < 100000; i++) {
        printf("\n%d\n", i);
        first(obj);
        second(obj);
        third(obj);
    }
    fooFree(obj);
    return 0;
}
#endif