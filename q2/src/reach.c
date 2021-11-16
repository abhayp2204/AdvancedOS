#include "libraries.h"
#include "variables.h"
#include "functions.h"
#include "utility.h"

void getSpectators(Time t)
{
    int c = 0;

    // Iterate through the groups
    for(int i = 0; i < num_groups; i++)
    {
        // Iterate through all the members in a group
        for(int j = 0; j < Group[i].k; j++)
        {
            s[c].group_no = i;

            if(Group[i].Person[j].ArrivalTime == t)
                s[c++].person_no = j;
        }
    }

    // printStruct(c);

    // Threading
    pthread_t thread[c];

    for(int i = 0; i < c; i++) pthread_create(&thread[i], NULL, reachStadium, &s[i]);
    // for(int i = 0; i < c; i++) pthread_create(&thread[i], NULL, getSeat, &s[i]);
    for(int i = 0; i < c; i++) pthread_join(thread[i], NULL);
}


void* reachStadium(void* arg)
{
    PersonInfo s = *(PersonInfo*)arg;

    int G = s.group_no;
    int P = s.person_no;

    pthread_mutex_lock(&lock);
        printc(Group[G].Person[P].Name);
        printc(" has reached the stadium\n");
        // a();
        // printf("this = %c\n", Group[G].Person[P].SupportTeam);

        if(Group[G].Person[P].SupportTeam == 'H')
        {
            if(isZoneFull(HOME) && isZoneFull(NEUT))
                noSeat(G, P);
            else if(isZoneFull(HOME))
                seatN(G, P);
            else if(isZoneFull(NEUT))
                seatH(G, P);
            else
            {
                if(Prob(0.5))
                    seatH(G, P);
                else
                    seatN(G, P);
            }
        }
        if(Group[G].Person[P].SupportTeam == 'A')
        {
            if(isZoneFull(AWAY))
                noSeat(G, P);
            else
                seatA(G, P);
        }
        if(Group[G].Person[P].SupportTeam == 'N')
        {
            // a();
            if(isZoneFull(HOME) && isZoneFull(AWAY) && isZoneFull(NEUT))
                noSeat(G, P);
            else if(isZoneFull(HOME) && isZoneFull(AWAY))
                seatN(G, P);
            else if(isZoneFull(HOME) && isZoneFull(NEUT))
                seatA(G, P);
            else if(isZoneFull(AWAY) && isZoneFull(NEUT))
                seatH(G, P);
            else if(isZoneFull(HOME))
            {
                if(Prob(0.5))
                    seatA(G, P);
                else
                    seatN(G, P);
            }
            else if(isZoneFull(AWAY))
            {
                if(Prob(0.5))
                    seatH(G, P);
                else
                    seatN(G, P);
            }
            else if(isZoneFull(NEUT))
            {
                if(Prob(0.5))
                    seatH(G, P);
                else
                    seatA(G, P);
            }
            else
            {      
                if(Prob(0.33))
                    seatH(G, P);
                else if(Prob(0.67))
                    seatN(G, P);
                else
                    seatA(G, P);
            }
        }
    
    pthread_mutex_unlock(&lock);

    return NULL;
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