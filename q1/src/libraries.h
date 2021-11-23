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

// Course/Mentor status
#define FREE 0
#define OCCUPIED 1

// Student status
#define NOT_FILLED 0
#define FILLED 1

// Types
typedef uint Time;

// Course Structure
typedef struct stCourse tCourse;
struct stCourse
{
    int CourseID;
    char Name[10];
    float Interest;
    int MaxSlots;
    int Slots;
    int SlotsFilled;
    int NumLabs;
    int* LabID;
    int Status;
};

// Mentor Structure
typedef struct stMentor tMentor;
struct stMentor
{
    int ID;
    int Num;
    int Status;
    pthread_mutex_t MentorLock;
};

// Lab Structure
typedef struct stLab tLab;
struct stLab
{
    char Name[10];
    int NumMentors;
    tMentor* Mentor;
    int Max;
};

// Student Structure
typedef struct stStudent tStudent;
struct stStudent
{
    // int dump[10];
    int StudentID;
    float Calibre;
    int Current;
    int Pref[2];
    Time FillTime;
    int Status;
};


#endif