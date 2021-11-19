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

int H_Goals = 0;
int A_Goals = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_t* goal_thread;

#endif