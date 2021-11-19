#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

clock_t getTime();
void delay(int s);
clock_t start;

int main()
{
    start = clock();
    delay(5);
    clock_t t = getTime();
    printf("t = %ld\n", t);
    // printf("Hello\n");
}

clock_t getTime()
{
    clock_t diff = clock() - start;
    return diff/CLOCKS_PER_SEC;
}

void delay(int s)
{
    s *= 1000000;
    clock_t timeDelay = s + clock();
    while(timeDelay > clock());
}