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
    printf(COLOR_YELLOW "%s could not get a seat\n" COLOR_RESET, Group[G].Person[P].Name);
}

void seat(int i, int j, int team, int s)
{
    Zone[team].Seat[s].Person = Group[i].Person[j];
    Zone[team].Seat[s].i = i;
    Zone[team].Seat[s].j = j;
    Zone[team].NumSpectators++;

    char str[2];
    str[0] = getZoneAsChar(team);
    char ch = getZoneAsChar(team);
    str[1] = '\n';

    char* name = malloc(50);
    strcpy(name, Group[i].Person[j].Name);

    // printy(strcat(strcat(name, " has got a seat in zone "), str));
    printf(COLOR_YELLOW "%s has got a seat in zone %c (%d/%d)\n" COLOR_RESET, 
            Group[i].Person[j].Name,
            ch,
            Zone[team].NumSpectators,
            Zone[team].Capacity);

    pthread_mutex_unlock(&Zone[team].SeatLocks[s]);
    sleep(X);
    pthread_mutex_lock(&Zone[team].SeatLocks[s]);

    if(Group[i].Person[j].status == WAITING)
        return;

    printf(COLOR_MAGENTA "%s watched the match for %d seconds and is leaving\n" COLOR_RESET, Group[i].Person[j].Name, X);
    printf("%s is waiting for their friends at the exit\n", Group[i].Person[j].Name);

    Zone[team].NumSpectators--;
    Zone[team].Seat[i].Person.Name[0] = '\0';
    Group[i].Person[j].status = WAITING;
    Group[i].Waiting++;

    pthread_mutex_lock(&lock);
    pthread_cond_signal(&cond_seat_freed);
    pthread_mutex_unlock(&lock);

    dinner(i);
}

int probHome()
{
    // Home --> Home & Neutral
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
    // Neutral --> Home & Neutral & Away
    int spaceH = Zone[HOME].Capacity - Zone[HOME].NumSpectators;
    int spaceN = Zone[NEUT].Capacity - Zone[NEUT].NumSpectators;
    int spaceA = Zone[AWAY].Capacity - Zone[AWAY].NumSpectators;
    int sum = spaceH + spaceN + spaceA;

    float probH = (float)spaceH/(float)(sum);
    float probN = (float)spaceN/(float)(sum);
    float probA = (float)spaceA/(float)(sum);

    float random = R();
    if(random < probH)
        return HOME;
    if(random < probH + probN)
        return NEUT;
    return AWAY;
}
int probAway()
{
    // Away --> Away
    return AWAY;
}
