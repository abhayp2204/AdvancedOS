#include "libraries.h"
#include "variables.h"
#include "functions.h"

void leaveAWAY()
{
    usleep(50);

    // Search for people supporting AWAY team
    leaveEnrage(AWAY, AWAY);
}

void leaveHOME()
{
    usleep(50);

    // Search for people supporting AWAY team
    leaveEnrage(HOME, HOME);
    leaveEnrage(HOME, NEUT);
}

void leaveEnrage(int Team, int Z)
{
    for(int i = 0; i < Zone[Z].Capacity; i++)
    {
        tSeat S = Zone[Z].Seat[i];
        tPerson P = S.Person;
        
        // Ignore neutral people
        if(P.SupportTeam == 'N')
            continue;

        if(!strlen(P.Name))
            continue;

        if(Group[S.i].Person[S.j].status == WAITING)
            continue;

        // Check enrage number
        if(Goals[1-Team] < P.EnrageNum)
            continue;

        usleep(50);
        printf(COLOR_RED "%s is leaving due to bad performance of his team\n" COLOR_RESET, Zone[Z].Seat[i].Person.Name);
        printf("%s is waiting for their friends at the exit\n", Zone[Z].Seat[i].Person.Name);

        Zone[Z].NumSpectators--;
        Zone[Z].Seat[i].Person.Name[0] = '\0';
        Group[S.i].Person[S.j].status = WAITING;
        Group[S.i].Waiting++;

        pthread_mutex_lock(&lock);
        pthread_cond_signal(&cond_seat_freed);
        pthread_mutex_unlock(&lock);
    }
}
