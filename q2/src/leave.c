#include "libraries.h"
#include "variables.h"
#include "functions.h"

void leaveAWAY()
{
    usleep(50);

    // AWAY supportes can be seated only in AWAY zone
    leaveEnrage(AWAY, AWAY);
}

void leaveHOME()
{
    usleep(50);

    // HOME supportes can be seated in HOME and NEUT zones
    leaveEnrage(HOME, HOME);    
    leaveEnrage(HOME, NEUT);
}

// Look for enraged people supporting team T in zone Z
void leaveEnrage(int T, int Z)
{
    // Iterate through all the seats in zone Z
    for(int i = 0; i < Zone[Z].Capacity; i++)
    {
        tSeat S = Zone[Z].Seat[i];
        tPerson P = S.Person;
        
        // Ignore neutral people
        if(P.SupportTeam == 'N')
            continue;

        if(!strlen(P.Name))
            continue;

        // Ignore people who have left
        if(Group[S.i].Person[S.j].status == WAITING)
            continue;

        // Check if not enraged (1-T gives the opposite team).
        if(Goals[1-T] < P.EnrageNum)
            continue;

        usleep(50);
        printf(COLOR_RED "%s is leaving due to bad performance of his team\n" COLOR_RESET, Zone[Z].Seat[i].Person.Name);
        printf("%s is waiting for their friends at the exit\n", Zone[Z].Seat[i].Person.Name);

        Zone[Z].NumSpectators--;
        Zone[Z].Seat[i].Person.Name[0] = '\0';
        Group[S.i].Person[S.j].status = WAITING;
        Group[S.i].Waiting++;

        // Send a signal so that threads of people who could not get a
        // seat can start looking for a seat after a person has left
        pthread_mutex_lock(&lock);
        pthread_cond_signal(&cond_seat_freed);
        pthread_mutex_unlock(&lock);
    }
}
