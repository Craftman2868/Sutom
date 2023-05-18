#include "utils.h"

#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

bool isRandInit = false;

time_t getTime() {
    return time(NULL);
}

void initRandom() {
    srand(getTime());

    isRandInit = true;
}

int safeRandom() {
    if (!isRandInit) {
        initRandom();
    }

    return rand();
}

int randrange(int min, int max) {
    // Generate a random number between min and max

    int range = (max - min + 1);

    return safeRandom() % range + min;
}

char* randchoice(char* array[], int size) {
    return array[safeRandom() % size];
}
