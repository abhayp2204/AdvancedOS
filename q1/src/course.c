#include "libraries.h"
#include "variables.h"
#include "functions.h"

void* courseFunction(void* arg)
{
    // pthread_mutex_lock(&lock);
    int i = *(int*)arg;
    // pthread_mutex_unlock(&lock);

    allocateMentor(i);

    return NULL;
}

void allocateMentor(int C)
{
    // Course already occupied
    if(Course[C].Status == OCCUPIED)
        return;

    // Iterate through course's lab id's
    for(int i = 0; i < Course[C].NumLabs; i++)
    {
        tLab L = Lab[Course[C].LabID[i]];
        
        // Iterate though the lab's mentors
        for(int j = 0; j < L.NumMentors; j++)
        {
            tMentor M = L.Mentor[j];

            // Mentor is taking sesh
            if(M.Status == OCCUPIED)
                continue;

            // Allocate M to C
            Course[C].Status = OCCUPIED;
            Lab[Course[C].LabID[i]].Mentor[j].Status = OCCUPIED;
            printf(COLOR_CYAN "TA %d from lab %s has been allocated to course %s for his %d TA ship\n" COLOR_RESET,
                j, L.Name, Course[C].Name, ++Lab[Course[C].LabID[i]].Mentor[j].Num);

            numSlots(C);
            allocateSeats(C);
            
            return;
        }
    }
}

void numSlots(int i)
{
    Course[i].Slots = randint(Course[i].MaxSlots);
    printf(COLOR_YELLOW "Course %s has been allocated %d seats\n" COLOR_RESET, Course[i].Name, Course[i].Slots);
}

void allocateSeats(int C)
{
    for(int i = 0; i < numStudents; i++)
    {
        if(Student[i].Status == NOT_FILLED)
            continue;

        if(Course[C].SlotsFilled == Course[C].Slots)
            return;

        if(Student[i].Pref[Student[i].Current] == Course[C].CourseID)
        {
            printf(COLOR_RED "Student %d has been allocated a seat in course %s\n" COLOR_RESET, i, Course[C].Name);
            // printf("pref = %s current = %d\n", Course[Student[i].Pref[Student[i].Current]].Name, Student[i].Current);
            Course[C].SlotsFilled++;
        }
    }
}