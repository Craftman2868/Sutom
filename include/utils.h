#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

time_t getTime();

void initRandom();

int safeRandom();

int randrange(int min, int max);
char* randchoice(char* array[], int size);

#endif  // UTILS_H
