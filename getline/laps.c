#include "laps.h"

/**
 * free_cars - recursively frees cars with false head that points to list
 * @car: pointer to cars struct
*/

static car_sdt dummyHead = {.nextCar = NULL};

static void free_cars(car_sdt *car) {
    if (car == NULL) return;
    free_cars(car->nextCar);
    free(car);
}

/**
 * race_state - counts laps driven by the cars in the race
 * @id: array of ints of ids of cars
 * @size: size of id array
*/

void race_state(int *id, size_t size) {
    car_sdt *previousCar = &dummyHead;
    car_sdt *currentCar = dummyHead.nextCar;

    if (size == 0) {
        free_cars(dummyHead.nextCar);
        dummyHead.nextCar = NULL;
        return;
    }

    for (; size--; id++) {
        for (; currentCar && *id > currentCar->id; previousCar = currentCar, currentCar = currentCar->nextCar);

        if (currentCar && *id == currentCar->id)
		{
            currentCar->laps++;
        } else {
            printf("Car %d joined the race\n", *id);
            car_sdt *newCar = malloc(sizeof(car_sdt));
            if (!newCar) return;
            newCar->id = *id;
            newCar->laps = 1;
            newCar->nextCar = currentCar;
            previousCar->nextCar = newCar;
        }
    }

    printf("Race state:\n");
    for (currentCar = dummyHead.nextCar; currentCar; currentCar = currentCar->nextCar) {
        printf("Car %d [%d laps]\n", currentCar->id, currentCar->laps);
    }
}
