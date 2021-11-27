#include "libraries.h"
#include "variables.h"
#include "functions.h"

void *goal_function(void* arg)
{
    int i = *(int*)arg;
    sleep(Goal[i].GoalTime);
    usleep(500);

    char* suffix = malloc(2);

    // Goal scored
    if(Prob(Goal[i].GoalProb))
    {
        // HOME team scores
        if(Goal[i].Team == 'H')
        {
            Goals[HOME]++;
            strcpy(suffix, getGoalSuffix(Goals[HOME]));
            printf(COLOR_GREEN "Team FC Messilona has scored their %d%s goal!\n" COLOR_RESET, Goals[HOME], suffix);

            // People supporting AWAY team may leave
            leaveAWAY();
        }
        // AWAY team scores
        else
        {
            Goals[AWAY]++;
            strcpy(suffix, getGoalSuffix(Goals[AWAY]));
            printf(COLOR_GREEN "Team Benzdrid CF has scored their %d%s goal!\n" COLOR_RESET, Goals[AWAY], suffix);

            // People supporting HOME team may leave
            leaveHOME();
        }
    }
    // Goal Missed
    else
    {
        if(Goal[i].Team == 'H')
        {
            printf(COLOR_GREEN "Team FC Messilona has missed the chance to score their %d%s goal\n" COLOR_RESET,
                Goals[HOME]+1, getGoalSuffix(Goals[HOME]+1));
        }
        else
        {
            printf(COLOR_GREEN "Team Benzdrid CF has missed the chance to score their %d%s goal\n" COLOR_RESET,
                Goals[AWAY]+1, getGoalSuffix(Goals[AWAY]+1));
        }
    }

    if(Goal[i].GoalTime == maxTime)
        exit(0);

    return NULL;
}

char* getGoalSuffix(int Goals)
{
    int secondLastDigit = (Goals/10) % 10;

    // Handle excpetions: 11th, 12th and 13th
    if(secondLastDigit == 1)
        return "th";

    switch(Goals)
    {
        case 1: return "st";
        case 2: return "nd";
        case 3: return "rd";
    }
    return "th";
}