#pragma once

int rand_miniwin(void);
void srand_miniwin(unsigned int seed);

#define srand srand_miniwin
#define rand rand_miniwin
