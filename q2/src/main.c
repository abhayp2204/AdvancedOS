#include "libraries.h"
#include "variables.h"
#include "functions.h"
#include "utility.h"
#include "input.c"

struct stxyz
{
    int group_no;
    int person_no;
};
typedef struct stxyz xyz;
xyz s[10];

void main()
{
    printf(COLOR_YELLOW "Simulation has started!\n" COLOR_RESET);
    input();

    printGroup(0);
    printGroup(1);

    getSpectators(1);

    scoreGoal(1);
    scoreGoal(2);
    scoreGoal(3);
    scoreGoal(4);
    scoreGoal(5);
    scoreGoal(6);
}

void getSpectators(Time t)
{
    char str[1];
    int c = 0;

    // Iterate through the groups
    for(int i = 0; i < num_groups; i++)
    {
        // Iterate through all the members in a group
        for(int j = 0; j < Group[i].k; j++)
        {
            s[c].group_no = i;

            if(Group[i].Person[j].ArrivalTime == t)
            {
                str[0] = Group[i].Person[j].SupportTeam;

                // printm(Group[i].Person[j].Name);                            printf("\t");
                // printm(str);                                                printf("  ");
                // printmn(Group[i].Person[j].ArrivalTime);                    printf("  ");
                // printmn(Group[i].Person[j].Patience);                       printf("  ");
                // printmn(Group[i].Person[j].EnrageNum);                      printf("\n");

                s[c++].person_no = j;
            }
        }
    }

    // printStruct(c);

    pthread_t thread[c];
    for(int i = 0; i < c; i++)
    {
        pthread_create(&thread[i], NULL, reachStadium, &s[i]);
    }
    for(int i = 0; i < c; i++)
    {
        pthread_join(thread[i], NULL);
    }
}

void printStruct(int c)
{
    for(int i = 0; i < c; i++)
    {
        printf("(%d, %d)\n", s[i].group_no + 1, s[i].person_no + 1);
    }
}

void* reachStadium(void* arg)
{
    xyz s = *(xyz*)arg;

    int G = s.group_no;
    int P = s.person_no;

    printc(Group[G].Person[P].Name);
    printc(" has reached the stadium\n");

    return NULL;
}

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
        printy(P(Goal[i].GoalProb)? " has scored a goal\n" : " has missed their chance to score a goal\n");
    }
}