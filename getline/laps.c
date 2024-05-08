#include "laps.h"

/**
 * race_state - counts laps driven by the cars in the race
 * @id: array of ints of ids of cars
 * @size: size of id array
*/

void race_state(int *id, size_t size)
{
	static car_sdt *cars;
	car_sdt *nextCar, *previousCar, *Car;

	if (size == 0)
	{
		for (; cars; cars = nextCar)
			nextCar = cars->nextCar, free(cars);
		return;
	}

	for (; size--; id++)
	{
		for (previousCar = NULL, nextCar = cars; nextCar;
				previousCar = nextCar, nextCar = nextCar->nextCar)
			if (*id <= nextCar->id)
				break;

		if (nextCar && *id == nextCar->id)
		{
			nextCar->laps = nextCar->laps + 1;
		}
		else
		{
			printf("Car %d joined the race\n", *id);
			Car = malloc(sizeof(car_sdt));
			if (Car == NULL)
				return;
			Car->id = *id;
			Car->laps = 0;
			Car->nextCar = nextCar;
			if (previousCar)
				previousCar->nextCar = Car;
			else
				cars = Car;
		}
	}

	printf("Race state:\n");
	for (nextCar = cars; nextCar; nextCar = nextCar->nextCar)
		printf("Car %d [%d laps]\n", nextCar->id, nextCar->laps);
}
