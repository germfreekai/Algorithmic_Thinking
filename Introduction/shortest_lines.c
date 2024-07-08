/*
 * Shortest lines problem
 * You have N lines and incoming people queue
 * in the shortest available line
 */ 

#include <stdio.h>
#include <stdlib.h>

#define MAX_LINES 100

int shortest(int *lines, int size);
void solve(int *lines, int line, int people);

int main(void)
{
    int *lines = (int*)calloc(MAX_LINES, sizeof(int));

    int line, people;

    scanf("%d%d", &line, &people);

    for (int i = 0; i < line; i++)
        scanf("%d", &lines[i]);

    solve(lines, line, people);

    free(lines);

    return EXIT_SUCCESS;
}

int shortest(int *lines, int size)
{
    int min = 0;
    for (int i = 0; i < size; i++)
        if (lines[i] < lines[min])
            min = i;
    return min;
}
void solve(int *lines, int line, int people)
{
    int shortest_line;
    for (int i = 0; i < people; i++)
    {
        shortest_line = shortest(lines, line);
        fprintf(stdout, "%d\n", lines[shortest_line]);
        lines[shortest_line]++;
    }
}
