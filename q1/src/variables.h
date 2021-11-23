#ifndef VAR_H
#define VAR_H

const int numStudents;    
const int numLabs;    
const int numCourses;    

tCourse* Course;
tStudent* Student;
tLab* Lab;

pthread_t* thStudent;
pthread_t* thCourse;
pthread_t* thLab;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_t* goal_thread;
pthread_cond_t cond_seat_freed = PTHREAD_COND_INITIALIZER;
// int seat_freed = 0;

#endif