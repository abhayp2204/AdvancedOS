#include "libraries.h"
#include "variables.h"
#include "functions.h"

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

    // Decide person's zone
    int seatZone;
    switch(teamNum)
    {
        case HOME: seatZone = probHome(); break;
        case NEUT: seatZone = probNeut(); break;
        case AWAY: seatZone = probAway(); break;
    }

    // Find the first available seat
    int c = seatAvailable(seatZone);
    if(c < 0)
    {
        noSeat(i, j);
        return NULL;
    }

    pthread_mutex_lock(&Zone[seatZone].SeatLocks[c]);
    seat(i, j, seatZone, c);
    // leave();
    // coord(i, j);
    pthread_mutex_unlock(&Zone[seatZone].SeatLocks[c]);

    return NULL;
}

void reach(int i, int j)
{
    sleep(Group[i].Person[j].ArrivalTime);
    char *str = malloc(30);
    strcpy(str, Group[i].Person[j].Name);
    printc(strcat(str, " has reached the stadium\n"));
}