#include "libraries.h"

void flushSTDIN()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Debugging
void a()
{
    printf("Fish\n");
}
void b()
{
    printf("Shark\n");
}

int Prob(float n)
{
    if(n == 1) return 1;

    srand(time(0));
    float p = (float)rand() / (float)RAND_MAX;
    return (p < n);
}
// Random number between 0 and 1
float R()
{
    srand(time(0));
    float p = (float)rand() / (float)RAND_MAX;
    return p;
}

// Random number between 1 and L (both inclusive)
int randint(int L)
{
    srand(time(NULL));
    return (rand() % L) + 1;
}