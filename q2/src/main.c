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

    // printGroup(0);
    // printGroup(1);


    getSpectators(1);
    printZone(HOME);
    scoreGoal(1);
    // leave();
}