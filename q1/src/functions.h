#ifndef FUN_H
#define FUN_H

// Input
void input();
    void inputCourses();
    void inputStudents();
    void inputLabs();
    void printZone(int i);
    void printGroup(int i);

// Main
void threadExit();

// Student
void* studentFunction(void* arg);

// Utility
void flushSTDIN();
void a();
void b();
int P(float n);
float R();

#endif