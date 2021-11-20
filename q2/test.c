#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

int initialized = 0;
int initialized2 = 0;

char* message;
char* message2;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t  cond2 = PTHREAD_COND_INITIALIZER;

void* function1(void* arg);
void* function2(void* arg);
void* function3(void* arg);

void main()
{
    pthread_t th1, th2, th3;
    pthread_mutex_init(&lock, NULL);

    pthread_create(&th2, NULL, function2, NULL);
    pthread_create(&th3, NULL, function3, NULL);
    pthread_create(&th1, NULL, function1, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
}

void* function1(void* arg)
{
    message = "Hello World!";

    pthread_mutex_lock(&lock);
    initialized = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);

    sleep(3);
    message2 = "Goodbye!";

    pthread_mutex_lock(&lock);
    initialized2 = 1;
    pthread_cond_signal(&cond2);
    pthread_mutex_unlock(&lock);

    return NULL;
}

void* function2(void* arg)
{
    pthread_mutex_lock(&lock);
    while(initialized == 0)
    {
        pthread_cond_wait(&cond, &lock);
    }
    pthread_mutex_unlock(&lock);

    printf("%s\n", message);
    return NULL;
}

void* function3(void* arg)
{
    pthread_mutex_lock(&lock);
    while(initialized2 == 0)
    {
        pthread_cond_wait(&cond2, &lock);
    }
    pthread_mutex_unlock(&lock);

    printf("%s\n", message2);
    return NULL;
}