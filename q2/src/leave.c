#include "libraries.h"
#include "variables.h"
#include "functions.h"

void leaveAWAY()
{
    // Search for people supporting AWAY team
    for(int i = 0; i < Zone[AWAY].Capacity; i++)
    {
        tSeat S = Zone[AWAY].Seat[i];
        tPerson P = S.Person;
        
        // Ignore neutral people
        if(P.SupportTeam == 'N')
            continue;

        if(!strlen(P.Name))
            continue;

        // Check enrage number
        if(H_Goals >= P.EnrageNum)
        {
            usleep(50);
            printr(strcat(Zone[AWAY].Seat[i].Person.Name, " is leaving due to bad performance of his team\n"));
            Zone[AWAY].NumSpectators--;
            Zone[AWAY].Seat[i].Person.Name[0] = '\0';
            Group[S.i].Person[S.j].status = WAITING;
        }
    }
}

void leaveHOME()
{

}