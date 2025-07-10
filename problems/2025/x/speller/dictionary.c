#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Set buckets in hash table
#define N 2000

// Hash table
node *table[N];
int total_words = 0;

char *toLowercase(const char *str)
{
    size_t len = strlen(str) + 1;
    char *dest = malloc(len);

    if (dest == NULL)
    {
        return NULL;
    }

    for (size_t i = 0; i < len; i++)
    {
        dest[i] = tolower((unsigned char) str[i]);
    }

    return dest;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char *word_lower = toLowercase(word);
    if (word_lower == NULL)
    {
        return false;
    }

    unsigned int wordHash = hash(word_lower);
    node *cursor = table[wordHash];

    while (cursor != NULL)
    {
        if (strcmp(word_lower, cursor->word) == 0)
        {
            free(word_lower);
            return true;
        }
        cursor = cursor->next;
    }

    free(word_lower);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int sumASCII = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        sumASCII += tolower(word[i] - 'A');
    }
    return sumASCII;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open input file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) == 1)
    {
        if (strlen(word) > LENGTH)
        {
            fprintf(stderr, "Word too long: %s\n", word);
            continue;
        }

        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            perror("Memory allocation error");
            fclose(file);
            return false;
        }

        char *word_lower = toLowercase(word);
        strncpy(n->word, word_lower, LENGTH);
        free(word_lower);
        n->word[LENGTH] = '\0';
        n->next = NULL;

        unsigned int word_hash = hash(word);

        if (table[word_hash] == NULL)
        {
            table[word_hash] = n;
            total_words++;
        }
        else
        {
            n->next = table[word_hash];
            table[word_hash] = n;
            total_words++;
        }
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return total_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        if (head != NULL)
        {
            free(head);
            continue;
        }

        node *ptr = table[i];
        while (ptr)
        {
            node *eraser = ptr;
            ptr = ptr->next;
            free(eraser);
        }
    }
    free(*table);
    return true;
}