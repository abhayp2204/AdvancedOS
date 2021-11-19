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
    char* str = malloc(50);
    strcpy(str, Group[G].Person[P].Name);
    strcat(str, " could not get a seat\n");
    printy(str);

    WaitSeat.Person[WaitSeat.Num++] = Group[G].Person[P];

    // Implement patience time
    sleep(Group[G].Person[P].Patience);
    printf("%s lost patience and left\n", Group[G].Person[P].Name);
    Group[G].Person[P].status = WAITING;
    Group[G].Waiting++;
    dinner(G);
}

void seat(int i, int j, int team, int s)
{
    Zone[team].Seat[s].Person = Group[i].Person[j];
    Zone[team].Seat[s].i = i;
    Zone[team].Seat[s].j = j;
    Zone[team].NumSpectators++;

    char str[2];
    str[0] = getZoneAsChar(team);
    str[1] = '\n';

    char* name = malloc(50);
    strcpy(name, Group[i].Person[j].Name);

    printy(strcat(strcat(name, " has got a seat in zone "), str));

    pthread_mutex_unlock(&Zone[team].SeatLocks[s]);
    sleep(X);
    pthread_mutex_lock(&Zone[team].SeatLocks[s]);

    if(Group[i].Person[j].status == WAITING)
        return;

    printf(COLOR_MAGENTA "%s watched the match for %d seconds and is leaving\n" COLOR_RESET, Group[i].Person[j].Name, X);
    Group[i].Person[j].status = WAITING;
    Group[i].Waiting++;

    printf("G%d: waiting = %d\n", i+1, Group[i].Waiting);
    dinner(i);
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

    // printf("sH = %d\n", spaceH);
    // printf("sN = %d\n", spaceN);
    // printf("sA = %d\n", spaceA);

    // printf("spec H = %d\n", Zone[HOME].NumSpectators);
    // printf("spec N = %d\n", Zone[NEUT].NumSpectators);
    // printf("spec A = %d\n", Zone[AWAY].NumSpectators);

    float random = R();
    if(random < probH)
        return HOME;
    if(random < probH + probN)
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

void dinner(int i)
{
    // Some members of the group are still watching the match
    if(Group[i].Waiting < Group[i].k)
        return;
    
    // If everyone from the group is waiting, they leave for dinner
    char* str = malloc(50);
    sprintf(str, COLOR_BLUE "Group %d is leaving for dinner\n" COLOR_RESET, i+1);
    printb(str);
}