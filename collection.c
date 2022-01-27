#include "collection.h"
#include <stdio.h>
#include <stdlib.h>

/* Returns the maximum size of the sets */
/* It's not pretty, but it's useful */
unsigned long get_SIZE_MAX_SETS(bool modify, unsigned long value) {
	static unsigned long SIZE_MAX_SETS;
	
	if(modify)
		SIZE_MAX_SETS = value;

	return SIZE_MAX_SETS;
}

/* return: 0 if a=b, 1 if a>b and -1 if a<b */
int setcmp (unsigned long *a, unsigned long *b) {
	int i;
	/* Let it do all the work */
	for (i = 0; i < REPRESENTATION_SIZE && a[i] == b[i]; ++i);
	if(i > 0 && a[i] == b[i])
		--i;
	
	unsigned long c1,c2;
	/*all that matter is the first element that's different, the smaller one "wins"*/
	/*using shift from 63 down to 0 we deslocate all the bits one by one and test them*/
	for (int j = 63; j >= 0; --j)
	{
		c1 = a[i] << j;
		c2 = b[i] << j;
		if (c1<c2)
			return 1;
		if (c2 <c1)
			return -1;
	}

	return 0;
}

/*Returns 1 if (a contains b), else returns 0 */
int superSet (unsigned long *a, unsigned long *b)
{
	int i;
	/*compares a and b until it reaches the size of the smaller one (b) */
	for (i = 0; i < REPRESENTATION_SIZE ; ++i)
	{
		/*in our representtion, using the & operator we can veify if one set is in another*/
		/*e.g.: set a is (binary) 01110101 and set b is 01000101, a & b results in b, so b is in a*/
		if ((a[i] & b[i])!= b[i])
			return 0;

	}	
	return 1;
}





bool readSet(unsigned long **set, unsigned short size_set) {
	long int x = 0;
	x+=x;
	/* Allocate the set if it isnt already allocated */
	if(*set == NULL){
		*set = (unsigned long *) calloc (REPRESENTATION_SIZE, sizeof(long));
		
		if(*set == NULL)
			return false;
	}
	else {
		/* If its already allocated, clean it */
		for (int i = 0; i < REPRESENTATION_SIZE; ++i)
			(*set)[i] = (long) 0; 
	}

	/* index_element and moves are bit addresses */
	/* index_element is the block of bits it goes */
	/* moves is the amount of bit shift */
	unsigned short element, moves, index_element;
	for (int i = 0; i < size_set; ++i) {
		x = scanf("%hu", &element);

		index_element = element >> 6;
		moves = element & 63;

		/* Turn on the corresponding bit */
		/* Casting is required because literal integers are 32 bits by default */
		(*set)[index_element] |= (long) 1 << moves;
	}

	return true;
}

bool printSet(unsigned long *set) {
	/* Look all the bits of the set and print the number corresponding to those that are turned on */
	unsigned short moves, index_element;
	int printed = 0;
	for (int i = 1; i <= get_SIZE_MAX_SETS(0,0); ++i) {
		index_element = i >> 6 ;
		moves = i % 64;
		if(set[index_element] & ((long) 1 << moves))
		{
			if (printed == 0)
			{
				printf("%d", i);
				printed++;
			}
			else 
			{
				printf(" %d", i);
				printed++;
			}
		}
	}
	printf("\n");

	return true;
}

bool insertSet(COLLECTION *collection, unsigned long *set, unsigned short set_size) {
	/* Allocate the set if it isnt already allocated */
	if(collection->sets[collection->size] == NULL){
		collection->sets[collection->size] = (unsigned long *) malloc (REPRESENTATION_SIZE*sizeof(long));

		if(collection->sets[collection->size] == NULL)
			return false;
	}

	/* Move the sets until you find the correct position of the new set */
	int pos;
	for (pos = collection->size-1; pos >= 0 && setcmp(collection->sets[pos], set) > 0; --pos) {
		for (int i = 0; i < REPRESENTATION_SIZE; ++i) {
			collection->sets[pos+1][i] = collection->sets[pos][i];
		}
	}
	
	/* Now place it in the correct position */
	++pos;
	for (int i = 0; i < REPRESENTATION_SIZE; ++i) {
		collection->sets[pos][i] = set[i];
	}

	collection->size++;

	return true;
}

bool removeSet(COLLECTION *collection, unsigned long position) {
	/* Move the sets until you find the correct position of the new set */
	for (int pos = position; pos < collection->size-1; ++pos) {
		for (int i = 0; i < REPRESENTATION_SIZE; ++i) {
			collection->sets[pos][i] = collection->sets[pos+1][i];
		}
	}

	collection->size--;

	return true;
}