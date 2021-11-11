#include "libraries.h"

void flushSTDIN()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Debugging
void a()
{
    printf("Fish\n");
}

// Random number between 0 and 1
int P(float n)
{
    if(n == 1) return 1;

    srand(time(0));
    float p = (float)rand() / (float)RAND_MAX;
    return (p < n);
}

// Color print
void printb(char s[])
{
    printf(COLOR_BLUE "%s" COLOR_RESET, s);
}
void printr(char s[])
{
    printf(COLOR_RED "%s" COLOR_RESET, s);
}
void printrn(int n)
{
    printf(COLOR_RED "%d" COLOR_RESET, n);
}
void printg(char s[])
{
    printf(COLOR_GREEN "%s" COLOR_RESET, s);
}
void printgn(int n)
{
    printf(COLOR_GREEN "%d" COLOR_RESET, n);
}
void printm(char s[])
{
    printf(COLOR_MAGENTA "%s" COLOR_RESET, s);
}
void printmn(int n)
{
    printf(COLOR_MAGENTA "%d" COLOR_RESET, n);
}
void printc(char s[])
{
    printf(COLOR_CYAN "%s" COLOR_RESET, s);
}
void printcn(int n)
{
    printf(COLOR_CYAN "%d" COLOR_RESET, n);
}
void printy(char s[])
{
    printf(COLOR_YELLOW "%s" COLOR_RESET, s);
}
void printyn(int n)
{
    printf(COLOR_YELLOW "%d" COLOR_RESET, n);
}