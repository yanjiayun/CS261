#include <stdlib.h>
#include "hashMap.h"
#include "structs.h"
#include <string.h>

int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between 1 and 2 is on this line*/
	return r;
}

void initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

void freeMap (struct hashMap * ht)
{  
	int i;
	if (ht == NULL){
		return;
	}
	for(i=0;i<ht->tableSize;++i){
		hashLink *prev, *temp;
		temp = ht->table[i];
		while(temp != NULL){
			free(temp->key);
			prev = temp;
			temp = temp->next;
			free(prev);
		}
	}
	free(ht->table);
	free(ht);
}

void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{ 
  	hashLink* temp;
	int hashIndex;
	int a;
	if(ht == NULL || k == NULL){
		return;
	}
	hashIndex = stringHash1(k)%ht->tableSize;
	temp = ht->table[hashIndex];
	a = containsKey(ht,k);
	if(a == 1){
		while(strcmp(temp->key,k) !=0){
			temp = temp->next;
		}
		temp->value = v;
		free(k);
	}
	else{
		hashLink* newLink = malloc(sizeof(hashLink));
		newLink->key = k;
		newLink->value = v;
		newLink->next = temp;
		ht->table[hashIndex] = newLink;
		ht->count++;
	}
}

ValueType* atMap (struct hashMap * ht, KeyType k)
{ 	
	hashLink *cur;
	int hashIndex;
	if(ht == NULL){
		return NULL;
	}
	hashIndex = stringHash1(k)%ht->tableSize;
	cur = ht->table[hashIndex];
	while(cur != NULL){
		if(strcmp(cur->key,k) == 0){
			return &cur->value;
		}
		cur = cur->next;
	}
	return NULL;
}

int containsKey (struct hashMap * ht, KeyType k)
{  
 	hashLink *cur;
	int hashIndex;
	if(ht == NULL){
		return 0;
	}
	hashIndex = stringHash1(k)%ht->tableSize;
	cur = ht->table[hashIndex];
	while(cur != NULL){
		if(strcmp(cur->key,k)==0){
			return 1;
		}
		cur = cur->next;
	}
	return 0;
}


void removeKey (struct hashMap * ht, KeyType k)
{ 	
	hashLink *last, *cur;
	int hashIndex;
	hashIndex = stringHash1(k)%ht->tableSize;
	if(ht == NULL || k == NULL){
		return;
	}
	cur = ht->table[hashIndex];
	while(cur != NULL){
		if(k == cur->key){
			free(cur->key);
			if(last != NULL){
				last->next = cur->next;
			}
			else{
				ht->table[hashIndex] = last->next;
			}
			free(cur);
			ht->count--;
		}
		else{
			last = cur;
			cur = cur->next;
		}
	}
}

int sizeMap (struct hashMap *ht)
{  
	if(ht == NULL){
		return 0;
	}
	else{
		return ht->count;
	}
}

int capacityMap(struct hashMap *ht)
{  
	if(ht == NULL){
		return 0;
	}
	else{
		return ht->tableSize;
	}
}

int emptyBuckets(struct hashMap *ht)
{	
	int i;
	int a=0; 
	for(i=0; i<ht->tableSize; i++){
		if(ht->table[i] == NULL){
			a++;
		}
	}
	return a;
}

float tableLoad(struct hashMap *ht)
{  
	if(ht == NULL){
		return 0;
	}
	else{
		return (ht->tableSize-emptyBuckets(ht))*1.0/ht->tableSize;
	}
}
