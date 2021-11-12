#include "libraries.h"
#include "variables.h"
#include "functions.h"
// #include "utility.h"
#include "input.c"
#include "reach.c"
#include "goal.c"

void main()
{
    printf(COLOR_YELLOW "Simulation has started!\n" COLOR_RESET);
    input();

    printGroup(0);
    printGroup(1);

    getSpectators(1);

    scoreGoal(1);
    scoreGoal(2);
    scoreGoal(3);
    scoreGoal(4);
    scoreGoal(5);
    scoreGoal(6);
}