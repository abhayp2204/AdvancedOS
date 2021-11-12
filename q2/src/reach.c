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

        if(Group[G].Person[P].SupportTeam == 'H')
        {
            if(isZoneFull(HOME) && isZoneFull(NEUT))
                printm(strcat(Group[G].Person[P].Name, " could not get a seat\n"));
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
                printm(strcat(Group[G].Person[P].Name, " could not get a seat\n"));
            else
                seatA(G, P);
        }
        if(Group[G].Person[P].SupportTeam == 'N')
        {
            if(isZoneFull(HOME) && isZoneFull(AWAY) && isZoneFull(NEUT))
                printm(strcat(Group[G].Person[P].Name, " could not get a seat\n"));
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

int isZoneFull(int i)
{
    return (Zone[i].NumSpectators == Zone[i].Capacity);
}

void seatH(int G, int P)
{
    Zone[HOME].Spectator[Zone[HOME].NumSpectators] = Group[G].Person[P];
    Zone[HOME].NumSpectators++;
    printm(strcat(Group[G].Person[P].Name, " has got a seat in zone H\n"));
}
void seatA(int G, int P)
{
    Zone[AWAY].NumSpectators++;
    printm(strcat(Group[G].Person[P].Name, " has got a seat in zone A\n"));
}
void seatN(int G, int P)
{
    Zone[NEUT].NumSpectators++;
    printm(strcat(Group[G].Person[P].Name, " has got a seat in zone N\n"));
}

void printStruct(int c)
{
    for(int i = 0; i < c; i++)
        printf("(%d, %d)\n", s[i].group_no + 1, s[i].person_no + 1);
}