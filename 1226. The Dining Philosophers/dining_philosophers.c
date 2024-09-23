#include "dining_philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t forks[NUM_PHILOSOPHERS];

void *philosopher(void *num) {
    int philosopher = *(int *)num;
    int left_fork = philosopher;
    int right_fork = (philosopher + 1) % NUM_PHILOSOPHERS;

    while (1) {
        pthread_mutex_lock(&forks[left_fork]);
        pthread_mutex_lock(&forks[right_fork]);

        printf("Philosopher %d is eating.\n", philosopher);
        sleep(1);

        pthread_mutex_unlock(&forks[left_fork]);
        pthread_mutex_unlock(&forks[right_fork]);

        printf("Philosopher %d is thinking.\n", philosopher);
        sleep(1);
    }

    return NULL;
}

void testDiningPhilosophers() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int nums[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
        nums[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &nums[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }
}
