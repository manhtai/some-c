#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "tries.h"


// Init root for trie
void trie_init(node* trie)
{
    trie->word = false;
    trie->size = 0;
}


// Append word to trie
bool trie_append(node* trie, char* string)
{
    node* cusor = trie;
    for (int i = 0, l = strlen(string); i < l; i++)
    {
        int index = get_index(string[i]);
        if (cusor->children[index] == NULL)
        {
            cusor->children[index] = (node*) malloc(sizeof(node));
            if (cusor->children[index] == NULL)
                return false;
        }
        cusor = cusor->children[index];
        if (i == l-1)
        {
            cusor->word = true;
            trie->size++;
        }
    }
    return true;
}

// Lookup a word in trie
bool trie_lookup(node* trie, const char* string)
{
    node* cusor = trie;
    bool result;
    for (int i = 0, l = strlen(string); i < l; i++)
    {
        int index = get_index(string[i]);
        if (cusor->children[index] == NULL)
            return false;
        else
            cusor = cusor->children[index];
    }
    result = (cusor->word == true) ? (true) : (false);
    return result;
}

// Size of trie
unsigned int trie_size(node* trie)
{
    return trie->size;
}

// Free trie memory
bool trie_free(node* trie)
{
    node* cusor = trie;
    for (int i = 0; i < 27; i++)
        if (cusor->children[i] != NULL)
            trie_free(cusor->children[i]);
    for (int i = 0; i < 27; i++)
        free(cusor->children[i]);
    return true;
}


// Get index
int get_index(char c)
{
    if (c == '\'')
        return 26;
    else
        return tolower(c) - 'a';
}
