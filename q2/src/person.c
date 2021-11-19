#include "libraries.h"
#include "variables.h"
#include "functions.h"

void *person_function(void *arg)
{
    // Extract structure
    tPersonID s = *(tPersonID*)arg;
    int i = s.groupNo;
    int j = s.personNo;

    // Get person's team
    char team = Group[i].Person[j].SupportTeam;
    int teamNum = getZoneAsInt(team);

    reach(i, j);

    // Decide person's zone
    time_t arrivalTime = time(NULL);
    int seatZone;
    int c;
    int flag = 0;
    int timeOut = 1;
    while(time(NULL) - arrivalTime <= Group[i].Person[j].Patience)
    {
        switch(teamNum)
        {
            case HOME: seatZone = probHome(); break;
            case NEUT: seatZone = probNeut(); break;
            case AWAY: seatZone = probAway(); break;
        }

        // Find the first available seat
        c = seatAvailable(seatZone);
        // printf("Seat Zone = %d\n", seatZone);
        
        if(c < 0 && !flag)
        {
            noSeat(i, j);
            flag = 1;
        }
        if(c >= 0)
        {
            timeOut = 0;
            break;
        }
    }

    if(timeOut)
    {
        patience(i, j);
        return NULL;
    }

    pthread_mutex_lock(&Zone[seatZone].SeatLocks[c]);
    seat(i, j, seatZone, c);
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