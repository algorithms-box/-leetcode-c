#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int id;
    pthread_mutex_t mutex;
    int greenRoad;
} TrafficLight;

void turnGreen(TrafficLight *obj, int road) {
    pthread_mutex_lock(&obj->mutex);
    obj->greenRoad = road;
    pthread_mutex_unlock(&obj->mutex);
}

void carArrived(TrafficLight *obj, int carId, int roadId, int direction,
                void (*turnGreen)(int), void (*crossCar)()) {
    pthread_mutex_lock(&obj->mutex);
    if (obj->greenRoad != roadId) {
        turnGreen(roadId);
        obj->greenRoad = roadId;
    }
    crossCar();
    pthread_mutex_unlock(&obj->mutex);
}

TrafficLight *trafficLightCreate() {
    TrafficLight *obj = (TrafficLight *)malloc(sizeof(TrafficLight));
    obj->id = 1;
    pthread_mutex_init(&obj->mutex, NULL);
    obj->greenRoad = 1;
    return obj;
}

void trafficLightFree(TrafficLight *obj) {
    pthread_mutex_destroy(&obj->mutex);
    free(obj);
}