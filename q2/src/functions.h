#ifndef FUN_H
#define FUN_H

// Input
void input();
    void inputZones();
    void inputGroups();
    void inputGoals();
    void inputPersons(int i);
    void printZone(int i);
    void printGroup(int i);

// Leave
void leaveHOME();
void leaveAWAY();

// Seat
void seat(int i, int j, int seatZone, int seatNum);
int seatAvailable(int i);
void noSeat(int G, int P);
int probHome();
int probNeut();
int probAway();

// Goal
void* goal_function(void* arg);
    char* getGoalSuffix(int G);

// Person
void* person_function(void* arg);
    void reach(int i, int j);
    void patience(int G, int P);
    void dinner(int i);

// Main
void join();

// Utility
void flushSTDIN();
void a();
void b();
void c();
void d();
int P(float n);
float R();

#endif