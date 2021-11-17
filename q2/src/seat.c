#include "libraries.h"
#include "variables.h"
#include "functions.h"
#include "utility.h"

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
    printy(Group[G].Person[P].Name);
    printy(" could not get a seat\n");
    WaitSeat.Person[WaitSeat.Num++] = Group[G].Person[P];
}

void seat(int i, int j, int team, int s)
{
    Zone[team].Seat[s].Person = Group[i].Person[j];
    Zone[team].NumSpectators++;

    char str[2];
    str[0] = getZoneAsChar(team);
    str[1] = '\n';

    char* name = malloc(50);
    strcpy(name, Group[i].Person[j].Name);

    printy(strcat(strcat(name, " has got a seat in zone "), str));

    pthread_mutex_unlock(&Zone[team].SeatLocks[s]);
    sleep(X);

    char* string = malloc(50);
    strcpy(string, Group[i].Person[j].Name);
    strcat(string, " is leaving for home\n");
    printb(string);
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

int isZoneFull(int i)
{
    return (Zone[i].NumSpectators == Zone[i].Capacity);
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