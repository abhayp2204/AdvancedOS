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

// Course Structure
typedef struct stCourse tCourse;
struct stCourse
{
    int CourseID;
    char Name[10];
    float Interest;
    int MaxSlots;
    int NumLabs;
    int* LabID;
};

// Lab Structure
typedef struct stLab tLab;
struct stLab
{
    char Name[10];
    int NumMentors;
    int MaxTA;
};

// Student Structure
typedef struct stStudent tStudent;
struct stStudent
{
    int StudentID;
    float Calibre;
    int Pref[2];
    int Current;
    Time FillTime;
};


#endif