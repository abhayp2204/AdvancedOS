#include "libraries.h"
#include "variables.h"
// #include "functions.h"
// #include "utility.h"

void input()
{
    inputZones();

    printf(COLOR_BLUE "Spectating Time: " COLOR_RESET);
    scanf("%d", &X);

    // Groups, Persons
    printf(COLOR_RED "Number of groups: " COLOR_RESET);
    scanf("%d", &num_groups);
    inputGroups();

    // Goals
    printf(COLOR_GREEN "\nNumber of goal scoring chances: " COLOR_RESET);
    scanf("%d", &G);
    goal_thread = (pthread_t*)malloc(G * sizeof(pthread_t));
    inputGoals();
}

void inputZones()
{
    Zone[HOME].Type = 'H';         // Home
    Zone[AWAY].Type = 'A';         // Away
    Zone[NEUT].Type = 'N';         // Neutral

    // Input zone capacities
    printf(COLOR_BLUE "Home | Away | Neutral\n" COLOR_RESET);
    scanf("%d %d %d", &Zone[0].Capacity, &Zone[1].Capacity, &Zone[2].Capacity);

    // Iterate through all the zones
    for(int i = 0; i < 3; i++)
    {
        // Intialize zones. Create locks for every seat in a zone
        Zone[i].NumSpectators = 0;
        Zone[i].Spectator = (tPerson*)malloc(Zone[i].Capacity * sizeof(tPerson));
        Zone[i].Seat = malloc(Zone[i].Capacity * sizeof(tSeat));
        Zone[i].SeatLocks = malloc(Zone[i].Capacity * sizeof(pthread_mutex_t));
        
        // Initialize the lock for each seat in a zone
        for(int j = 0; j < Zone[i].Capacity; j++)
        {
            pthread_mutex_init(&Zone[i].SeatLocks[j], NULL);
        }
    }
}

void inputGroups()
{
    Group = (tGroup*)malloc(num_groups * sizeof(tGroup));

    // Iterate through the groups
    for(int i = 0; i < num_groups; i++)
    {
        flushSTDIN();
        printf(COLOR_RED "\n(Group %d)\n" COLOR_RESET, i+1);

        // Number of people in group i
        printf(COLOR_RED "Number: " COLOR_RESET);
        scanf("%d", &Group[i].k);
        num_people += Group[i].k;

        // Allocate memory for all persons in a group
        Group[i].Person = (tPerson*)malloc(Group[i].k * sizeof(tPerson));

        // Initially, no one is waiting
        Group[i].Waiting = 0;
        
        // Input persons in the group
        inputPersons(i);
    }
}

void inputPersons(int i)
{
    // Iterate through all the persons in the group
    for(int j = 0; j < Group[i].k; j++)
    {
        // Prefix
        printf(COLOR_RED "P%d: " COLOR_RESET, j+1);

        // Input person variables
        scanf("%s %c %d %d %d", 
                &Group[i].Person[j].Name,
                &Group[i].Person[j].SupportTeam,
                &Group[i].Person[j].ArrivalTime,
                &Group[i].Person[j].Patience,
                &Group[i].Person[j].EnrageNum);
        // Group[i].Person[j].status = REACHED;
    }
}

void inputGoals()
{
    Goal = (tGoal*)malloc(G * sizeof(tGoal));

    for(int i = 0; i < G; i++)
    {
        pthread_mutex_init(&Goal[i].GoalLock, NULL);
        flushSTDIN();

        // Prefix
        printf(COLOR_GREEN "G%d: " COLOR_RESET, i+1);

        // Input goal variables
        scanf("%c %d %f", 
                &Goal[i].Team,
                &Goal[i].GoalTime,
                &Goal[i].GoalProb);
    }   
    printf("\n");
}

void printZone(int i)
{
    printf("\nType = %c\n", Zone[i].Type);
    printf("Capacity = %d\n", Zone[i].Capacity);
    for(int j = 0; j < Zone[i].NumSpectators; j++)
    {
        printf("%d: %s\n", j+1, Zone[i].Spectator[j].Name);
    }
    printf("\n");
}

void printGroup(int i)
{
    printr("(Group ");
    printrn(i+1);
    printr(")\n");

    printr("Number: ");
    printrn(Group[i].k);
    printr("\n");

    for(int j = 0; j < Group[i].k; j++)
    {
        printr("P");
        printrn(j+1);
        printr(": ");

        printf("%s\t", Group[i].Person[j].Name);
        printf("%c  ", Group[i].Person[j].SupportTeam);
        printf("%d  ", Group[i].Person[j].ArrivalTime);
        printf("%d  ", Group[i].Person[j].Patience);
        printf("%d\n", Group[i].Person[j].EnrageNum);
    }
    printf("\n");
}

void printGoals()
{
    for(int i = 0; i < G; i++)
    {
        printf("G%d: %c %d %f\n", i+1, Goal[i].Team, Goal[i].GoalTime, Goal[i].GoalProb);
    }
}