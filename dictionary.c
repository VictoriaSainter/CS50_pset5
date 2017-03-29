#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "dictionary.h"



#define SIZE 5129

typedef struct node
{
    char word[LENGTH+1];
    struct node* next;
}
node;


node* hashtable[SIZE] = {NULL};


int hash (const char* word)
{
    int hash = 0;
    int n;
    for (int i = 0; word[i] != '\0'; i++)
    {
 
        if(isalpha(word[i]))
            n = word [i] - 'a' + 1;
        
       
        else
            n = 27;
            
        hash = ((hash << 3) + n) % SIZE;
    }
    return hash;    
}


int numOfDictionaryNodes = 0;

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{

    FILE* file = fopen(dictionary, "r");
    if (file == NULL)
        return false;
    

    char word[LENGTH+1];
    

    while (fscanf(file, "%s\n", word)!= EOF)
    {

        numOfDictionaryNodes++;
        

        node* newNode = malloc(sizeof(node));
        

        strcpy(newNode->word, word);
        

        int index = hash(word);
        

        if (hashtable[index] == NULL)
        {
            hashtable[index] = newNode;
            newNode->next = NULL;
        }
        
        // if hashtable is not empty at index, append
        else
        {
            newNode->next = hashtable[index];
            hashtable[index] = newNode;
        }      
    }
    
    // close file
    fclose(file);
    
    // return true if successful 
    return true;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{

    char tempStorage[LENGTH + 1];
    int len = strlen(word);
    for(int i = 0; i < len; i++){
        tempStorage[i] = tolower(word[i]);
        }
    tempStorage[len] = '\0';
    

    int index = hash(tempStorage);
    

    if (hashtable[index] == NULL)
    {
        return false;
    }

    node* pointer = hashtable[index];
    
    while (pointer != NULL)
    {
        if (strcmp(tempStorage, pointer->word) == 0)
        {
            return true;
        }
        pointer = pointer->next;
    }
    

    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{

    if (numOfDictionaryNodes > 0)
    {
        return numOfDictionaryNodes;
    }
     

    else
        return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{

    int index = 0;
    

    while (index < SIZE)
    {

        if (hashtable[index] == NULL)
        {
            index++;
        }
        
        
        else
        {
            while(hashtable[index] != NULL)
            {
                node* pointer = hashtable[index];
                hashtable[index] = pointer->next;
                free(pointer);
            }
            
            
            index++;
        }
    }
    
    
    return true;
}
