#ifndef LIB_H
#define LIB_H

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>   

// Colors
// Colors
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

// Zone Structure
typedef struct stZone tZone;
struct stZone
{
    char Type;
    uint Capacity;
};
tZone Zone[3];

// Person Structure
typedef struct stPerson tPerson;
struct stPerson
{
    char Name[20];
    char Support;
    int Time;
    int Patience;
    int EnrageNum;
};

// Group Structure
typedef struct stGroup tGroup;
struct stGroup
{
    int k;
    tPerson* Person;
};
tGroup* Group;

// Goal Structure
typedef struct stGoal tGoal;
struct stGoal
{
    char Team;
    int Time;
    float Prob;
};
tGoal* Goal;

#endif