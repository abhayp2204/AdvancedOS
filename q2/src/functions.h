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

int isZoneFull(int Zone);
void noSeat(int G, int P);
void seatH(int G, int P);
void seatA(int G, int P);
void seatN(int G, int P);

void scoreGoal();

void* person_function(void* arg);
int seatAvailable(int i);

void reach(int i, int j);
void seat(int i, int j);

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