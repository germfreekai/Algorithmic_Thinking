#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_BITS 17
#define WORD_LENGTH 16

typedef struct word_node
{
    char **word;
    struct word_node *next;
}word_node;

char *read_line(int size);
int in_hash_table(word_node *hash_table[], char *find, unsigned find_len);
void identify_compound_words(char *words[], word_node *hash_table[], int total_words);

int main(void)
{
    static char *words[1 << NUM_BITS] = {NULL};  // use left shift to get the max size
    static word_node *hash_table[1 << NUM_BITS] = {NULL};  // use left shift to get the max size
    int total = 0;
    char *word;
    word_node *wordptr;
    unsigned length, word_code;
    word = read_line(WORD_LENGTH);

    while (*word) {
        words[total] = word;  // store each word (read by read_line) in the words array
        wordptr = malloc(sizeof(word_node));
        if (wordptr == NULL)
        {
            fprintf(stderr, "malloc error\n");
            exit(EXIT_FAILURE);
        }
        length = strlen(word);
        word_code = oaat(word, length, NUM_BITS);

        wordptr->word = &words[total];
        wordptr->next = hash_table[word_code];  // store a pointer to each word in the hash table

        hash_table[word_code] = wordptr;  // 5
        word = read_line(WORD_LENGTH);
        total++;
    }

    identify_compound_words(words, hash_table, total);

    return EXIT_SUCCESS;
}

char *read_line(int size)
{
    char *str;
    int ch;
    int len = 0;
    str = malloc(size);

    if (str == NULL)
    {
        fprintf(stderr, "malloc error\n");
        exit(EXIT_FAILURE);
    }

    while ( (ch = getchar()) != EOF && (ch != '\n') )
    {
        str[len++] = ch;
        if (len == size)
        {
            size = size * 2;
            str = realloc(str, size);
            if (str == NULL)
            {
                fprintf(stderr, "realloc error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    str[len] = '\n';

    return str;
}

int in_hash_table(word_node *hash_table[], char *find, unsigned find_len)
{
    unsigned word_code;
    word_node *wordptr;
    word_code = oaat(find, find_len, NUM_BITS);  // calculate the hashcode of the word
    wordptr = hash_table[word_code];  // use the hascode to find the appropiate linked list to search at

    // the hash table contains pointers to strings *(wordptr->word)
    while (wordptr)
    {
        // we give a len to strcmp to compare a subset of a given string (e.g read -> readable)
        if ( (strlen(*(wordptr->word)) == find_len) && (strcmp(*(wordptr->word), find, find_len) == 0) )
            return 1;
        wordptr = wordptr->next;
    }
    return 0;
}

void identify_compound_words(char *words[], word_node *hash_table[], int total_words)
{
    int i, j;
    unsigned len;

    for (i = 0; i < total_words; i++)  // generate splits for each word
    {
        len = strlen(words[i]);

        /*
         * searches the has table for both the prefix string (prior to the split point)
         * and suffix string (from the split point on) where 'j' is the split point
         */
        for (j = 1; j < len; j++)
        {
            /*
             * first search is for the first 'j' characters of word 'i'
             * second searches for the piece of word 'i' beginning at index 'j' (with length len - j)
             * if both searches are successfull, then the current word is a compound word
             *
             * We use array 'words' to print the words in a sorted way (as read)
             */
            if (in_hash_table(hash_table, words[i], j) && in_hash_table(hash_table, &words[i][j], len - j))
            {
                fprintf(stdout, "%s\n", words[i]);
                break;  // stop at first finding
            }
        }
    }
}
