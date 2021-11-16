#include "libraries.h"
#include "variables.h"
#include "functions.h"

void leave()
{
    // Home
    for(int i = 0; i < Zone[HOME].NumSpectators; i++)
    {
        if(Zone[HOME].Spectator[i].SupportTeam == 'N')
            continue;
        if(A_Goals >= Zone[HOME].Spectator[i].EnrageNum)
        {
            printr(strcat(Zone[HOME].Spectator[i].Name, " is leaving due to poor performance of his team\n"));
            Zone[HOME].NumSpectators--;
        }
    }
    // Away
    for(int i = 0; i < Zone[AWAY].NumSpectators; i++)
    {
        if(Zone[HOME].Spectator[i].SupportTeam == 'N')
            continue;
        if(H_Goals >= Zone[AWAY].Spectator[i].EnrageNum)
        {
            printr(strcat(Zone[AWAY].Spectator[i].Name, " is leaving due to poor performance of his team\n"));
            Zone[AWAY].NumSpectators--;
        }
    }
}