/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"

#include "tries.h"

node trie;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    return trie_lookup(&trie, word);
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // Open dictionary file
    FILE* dic = fopen(dictionary, "r");
    if (dic == NULL)
        return false;

    // Init trie
    trie_init(&trie);

    // Load words from dictionary
    char word[LENGTH+2];
    while (fgets(word, LENGTH+2, dic))
    {
        word[strlen(word) - 1] = '\0';
        trie_append(&trie, word);
    }
    
    // Remember closing file
    fclose(dic);

    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return trie_size(&trie);
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    return trie_free(&trie);
}
