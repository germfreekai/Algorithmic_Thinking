/*
 * Verify whether two snowflakes are identical.
 * A snowflake is made out of 6 integers.
 * A snowflake could be identical if by spinning the given
 * ints, either to the left or to the right we get the same
 * order (like a circle)
 * You will receive N snowflakes, time limit 2 seconds
 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 100000

// Sample easy function
void identify_identical(int **snowflakes, int size);

// Main function
int are_identical(int *snow1, int *snow2);
// Helper functions
int identical_right(int *snow1, int *snow2, int start_s2);
int identical_left(int *snow1, int *snow2, int start_s2);

// Doing less work
// Weed out some options
int code(int *snow);

// Now we will create a linked list
typedef struct _snowflake_node
{
    int *snowflake;
    struct snowflake_node *next;
}snowflake_node;

int main(void)
{
    static snowflake_node *snowflakes[SIZE] = {NULL};
    snowflake_node *snow;

    int **snowflakes = (int**)calloc(SIZE, sizeof(int*));

    int n, i, j;

    scanf("%d", &n);
    for (i = 0; i < n; i++)
        snowflakes[i] = (int*)calloc(6, sizeof(int));

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < 6; j++)
        {
            scanf("%d", &snowflakes[i][j]);
        }
    }

    identify_identical(snowflakes, n);

    for (i = 0; i < n; i++)
        free(snowflakes[i]);
    free(snowflakes);

    return EXIT_SUCCESS;
}

void identify_identical(int **snowflakes, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (are_identical(snowflakes[i], snowflakes[j]))
            {
                fprintf(stdout, "Twin snowflakes found!\n");
                return;
            }
        }
    }
    fprintf(stderr, "No twin snowflakes found\n");
}

int identical_right(int *snow1, int *snow2, int start_s2)
{
    int offset;
    for (offset = 0; offset < 6; offset++)
    {
        /*
         * Mod returns the remaining, so if we divide we will
         * always get a smaller number than snow2 len
         */
        if (snow1[offset] != snow2[(start_s2 + offset) % 6])
            return 0;
    }
    return 1;
}

int identical_left(int *snow1, int *snow2, int start_s2)
{
    int offset;
    int snow2_index;

    for (offset = 0; offset < 6; offset++)
    {
        snow2_index = start_s2 - offset;
        if (snow2_index < 0)
            snow2_index = snow2_index + 6;
        if (snow1[offset] != snow2[snow2_index])
            return 0;
    }
    return 1;
}

int are_identical(int *snow1, int *snow2)
{
    for (int start = 0; start < 6; start++)
    {
        if (identical_right(snow1, snow2, start))
            return 1;
        if (identical_left(snow1, snow2, start))
            return 1;
    }
    return 0;
}

int code(int *snow)
{
    int sum = 0;
    for (int i = 0; i < 6; i++)
        sum += snow[i];
    // We mod SIZE to make sure the number
    // is not to high - somewhere between
    // 0 - 99999
    return sum % SIZE;
}
