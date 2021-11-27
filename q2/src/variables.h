#ifndef VAR_H
#define VAR_H

#define HOME_TEAM "FC Messilona"
#define AWAY_TEAM "Benzdrid CF"

#define HOME 0
#define AWAY 1
#define NEUT 2

#define REACHED 11
#define WAITING 12
#define EXIT    13

int X;               // Spectating time
int num_groups;      // Total number of groups
int num_people = 0;
int G;               // Number of goal scoring chances
time_t startTime;
time_t maxTime = 0;

int Goals[2];

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_t* goal_thread;
pthread_cond_t cond_seat_freed = PTHREAD_COND_INITIALIZER;
// int seat_freed = 0;

#endif