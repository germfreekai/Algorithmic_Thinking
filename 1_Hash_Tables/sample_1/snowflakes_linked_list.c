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

// Now we will create a linked list
typedef struct snowflake_node
{
    int *snowflake;
    struct snowflake_node *next;
}snowflake_node;

// Sample easy function
void identify_identical(snowflake_node **snowflake);

// Main function
int are_identical(int *snow1, int *snow2);
// Helper functions
int identical_right(int *snow1, int *snow2, int start_s2);
int identical_left(int *snow1, int *snow2, int start_s2);

// Doing less work
// Weed out some options
int code(int *snow);

int main(void)
{
    // This will be an array of linked lists
    // each existing index will have a linked list
    // of nodes that have that 'snowflake_code'
    static snowflake_node *snowflakes[SIZE] = {NULL};
    // This will be a "pointer" to nodes
    snowflake_node *snow;

    int n, i, j, snowflake_code;

    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        // Allocate memory per node
        snow = malloc(sizeof(snowflake_node));
        snow->snowflake = (int*)calloc(6, sizeof(int));

        if (snow == NULL)
        {
            fprintf(stderr, "malloc error\n");
            exit(1);
        }
        // Read numbers
        for (j = 0; j < 6; j++)
            scanf("%d", &snow->snowflake[j]);
        // Get code value
        snowflake_code = code(snow->snowflake);
        // Point the inserted node's next pointer
        // to the first node in the lsit
        snow->next = snowflakes[snowflake_code];
        // set the start of the lsit to point to the inserted nodes.
        snowflakes[snowflake_code] = snow;
    }

    identify_identical(snowflakes);

    // Free allocated memory
    for (int i = 0; i < SIZE; i++)
    {
        snowflake_node *current = snowflakes[i];
        while (current != NULL)
        {
            snowflake_node *next = current->next;
            free(current->snowflake); // Free the snowflake array
            free(current); // Free the node
            current = next;
        }
    }
    return EXIT_SUCCESS;
}

void identify_identical(snowflake_node **snowflake)
{
    snowflake_node *node1, *node2;
    
    for (int i = 0; i < SIZE; i++)
    {
        // Get first node at the linked list
        node1 = snowflake[i];
        while (node1 != NULL)
        {
            // Use node 2 to traverse to the right from
            // node 1 - this basically compares the first
            // node at the linked list to all other ones
            // at the right
            node2 = node1->next;
            while (node2 != NULL)
            {
                if (are_identical(node1->snowflake, node2->snowflake))
                {
                    fprintf(stdout, "Twin snowflakes found\n");
                    return;
                }
                node2 = node2->next;
            }
            // Move node 1 to the following position and
            // once again compare against all the other
            // nodes to the right
            node1 = node1->next;
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
