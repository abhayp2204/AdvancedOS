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

    do
    {
        switch(teamNum)
        {
            case HOME: seatZone = probHome(); break;
            case NEUT: seatZone = probNeut(); break;
            case AWAY: seatZone = probAway(); break;
        }

        // Find the first available seat
        c = seatAvailable(seatZone);
        
        if(c < 0 && !flag)
        {
            noSeat(i, j);
            flag = 1;
        }
        if(c >= 0)
        {
            // seat_freed = 0;
            timeOut = 0;
            break;
        }

        // pthread_cond_wait(&cond_seat_freed, &lock);
        pthread_cond_wait(&cond_seat_freed, &Zone[seatZone].SeatLocks[c]);

    }while(time(NULL) - arrivalTime <= Group[i].Person[j].Patience);

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
    printf(COLOR_CYAN "%s has reached the stadium\n" COLOR_RESET, Group[i].Person[j].Name);
}

void patience(int G, int P)
{
    printf("%s is waiting for their friends at the exit\n", Group[G].Person[P].Name);
    Group[G].Person[P].status = WAITING;
    Group[G].Waiting++;
    dinner(G);
}

void dinner(int i)
{
    // Some members of the group are still watching the match
    if(Group[i].Waiting < Group[i].k)
        return;
    
    // Everyone from the group is waiting, they leave for dinner
    printf(COLOR_BLUE "Group %d is leaving for dinner\n" COLOR_RESET, i+1);
}