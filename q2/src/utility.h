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