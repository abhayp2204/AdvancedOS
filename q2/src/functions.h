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
// void* getSeat(void* arg);

int isZoneFull(int Zone);
void seatH(int G, int P);
void seatA(int G, int P);
void seatN(int G, int P);

void scoreGoal();

// Utility
void flushSTDIN();
void a();
int P(float n);
void printb(char s[]);
void printr(char s[]);
void printrn(int n);
void printg(char s[]);
void printgn(int n);
void printm(char s[]);
void printmn(int n);
void printc(char s[]);
void printcn(int n);
void printy(char s[]);
void printyn(int n);

#endif