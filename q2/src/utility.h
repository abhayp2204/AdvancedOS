#include "libraries.h"

void flushSTDIN()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Debugging
void a()
{
    printf("------ Fish\n");
}
void b()
{
    printf("------ Shark\n");
}
void c()
{
    printf("------ Start\n");
}
void d()
{
    printf("------ End\n");
}
void coord(int i, int j)
{
    printf("(%d, %d) %s\n", i+1, j+1, Group[i].Person[j].Name);
}

int getZoneAsInt(char c)
{
    switch(c)
    {
        case 'H': return HOME;
        case 'A': return AWAY;
        case 'N': return NEUT;
    }
}

char getZoneAsChar(int zone)
{
    switch(zone)
    {
        case HOME: return 'H';
        case AWAY: return 'A';
        case NEUT: return 'N';
    }
}

int Prob(float n)
{
    if(n == 1) return 1;

    srand(time(NULL) % 30);
    float p = (float)rand() / (float)RAND_MAX;
    return (p < n);
}
// Random number between 0 and 1
float R()
{
    srand(time(NULL) % 30);
    float p = (float)rand() / (float)RAND_MAX;
    return p;
}