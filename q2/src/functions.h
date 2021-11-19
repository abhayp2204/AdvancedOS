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
void leave();
void waitSeat();
void printWaitSeat();

void leaveEnrage();

int isZoneFull(int Zone);
void noSeat(int G, int P);

int probH();
int probN();
int probA();

void* person_function(void* arg);
void* goal_function(void* arg);
char* getGoalSuffix(int G);
int seatAvailable(int i);

void reach(int i, int j);
void seat(int i, int j, int seatZone, int seatNum);
void dinner(int i);
void leaveHOME();
void leaveAWAY();
void join();

// Time
char* getCurrentTime();
void patience(int G, int P);

// Utility
void flushSTDIN();
void a();
int P(float n);
float R();
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