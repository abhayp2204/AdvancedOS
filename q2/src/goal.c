#include "libraries.h"
#include "variables.h"
#include "functions.h"

void scoreGoal(Time t)
{
    char str[1];

    // Iterate through the goals
    for(int i = 0; i < G; i++)
    {
        if(Goal[i].GoalTime != t)
            continue;

        str[0] = Goal[i].Team;
        
        printy("Team ");
        printy(str);

        // If they score
        if(Prob(Goal[i].GoalProb))
        {
            printy(" has scored their ");
            if(Goal[i].Team == 'H')
            {
                H_Goals++;
                printyn(H_Goals);
            }
            else
            {
                A_Goals++;
                printyn(A_Goals);
            }
            printy(" goal\n");
            continue;
        }

        printy(" has missed their chance to score a goal\n");     
    }
}