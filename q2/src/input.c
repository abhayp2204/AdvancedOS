#include "libraries.h"
#include "variables.h"
// #include "functions.h"
// #include "utility.h"

void input()
{
    inputZones();

    printb("Spectating Time: ");
    scanf("%d", &X);

    printr("Number of groups: ");
    scanf("%d", &num_groups);
    inputGroups();

    printg("\nNumber of goal scoring chances: ");
    scanf("%d", &G);
    inputGoals();
}

void inputZones()
{
    Zone[0].Type = 'H';         // Home
    Zone[1].Type = 'A';         // Away
    Zone[2].Type = 'N';         // Neutral

    printb("Home | Away | Neutral\n");
    scanf("%d %d %d", &Zone[0].Capacity, &Zone[1].Capacity, &Zone[2].Capacity);

    // Initialize the zone
    for(int i = 0; i < 3; i++)
    {
        Zone[i].NumSpectators = 0;
        Zone[i].Spectator = (tPerson*)malloc(Zone[i].Capacity * sizeof(tPerson));
        Zone[i].SeatLocks = malloc(Zone[i].Capacity * sizeof(pthread_mutex_t));
        Zone[i].Seat = malloc(Zone[i].Capacity * sizeof(tSeat));

        // Initialize the lock for each seat in a zone
        for(int j = 0; j < Zone[i].Capacity; j++)
        {
            pthread_mutex_init(&Zone[i].SeatLocks[j], NULL);

        }
    }
    WaitSeat.Person = (tPerson*)malloc(20*sizeof(tPerson));

    // printZone(HOME);
    // printZone(AWAY);
    // printZone(NEUT);
}

void inputGroups()
{
    Group = (tGroup*)malloc(num_groups * sizeof(tGroup));

    // Iterate through the groups
    for(int i = 0; i < num_groups; i++)
    {
        flushSTDIN();
        printr("\n(Group ");
        printrn(i+1);
        printr(")\n");

        // Number of people in group i
        printr("Number: ");
        scanf("%d", &Group[i].k);
        num_people += Group[i].k;

        // Allocate memory for all persons in a group
        Group[i].Person = (tPerson*)malloc(Group[i].k * sizeof(tPerson));
        
        // Iterate through the persons
        for(int j = 0; j < Group[i].k; j++)
        {
            printr("P");
            printrn(j+1);
            printr(": ");
            scanf("%s %c %d %d %d", 
                  &Group[i].Person[j].Name,
                  &Group[i].Person[j].SupportTeam,
                  &Group[i].Person[j].ArrivalTime,
                  &Group[i].Person[j].Patience,
                  &Group[i].Person[j].EnrageNum);
        }
    }
}

void inputGoals()
{
    Goal = (tGoal*)malloc(G * sizeof(tGoal));

    for(int i = 0; i < G; i++)
    {
        flushSTDIN();

        printg("G");
        printgn(i+1);
        printg(": ");

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