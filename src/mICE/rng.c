#include <mICE/rng.h>
#include <stdlib.h>

void setSeed(unsigned int seed) {
	srand(seed);
}

int randInt(int min, int max) {
	return rand() % (max - min) + min;
}

float randFloat(float min, float max) {
	return rand() / (float)RAND_MAX * (max - min) + min;
}