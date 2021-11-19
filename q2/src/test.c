#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

clock_t getTime();
void delay(int ms);
clock_t start;

int main()
{
    start = clock();
    delay(5000);
    printf("Hello\n");
}

clock_t getTime()
{
    clock_t diff = clock() - start;
    return (diff * 1000)/CLOCKS_PER_SEC;
}

void delay(int ms)
{
    clock_t timeDelay = ms + clock();
    while(timeDelay > clock());
}