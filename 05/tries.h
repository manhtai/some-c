#include <stdbool.h>
#include <string.h>


// Trie for words
typedef struct node
{
    struct node* children[27];
    bool word;
    unsigned int size;
}
node;

// Init root for trie
void trie_init(node* trie);

// Append word to trie
bool trie_append(node* trie, char* string);

// Lookup a word in trie
bool trie_lookup(node* trie, const char* string);

// Size of trie
unsigned int trie_size(node* trie);

// Free trie memory
bool trie_free(node* trie);

// Get index
int get_index(char c);
