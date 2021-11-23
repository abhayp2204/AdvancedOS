// Each person is a thread
// Each TA is a lock

// Libraries
#include "libraries.h"
#include "variables.h"
#include "functions.h"
#include "input.c"
#include "student.c"
#include "course.c"
// #include "seat.c"
// #include "goal.c"
// #include "leave.c"

void main()
{
    printf(COLOR_YELLOW "Simulation has started!\n" COLOR_RESET);
    input();
    printf("------------------------------------------------------------------------\n");

    // Thread for each student
    thStudent = (pthread_t*)malloc(numStudents * sizeof(pthread_t));
    for(int i = 0; i < numStudents; i++)
    {
        pthread_create(&thStudent[i], NULL, studentFunction, &i);
        usleep(20);
    }

    sleep(1);

    // Thread for each course
    thCourse = (pthread_t*)malloc(numCourses * sizeof(pthread_t));
    for(int i = 0; i < numCourses; i++)
    {
        pthread_create(&thCourse[i], NULL, courseFunction, &i);
        usleep(20);
    }

    threadExit();
}
    /*
    // Person Threads
    tPersonID PersonID[num_people];
    int c = 0;
    for (int i = 0; i < num_groups; i++)
    {
        // Each group has k members, hence a thread array of size k
        Group[i].th[Group[i].k];

        // Pass (Group-No, Person-No) to each thread to identify the person
        for (int j = 0; j < Group[i].k; j++)
        {
            PersonID[c].groupNo = i;
            PersonID[c].personNo = j;
            pthread_create(&Group[i].th[j], NULL, person_function, &PersonID[c++]);
        }
    }

    // Goal Threads
    for(int i = 0; i < G; i++)
    {
        pthread_create(&goal_thread[i], NULL, goal_function, &i);
        usleep(50);
    }

    // Join threads
    join();

    printf("------------------------------------------------------------------------\n");
}
*/

void threadExit()
{
    // Exit student threads
    for (int i = 0; i < numStudents; i++)
    {
        pthread_exit(thStudent[i]);
    }
    // Exit course threads
    for (int i = 0; i < numCourses; i++)
    {
        pthread_exit(thCourse[i]);
    }
    // Exit student threads
    for (int i = 0; i < numLabs; i++)
    {
        pthread_exit(thLab[i]);
    }
}