#ifndef VAR_H
#define VAR_H

#define HOME_TEAM "FC Messilona"
#define AWAY_TEAM "Benzdrid CF"

#define HOME 0
#define AWAY 1
#define NEUT 2

int X;               // Spectating time
int num_groups;      // Total number of groups
int G;               // Number of goal scoring chances

int H_Goals = 0;
int A_Goals = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

#endif