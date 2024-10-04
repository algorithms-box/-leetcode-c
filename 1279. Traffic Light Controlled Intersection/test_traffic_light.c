#include "traffic_light.c"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 模拟turnGreen函数
void mockTurnGreen(int roadId) { printf("Turn green for road %d\n", roadId); }

// 模拟crossCar函数
void mockCrossCar() { printf("Car is crossing\n"); }

// 单元测试
void unitTest() {
    TrafficLight *light = trafficLightCreate();
    assert(light != NULL);
    assert(light->greenRoad == 1);

    carArrived(light, 1, 1, 1, mockTurnGreen, mockCrossCar);
    assert(light->greenRoad == 1);

    carArrived(light, 2, 2, 3, mockTurnGreen, mockCrossCar);
    assert(light->greenRoad == 2);

    carArrived(light, 3, 1, 2, mockTurnGreen, mockCrossCar);
    assert(light->greenRoad == 1);

    trafficLightFree(light);
    printf("Unit tests passed!\n");
}

// 性能测试
void performanceTest() {
    TrafficLight *light = trafficLightCreate();
    clock_t start = clock();

    for (int i = 0; i < 1000000; i++) {
        carArrived(light, i, i % 2 + 1, i % 4 + 1, mockTurnGreen, mockCrossCar);
    }

    clock_t end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Performance test: Processed 1,000,000 cars in %f seconds\n",
           cpu_time_used);

    trafficLightFree(light);
}

int main() {
    unitTest();
    performanceTest();
    return 0;
}