#include "collection.h"
#include <stdio.h>
#include <stdlib.h>

unsigned long binary_search(unsigned long *set_target, COLLECTION collection, long begin, long end);

/* I dont like global variables either, but I needed memory space */
/* Vector indexed according to the size of sets (-1) */

int main() {
	char c_input;
	unsigned long temp_n;
	unsigned short size_set;
	unsigned long *temp_set = NULL;
	unsigned int x = 0;
	x+=x;
	/* Reads the value of the largest element that can appear in sets */
	x =scanf("%lu", &temp_n);
	get_SIZE_MAX_SETS(1, temp_n);

	/* The major_collection is a collections vector that is indexed by the size of the sets */
	COLLECTION *major_collection = (COLLECTION *) calloc (get_SIZE_MAX_SETS(0,0)+1, sizeof(COLLECTION));
	
	x =scanf("%c", &c_input);
	while(c_input != '0'){
		switch(c_input) {
			case '+':
				/* Size of the set */
				x =scanf("%hu", &size_set);

				/* Allocate the collection if it isnt already allocated */
				if(major_collection[size_set-1].sets == NULL){
					major_collection[size_set-1].sets = (unsigned long **) malloc (QTT_MAX_SETS * sizeof(unsigned long *));
				}

				/* If collection is empty, just read in first position */
				if(major_collection[size_set-1].size == 0) {
					readSet(&(major_collection[size_set-1].sets[0]), size_set);
					++major_collection[size_set-1].size;
					
					printf("0\n");
				}
				else {
					/* Read the set in a temporary */
					readSet(&temp_set, size_set);
				
					/* Seach for the set in collection */
					temp_n = binary_search(temp_set, major_collection[size_set-1], 0, major_collection[size_set-1].size-1);
					if(temp_n != -1){
						printf("E\n0\n");
					}
					else{
						/* Orderly insertion */
						insertSet(&major_collection[size_set-1], temp_set, size_set);

						printf("0\n");
					}
				}
				break;
			case '-':
				/* Size of the set */
				x =scanf("%hu", &size_set);

				/* Read the set in a temporary */
				readSet(&temp_set, size_set);
				
				/* Seach for the set in collection */
				temp_n = binary_search(temp_set, major_collection[size_set-1], 0, major_collection[size_set-1].size-1);
				if(temp_n == -1){
					printf("E\n0\n");
				}
				else{
					/* Remove set from collection */
					removeSet(&major_collection[size_set-1], temp_n);
					printf("0\n");
				}
				break;
			case '=':
				/* Size of the set */
				x =scanf("%hu", &size_set);	

				/* Read the set in a temporary */
				readSet(&temp_set, size_set);
				
				/* Seach for the set in collection */
				temp_n = binary_search(temp_set, major_collection[size_set-1], 0, major_collection[size_set-1].size-1);
				if(temp_n == -1) {
					printf("E\n");
				}
				printf("0\n");
				break;
			case '*':
				/* Scroll through the entire collection by printing the sets */
				for (int i = 0; i < get_SIZE_MAX_SETS(0,0); ++i)	{
					if(major_collection[i].sets != NULL){
						for (int j = 0; j < major_collection[i].size; ++j) {
							printf("%d ",i+1);
							printSet(major_collection[i].sets[j]);
						}
					}					
				}
				printf("0\n");
				break;
			case '<':
				/* Size of the set */
				x =scanf("%hu", &size_set);	

				/* Read the set in a temporary */
				readSet(&temp_set, size_set);
				/* tests all sets */
				for (int i = 0; i < size_set+1; ++i)
					for (int j = 0; j < major_collection[i].size; ++j)
					{
						if ( superSet(temp_set, major_collection[i].sets[j])
						&& setcmp(temp_set, major_collection[i].sets[j]) != 0)
						{
							printf("%d ",i+1);
							printSet(major_collection[i].sets[j]);
						}
					}
				printf("0\n");
				break;
			case '>':
				/* Size of the set */
				x =scanf("%hu", &size_set);	

				/* Read the set in a temporary */
				readSet(&temp_set, size_set);
				/* tests all sets*/
				for (int i = size_set-1; i < get_SIZE_MAX_SETS(0,0); ++i)
				{
					for (int j = 0; j < major_collection[i].size; ++j)
					{
						if ( superSet(major_collection[i].sets[j], temp_set)
						&& setcmp(temp_set, major_collection[i].sets[j]) != 0)
						{
							printf("%d ",i+1);
							printSet(major_collection[i].sets[j]);
						}

					}
				}
				printf("0\n");
				break;
			case '/':
				/* Size of the set */
				x =scanf("%hu", &size_set);
				int success = 0;	

				/* Read the set in a temporary */
				readSet(&temp_set, size_set);
				/* tests all bigger sets*/
				for (int i = 0; i < get_SIZE_MAX_SETS(0,0); ++i)
				{
					for (int j = 0; j < major_collection[i].size; ++j)
					{
						if ( superSet(major_collection[i].sets[j], temp_set)
						&& setcmp(temp_set, major_collection[i].sets[j]) != 0)
						{
							++success;
							/*remove set*/
							removeSet(&major_collection[i], j);
						}

					}
				}
				if (!success)
					printf("E\n");
				printf("0\n");
		}

		x =scanf("%c", &c_input);
	}
	for (int i = 0; i < get_SIZE_MAX_SETS(0,0); ++i)	{
		if(major_collection[i].sets != NULL){
			for (int j = 0; j < QTT_MAX_SETS; ++j) {
				if(major_collection[i].sets[j] != NULL)
					free(major_collection[i].sets[j]);
			}
			free(major_collection[i].sets);
		}					
	}

	free(major_collection);

	if(temp_set != NULL)
		free(temp_set);

	return 0;
}

/* Return -1 if its not found */
unsigned long binary_search(unsigned long *set_target, COLLECTION collection, long begin, long end) {
	/* If the collection is empty */
	if (begin > end)
		return -1;

	/* Find the central position and compare with the element in it */
	long m = (begin+end)/2;
	int x = setcmp (set_target, collection.sets[m]);
	
	/* Found! */
	if(x == 0){
		return m;
	}
	/* Search for the set in a sub-collection with smaller values */
	else if (x < 0) 
 		return binary_search(set_target, collection, begin, m-1);
	/* Search for the set in a sub-collection with larger values */
	return binary_search(set_target, collection, m+1, end);
}