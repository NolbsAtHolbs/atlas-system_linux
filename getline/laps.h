#ifndef LAPS_H
#define LAPS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/*
* struct cars - represents a car in a race
* @id: id of car
* @laps: laps car has driven
*/

typedef struct cars {
	int *id;
	int laps;
} cars_t;

void race_state(int *id, size_t size);

#endif
