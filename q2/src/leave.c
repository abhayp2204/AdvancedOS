#include "libraries.h"
#include "variables.h"
#include "functions.h"

// void leave()
// {
//     // Home
//     for(int i = 0; i < Zone[HOME].NumSpectators; i++)
//     {
//         if(Zone[HOME].Spectator[i].SupportTeam == 'N')
//             continue;
//         if(A_Goals >= Zone[HOME].Spectator[i].EnrageNum)
//         {
//             printr(strcat(Zone[HOME].Spectator[i].Name, " is leaving due to poor performance of his team\n"));
//             Zone[HOME].NumSpectators--;
//         }
//     }
//     // Away
//     for(int i = 0; i < Zone[AWAY].NumSpectators; i++)
//     {
//         if(Zone[HOME].Spectator[i].SupportTeam == 'N')
//             continue;
//         if(H_Goals >= Zone[AWAY].Spectator[i].EnrageNum)
//         {
//             printr(strcat(Zone[AWAY].Spectator[i].Name, " is leaving due to poor performance of his team\n"));
//             Zone[AWAY].NumSpectators--;
//         }
//     }
// }

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

        // Check enrage number
        if(H_Goals >= P.EnrageNum)
        {
            Zone[AWAY].Seat[i].Person.Name[0] = '\0';
            Zone[AWAY].Seat[i].Person.EnrageNum = -1;

            usleep(50);
            printr(strcat(P.Name, " is leaving due to bad performance of his team\n"));
        }
    }
}

void leaveHOME()
{

}