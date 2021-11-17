#include "libraries.h"
#include "variables.h"
#include "functions.h"

void *goal_function(void* arg)
{
    int i = *(int*)arg;
    // pthread_mutex_lock(&Goal[i].GoalLock);
    // printf("G: i=%d time=%d prob=%f\n", i, Goal[i].GoalTime, Goal[i].GoalProb);
    sleep(Goal[i].GoalTime);
    usleep(100);

    // Goal scored
    if(Prob(Goal[i].GoalProb))
    {
        // HOME team scores
        if(Goal[i].Team == 'H')
        {
            H_Goals++;
            printf(COLOR_GREEN "Team H has scored their %d goal!\n" COLOR_RESET, H_Goals);
            leaveAWAY();
        }
        // AWAY team scores
        else
        {
            A_Goals++;
            printf(COLOR_GREEN "Team A has scored their %d goal!\n" COLOR_RESET, A_Goals);
            leaveHOME();
        }
        
        return NULL;
    }
    // Goal Missed
    printf(COLOR_GREEN "Team %c has missed!\n" COLOR_RESET, Goal[i].Team);
}