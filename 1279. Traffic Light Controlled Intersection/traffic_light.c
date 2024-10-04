#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#define NUM_CARS 10

sem_t mutex;
sem_t green[2];

void* car(void* arg) {
    int id = *(int*)arg;
    int direction = id % 2;
    sem_wait(&mutex);
    printf("Car %d entering intersection in direction %d\n", id, direction);
    sem_post(&mutex);

    sem_wait(&green[direction]);
    printf("Car %d passing through intersection in direction %d\n", id, direction);
    sem_post(&green[1 - direction]);

    return NULL;
}

int main(int argc, char* argv[]) {
    pthread_t threads[NUM_CARS];
    int ids[NUM_CARS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&green[0], 0, 1);
    sem_init(&green[1], 0, 0);

    for (int i = 0; i < NUM_CARS; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, car, &ids[i]);
    }

    for (int i = 0; i < NUM_CARS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&green[0]);
    sem_destroy(&green[1]);

    return 0;
}