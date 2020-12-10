#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hashMap.h"

#define TABLE_SIZE 100

/*
 the getWord function takes a FILE pointer and returns you a string which was
 the next word in the in the file. words are defined (by this function) to be
 characters or numbers separated by periods, spaces, or newlines.
 
 when there are no more words in the input file this function will return NULL.
 
 this function will malloc some memory for the char* it returns. it is your job
 to free this memory when you no longer need it.
 */
char *getWord(FILE *file); /* prototype */

/****************************************/


int main(int argc, const char *argv[]) {
    FILE *file;
    char *string;
    int i, *count;
    hashMap *ht;
    assert(argc == 2);
    file = fopen(argv[1], "r");
    ht = malloc(sizeof(hashMap));
    initMap(ht, TABLE_SIZE);
    
	 string = getWord(file);
    while (string != NULL) {
        count = atMap(ht, string);
        if (count == NULL) {
            insertMap(ht, string, 1);
        } 
		  else if (count != NULL){
            insertMap(ht, string, *count+1);
        }
        string = getWord(file);
    }
    
	 for (i = 0; i < ht->tableSize; i++) {
        hashLink *cur = ht->table[i];
        while (cur != NULL) {
            printf("%s: %d\n", cur->key, cur->value);
            cur = cur->next;
        }
    }

    freeMap(ht);
    fclose(file);
    return 0;
}


char *getWord(FILE *file) {

    int length = 0;
    int maxLength = 16;
    char character;

    char *word = (char *) malloc(sizeof(char) * maxLength);
    assert(word != NULL);

    while ((character = fgetc(file)) != EOF) {
        if ((length + 1) > maxLength) {
            maxLength *= 2;
            word = (char *) realloc(word, maxLength);
        }
        if ((character >= '0' && character <= '9') || /*is a number*/
            (character >= 'A' && character <= 'Z') || /*or an uppercase letter*/
            (character >= 'a' && character <= 'z') || /*or a lowercase letter*/
            character == 39) /*or is an apostrophy*/
        {
            word[length] = character;
            length++;
        } else if (length > 0)
            break;
    }

    if (length == 0) {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

