#include "libraries.h"
#include "variables.h"
#include "functions.h"

void* studentFunction(void* arg)
{
    int i = *(int*)arg;
    printf("S%d: %d %d %d\n", Student[i].StudentID, Student[i].Pref[0], Student[i].Pref[1], Student[i].Pref[2]);
    return NULL;
}