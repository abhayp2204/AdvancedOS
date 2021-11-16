#include "libraries.h"
#include "variables.h"
#include "functions.h"
#include "utility.h"

int isZoneFull(int i)
{
    return (Zone[i].NumSpectators == Zone[i].Capacity);
}

int seatAvailable(int teamNum)
{
    for(int i = 0; i < Zone[teamNum].Capacity; i++)
    {
        tSeat S = Zone[teamNum].Seat[i];
        // printf("S.Person.Name = %s\n", S.Person.Name);
        if(!strlen(S.Person.Name))
        {
            return i;
        }
    }
    return -1;
}

void noSeat(int G, int P)
{
    printm(Group[G].Person[P].Name);
    printm(" could not get a seat\n");
    WaitSeat.Person[WaitSeat.Num++] = Group[G].Person[P];
}

void seatH(int G, int P)
{
    Zone[HOME].Spectator[Zone[HOME].NumSpectators] = Group[G].Person[P];
    // Zone[HOME].Seat[Zone[HOME].NumSpectators] = Group[G].Person[P];
    Zone[HOME].NumSpectators++;
    printm(strcat(Group[G].Person[P].Name, " has got a seat in zone H\n"));
}
void seatA(int G, int P)
{
    Zone[AWAY].Spectator[Zone[AWAY].NumSpectators] = Group[G].Person[P];
    Zone[AWAY].NumSpectators++;
    printm(strcat(Group[G].Person[P].Name, " has got a seat in zone A\n"));
}
void seatN(int G, int P)
{
    Zone[NEUT].Spectator[Zone[NEUT].NumSpectators] = Group[G].Person[P];
    Zone[NEUT].NumSpectators++;
    printm(strcat(Group[G].Person[P].Name, " has got a seat in zone N\n"));
}

void printStruct(int c)
{
    for(int i = 0; i < c; i++)
        printf("(%d, %d)\n", s[i].group_no + 1, s[i].person_no + 1);
}

void printWaitSeat()
{
    for(int i = 0; i < WaitSeat.Num; i++)
    {
        printf("%d: %s\n", i+1, WaitSeat.Person[i].Name);
    }
}

void seat(int i, int j, int team, int s)
{
    Zone[team].Seat[s].Person = Group[i].Person[j];
    Zone[team].NumSpectators++;

    char str[2];
    str[0] = getZoneAsChar(team);
    str[1] = '\n';

    printm(strcat(strcat(Group[i].Person[j].Name, " has got a seat in zone "), str));
    // printmn(Zone[team].NumSpectators);
    // printm("\n");
}

int probHome()
{
    // Home -> Home & Neutral
    int spaceH = Zone[HOME].Capacity - Zone[HOME].NumSpectators;
    int spaceN = Zone[NEUT].Capacity - Zone[NEUT].NumSpectators;
    int sum = spaceH + spaceN;

    float probH = (float)spaceH/(float)(sum);
    if(Prob(probH))
        return HOME;
    return NEUT;
}
int probNeut()
{
    // Home -> Home & Neutral
    int spaceH = Zone[HOME].Capacity - Zone[HOME].NumSpectators;
    int spaceN = Zone[NEUT].Capacity - Zone[NEUT].NumSpectators;
    int spaceA = Zone[AWAY].Capacity - Zone[AWAY].NumSpectators;
    int sum = spaceH + spaceN + spaceA;

    float probH = (float)spaceH/(float)(sum);
    float probN = (float)spaceN/(float)(sum);
    float probA = (float)spaceA/(float)(sum);

    float random = R();
    if(random <= probH)
        return HOME;
    if(random <= probH + probN)
        return NEUT;
    return AWAY;
}
int probAway()
{
    return AWAY;
}