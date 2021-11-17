// Each person is a thread
// Each seat is a lock

// Libraries
#include "libraries.h"
#include "variables.h"
#include "functions.h"
#include "input.c"
#include "seat.c"
#include "person.c"
#include "goal.c"
#include "leave.c"

void main()
{
    WaitSeat.Num = 0;

    printy("Simulation has started!\n");
    input();
    printf("-----------------------------------------------\n");
    tPersonID PersonID[num_people];

    // Person Threads
    int c = 0;
    for (int i = 0; i < num_groups; i++)
    {
        Group[i].th[Group[i].k];
        for (int j = 0; j < Group[i].k; j++)
        {
            PersonID[c].groupNo = i;
            PersonID[c].personNo = j;
            pthread_create(&Group[i].th[j], NULL, person_function, &PersonID[c++]);
        }
    }

    // Goal Threads
    for(int i = 0; i < G; i++)
    {
        pthread_create(&goal_thread[i], NULL, goal_function, &i);
        usleep(50);
    }

    // Join threads
    join();
}

void join()
{
    // Join person threads
    for (int i = 0; i < num_groups; i++)
    {
        for (int j = 0; j < Group[i].k; j++)
        {
            pthread_join(Group[i].th[j], NULL);
        }
    }

    // Join goal threads
    for(int i = 0; i < G; i++)
    {
        pthread_join(goal_thread[i], NULL);
    }
}