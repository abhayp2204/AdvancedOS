// Each person is a thread
// Each seat is a lock

// Libraries
#include "libraries.h"
#include "variables.h"
#include "functions.h"
#include "input.c"
#include "seat.c"
#include "goal.c"
#include "leave.c"

void main()
{
    WaitSeat.Num = 0;

    printy("Simulation has started!\n");
    input();
    printf("-----------------------------------\n");
    tPersonID PersonID[num_people];

    // Create threads
    int c = 0;
    for (int i = 0; i < num_groups; i++)
    {
        Group[i].th[Group[i].k];
        for (int j = 0; j < Group[i].k; j++)
        {
            PersonID[c].groupNo = i;
            PersonID[c].personNo = j;
            pthread_create(&Group[i].th[j], NULL, person_function, &PersonID[c++]);
            // sleep(1);
        }
    }
    // Join threads
    for (int i = 0; i < num_groups; i++)
    {
        for (int j = 0; j < Group[i].k; j++)
        {
            pthread_join(Group[i].th[j], NULL);
        }
    }
}

void *person_function(void *arg)
{
    // Extract structure
    tPersonID s = *(tPersonID *)arg;
    int i = s.groupNo;
    int j = s.personNo;

    // Get person's team
    char team = Group[i].Person[j].SupportTeam;
    int teamNum = getZoneAsInt(team);

    reach(i, j);

    int seatZone;
    switch(teamNum)
    {
        case HOME: seatZone = probHome(); break;
        case NEUT: seatZone = probNeut(); break;
        case AWAY: seatZone = probAway(); break;
    }

    int c = seatAvailable(seatZone);
    // printf("c = %d\n", c);
    if(c < 0)
    {
        noSeat(i, j);
        return NULL;
    }

    pthread_mutex_lock(&Zone[seatZone].SeatLocks[c]);
    seat(i, j, seatZone, c);
    // coord(i, j);
    pthread_mutex_unlock(&Zone[seatZone].SeatLocks[c]);

    return NULL;
}

void reach(int i, int j)
{
    sleep(Group[i].Person[j].ArrivalTime);
    char *str = malloc(30);
    strcpy(str, Group[i].Person[j].Name);
    printr(strcat(str, " has reached the stadium\n"));
}