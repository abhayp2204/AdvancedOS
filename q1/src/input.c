#include "libraries.h"
#include "variables.h"
// #include "functions.h"
#include "utility.h"

void input()
{
    printf(COLOR_BLUE "#Students | #Labs | #Courses\n" COLOR_RESET);
    scanf("%d %d %d", &numStudents, &numLabs, &numCourses);

    inputCourses();
    inputStudents();
    inputLabs();
}

void inputCourses()
{
    Course = (tCourse*)malloc(numCourses * sizeof(tCourse));
    for(int i = 0; i < numCourses; i++)
    {
        // Prefix
        printf(COLOR_RED "C%d: " COLOR_RESET, i+1);

        // Set Course ID
        Course[i].CourseID = i;

        // Input course variables
        scanf("%s %f %d %d", 
                &Course[i].Name,
                &Course[i].Interest,
                &Course[i].MaxSlots,
                &Course[i].NumLabs);

        // Input lab id's for this course
        Course[i].LabID = (int*)malloc(Course[i].NumLabs * sizeof(int));
        for(int j = 0; j < Course[i].NumLabs; j++)
        {
            scanf("%d", &Course[i].LabID[j]);
        }
    }
}

void inputStudents()
{
    Student = (tStudent*)malloc(numStudents * sizeof(tStudent));

    // Iterate through all the students
    for(int i = 0; i < numStudents; i++)
    {
        flushSTDIN();

        // Prefix
        printf(COLOR_CYAN "S%d: " COLOR_RESET, i+1);

        // Set student ID
        Student[i].StudentID = i;
        Student[i].Current = 0;

        // Input student variables
        scanf("%f %d %d %d %d", 
                &Student[i].Calibre,
                &Student[i].Pref[0],
                &Student[i].Pref[1],
                &Student[i].Pref[2],
                &Student[i].FillTime);
    }
}


void inputLabs()
{
    Lab = (tLab*)malloc(numLabs * sizeof(tLab));

    for(int i = 0; i < numLabs; i++)
    {
        flushSTDIN();

        // Prefix
        printf(COLOR_GREEN "L%d: " COLOR_RESET, i+1);

        // Input goal variables
        scanf("%s %d %f", 
                &Lab[i].Name,
                &Lab[i].NumMentors,
                &Lab[i].MaxTA);
    }   
    printf("\n");
}