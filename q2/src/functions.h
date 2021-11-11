#ifndef FUN_H
#define FUN_H

void input();
    void inputZones();
    void inputGroups();
    void inputGoals();
    void printZone(int i);
    void printGroup(int i);

void getSpectators(Time t);
void printStruct(int c);
void* reachStadium(void* arg);

void scoreGoal();

// Utility
void flushSTDIN();
void a();
int P(float n);
void printb(char s[]);
void printr(char s[]);

#endif