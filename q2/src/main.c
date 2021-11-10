#include "libraries.h"
#include "variables.h"
#include "functions.h"
#include "utility.h"

void main()
{
    printf(COLOR_YELLOW "Simulation has started!\n" COLOR_RESET);
    input();
}

void input()
{
    inputZones();

    printb("Spectating Time: ");
    scanf("%d", &X);

    printr("Number of groups: ");
    scanf("%d", &num_groups);
    inputGroups();

    // printGroup(0);

    printg("\nNumber of goal scoring chances: ");
    scanf("%d", &G);
    inputGoals();
}

void inputZones()
{
    Zone[0].Type = 'H'; // Home
    Zone[1].Type = 'A'; // Away
    Zone[2].Type = 'N'; // Neutral

    printb("Home | Away | Neutral\n");
    scanf("%d %d %d", &Zone[0].Capacity, &Zone[1].Capacity, &Zone[2].Capacity);
    // printZone(0);
    // printZone(1);
    // printZone(2);
}

void inputGroups()
{
    Group = (tGroup*)malloc(num_groups * sizeof(tGroup));

    for(int i = 0; i < num_groups; i++)
    {
        flushSTDIN();
        printr("\n(Group ");
        printrn(i+1);
        printr(")\n");

        // Number of people in group i
        printr("Number: ");
        scanf("%d", &Group[i].k);

        Group[i].Person = (tPerson*)malloc(Group[i].k * sizeof(tPerson));
        for(int j = 0; j < Group[i].k; j++)
        {
            printr("P");
            printrn(j+1);
            printr(": ");
            scanf("%s %c %d %d %d", 
                  &Group[i].Person[j].Name,
                  &Group[i].Person[j].Support,
                  &Group[i].Person[j].Time,
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

        scanf("%c %d %lf", 
              &Goal[i].Team,
              &Goal[i].Time,
              &Goal[i].Prob);
    }   
}

void printZone(int i)
{
    printf("Type = %c\n", Zone[i].Type);
    printf("Capacity = %d\n", Zone[i].Capacity);
}

void printGroup(int i)
{
    printf("Number of members = %d\n", Group[i].k);
    for(int j = 0; j < Group[i].k; j++)
    {
        printf("%s ", Group[i].Person[j].Name);
        printf("%c ", Group[i].Person[j].Support);
        printf("%d ", Group[i].Person[j].Time);
        printf("%d ", Group[i].Person[j].Patience);
        printf("%d\n", Group[i].Person[j].EnrageNum);
    }
}