#ifndef LIB_H
#define LIB_H

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

// Colors
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

// Types
typedef uint Time;

// Person Structure
typedef struct stPerson tPerson;
struct stPerson
{
    int dump[10];
    char Name[100];
    char SupportTeam;
    char SeatedZone;
    Time ArrivalTime;
    Time Patience;
    int EnrageNum;
    int status;
    pthread_mutex_t PersonLock;
};

// Seat Structure
typedef struct stSeat tSeat;
struct stSeat
{
    tPerson Person;
    int i;
    int j;
};

// Zone Structure
typedef struct stZone tZone;
struct stZone
{
    char Type;
    uint Capacity;
    uint NumSpectators;
    tPerson* Spectator;
    tSeat* Seat;
    pthread_mutex_t* SeatLocks;
};
tZone Zone[3];

// Group Structure
typedef struct stGroup tGroup;
struct stGroup
{
    int dump[10];
    int k;
    int Waiting;
    tPerson* Person;
    pthread_t th[];
};
tGroup* Group;

// Goal Structure
typedef struct stGoal tGoal;
struct stGoal
{
    int dump[30];
    char Team;
    Time GoalTime;
    float GoalProb;
    pthread_mutex_t GoalLock;
};
tGoal* Goal;

// Person info structure
struct stPersonID
{
    int dump[10];
    int groupNo;
    int personNo;
};
typedef struct stPersonID tPersonID;

#endif