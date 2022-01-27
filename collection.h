/*== Stephanie Briere Americo ==*/
/*== Talita Halboth ==*/

#ifndef __COLLECTION_H__
#define __COLLECTION_H__

#include <stdbool.h>
#include <math.h>

/* Maximum sets in collection */
#define QTT_MAX_SETS 9000
/* Basically, the minimum vector size that has enough bits to store sets of X size */
#define REPRESENTATION_SIZE ceil(get_SIZE_MAX_SETS(0,0) / (sizeof(long)*8.0))

typedef struct COLLECTION {
	unsigned short size; 
	unsigned long **sets; 

} COLLECTION;

unsigned long get_SIZE_MAX_SETS(bool modify, unsigned long value);
int setcmp (unsigned long *a, unsigned long *b);
int superSet (unsigned long *a, unsigned long *b);
bool readSet(unsigned long **set, unsigned short size_set);
bool printSet(unsigned long *set);
bool insertSet(COLLECTION *collection, unsigned long *set, unsigned short set_size);
bool removeSet(COLLECTION *collection, unsigned long position);

#endif