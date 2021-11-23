#include "libraries.h"
#include "variables.h"
#include "functions.h"

void* studentFunction(void* arg)
{
    // pthread_mutex_lock(&lock);
    int i = *(int*)arg;
    // printf("S%d: %d %d %d\n", Student[i].StudentID, Student[i].Pref[0], Student[i].Pref[1], Student[i].Pref[2]);
    // pthread_mutex_unlock(&lock);

    courseRegister(i);

    return NULL;
}

void courseRegister(int i)
{
    sleep(Student[i].FillTime);
    Student[i].Status = FILLED;
    printf(COLOR_GREEN "Student %d has filled in preferences for course registration\n" COLOR_RESET, i);
}