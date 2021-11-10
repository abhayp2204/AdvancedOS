#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* myturn(void* arg)
{
    while(1)
    {
        sleep(1);
        printf("My turn!\n");
    }
    return NULL;
}

void yourturn()
{
    while(1)
    {
        sleep(2);
        printf("Your turn!\n");
    }
}

int main()
{
    pthread_t newThread;

    pthread_create(&newThread, NULL, myturn, NULL);
    yourturn();
}