#include "devilution.h"

unsigned int rand_state = 1;

int rand(void)
{
	rand_state = rand_state * 214013 + 2531011;
	return (rand_state >> 16) & 0x7FFF;
}

void srand(unsigned int seed)
{
	rand_state = seed;
}
