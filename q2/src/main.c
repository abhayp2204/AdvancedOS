// Each person is a thread
// All seats are locks

// Libraries
#include "libraries.h"
#include "variables.h"
#include "functions.h"
#include "input.c"
#include "reach.c"
#include "goal.c"
#include "leave.c"

void main()
{
    WaitSeat.Num = 0;

    printy("Simulation has started!\n");
    input();
    tPersonID PersonID[num_people]; // Update size

    int c = 0;

    // Create threads
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

    // a();
    // printf("Person in seat = %s\n", Zone[HOME].Seat[0].Person.Name);
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

    int c = seatAvailable(teamNum);

    if(c < 0)
    {
        noSeat(i, j);
    }

    reach(i, j);
    pthread_mutex_lock(&Zone[teamNum].SeatLocks[i]);
    seat(i, j);
    // coord(i, j);
    pthread_mutex_unlock(&Zone[teamNum].SeatLocks[i]);

    return NULL;
}

void reach(int i, int j)
{
    sleep(Group[i].Person[j].ArrivalTime);
    char *str = malloc(30);
    strcpy(str, Group[i].Person[j].Name);
    printr(strcat(str, " has reached the stadium\n"));
}

void seat(int i, int j)
{
    if (Group[i].Person[j].SupportTeam == 'H')
    {
        if (isZoneFull(HOME) && isZoneFull(NEUT))
            noSeat(i, j);
        else if (isZoneFull(HOME))
            seatN(i, j);
        else if (isZoneFull(NEUT))
            seatH(i, j);
        else
        {
            if (Prob(0.5))
                seatH(i, j);
            else
                seatN(i, j);
        }
    }
    if (Group[i].Person[j].SupportTeam == 'A')
    {
        if (isZoneFull(AWAY))
            noSeat(i, j);
        else
            seatA(i, j);
    }
    if (Group[i].Person[j].SupportTeam == 'N')
    {
        // a();
        if (isZoneFull(HOME) && isZoneFull(AWAY) && isZoneFull(NEUT))
            noSeat(i, j);
        else if (isZoneFull(HOME) && isZoneFull(AWAY))
            seatN(i, j);
        else if (isZoneFull(HOME) && isZoneFull(NEUT))
            seatA(i, j);
        else if (isZoneFull(AWAY) && isZoneFull(NEUT))
            seatH(i, j);
        else if (isZoneFull(HOME))
        {
            if (Prob(0.5))
                seatA(i, j);
            else
                seatN(i, j);
        }
        else if (isZoneFull(AWAY))
        {
            if (Prob(0.5))
                seatH(i, j);
            else
                seatN(i, j);
        }
        else if (isZoneFull(NEUT))
        {
            if (Prob(0.5))
                seatH(i, j);
            else
                seatA(i, j);
        }
        else
        {
            if (Prob(0.33))
                seatH(i, j);
            else if (Prob(0.67))
                seatN(i, j);
            else
                seatA(i, j);
        }
    }
}

int isZoneFull(int i)
{
    return (Zone[i].NumSpectators == Zone[i].Capacity);
}

int seatAvailable(int teamNum)
{
    for(int i = 0; i < Zone[teamNum].Capacity; i++)
    {
        tSeat S = Zone[teamNum].Seat[i];
        if(!strlen(S.Person.Name))
        {
            return i;
        }
    }
    return -1;
}