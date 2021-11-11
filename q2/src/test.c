#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define BIG 10000000
uint counter = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* count1(void* arg)
{
    for(int i = 1; i <= BIG; i++)
    {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    sleep(5);
    return NULL;
}

void count2()
{
    for(int i = 1; i <= BIG; i++)
    {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    sleep(5);
}

void count3()
{
    for(int i = 1; i <= BIG; i++)
    {
        counter++;
    }
    sleep(5);
}

void main()
{
    pthread_t thread;

    pthread_create(&thread, NULL, count1, NULL);
    count2();
    // count3();

    // pthread_join(thread, NULL);
    printf("Counter = %d\n", counter);
}