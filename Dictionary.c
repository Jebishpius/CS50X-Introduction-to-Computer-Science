// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    bool is_word;
    struct node* children[46];
    // char word[LENGTH + 1];
    //struct node *next;
}
node;
node* first;

int word_count = 0;


#define MULTIPLIER (37);
int get_index(char c);
node* create_init_node();
bool unload_helper(node* node_ptr);

// Number of buckets in hash table
//const unsigned int N = 26;
int counter_word = 0;

// Number of buckets in hash table
const unsigned int N = 10;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node* node_ptr = first;
    for(int i = 0, len = strlen(word); i <= len+1; i++)
    {

        if( word[i] == '\0')
        {
            if (node_ptr->is_word == true)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        int index = get_index(word[i]);
        if (node_ptr->children[index] == NULL)
        {
            return false;
        }
        node_ptr = node_ptr->children[index];
    }
    // TODO
    return false;
}


// Hashes word to a number
/*
unsigned int hash(const char *word)
{
    // TODO
    unsigned const char *us;
    unsigned long h;

       h = 0;

       for(us = (unsigned const char *) word; *us; us++) {
           h = h * MULTIPLIER + *us;
       }

       return h;
  //  return 0;
}*/

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE* dict_ptr = fopen(dictionary, "r");
    if (dict_ptr == NULL){
    return false;
    }
    first = create_init_node();

   int index;
    node* node_ptr = first;
    for (char c = fgetc(dict_ptr); c != EOF; c = fgetc(dict_ptr))
    {
        if (c != '\n'){
            // node_ptr  = create_init_node();
            index = get_index(c);
            if (node_ptr->children[index]== NULL)
            {
                node_ptr->children[index] = create_init_node();
            node_ptr = node_ptr->children[index];
            }
        }
        else{
            node_ptr->is_word = true;
            word_count++;
            node_ptr = first;
        }

    }
    // TODO
    return true;
}
int get_index(char c)
{
    if (c == '\'')
    {
        return 45;
    }
    else if (c >= 'a' && c <= 'z')
    {
        return c - 'a';
    }
    else if (c >= 'A' && c <= 'Z')
    {
        return c - 'A';

    }
    else
    {
    return -1;
    }
}


node* create_init_node()
{
    node* node_ptr = malloc(sizeof(node));
    node_ptr->is_word = false;
    for(int i = 0; i <46;i++){
        node_ptr->children[i] = NULL;
    }
    return node_ptr;
}
// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    if(unload_helper(first))
    {
        return true;
    }
    return false;
}

bool unload_helper(node* node_ptr)
{
    for(int i =0 ; i <46; i++)
    {

    if (node_ptr->children[i]!=NULL)
    {
        unload_helper(node_ptr->children[i]);
    }
    }
    free(node_ptr);
    return true;
}
