#include "hoc.h"
#ifdef STDC_HEADERS
#include <stdlib.h>
#include <string.h>
#else
	char *malloc(),*memset();
#endif


#define MEMSIZE 128
#define OVRHD (sizeof(int*)/sizeof(int)	/* warning: must be and integer */
typedef struct {
#ifdef DEBUGING
	int *i;/*overhead*/
#endif
	union {
		Local l;
	} u;
} largest;
static int *memlist[(sizeof(largest)-1)/sizeof(int)+2];

int *
getmem(i)
{
/*
* Get i words of cleared memory.
*
* On the first call, MEMSIZE blocks of i words each are allocated, 
* and are linked into a free list, whose address is in memlist[i].
* The link pointer is normally contained in the requested block
* (assuming that an int* can be stored at an int boundary)
* but, as a debugging option, it is prepended to that block,
* and is cleared on allocation to enable error checking.
*/
	int *p,n;
#ifdef DEBUGING
	i += OVRHD;
#endif
	if (p=memlist[i])
		memlist[i]= *(int**)p;
	else {
		n=MEMSIZE*i;
		if(!(p=(int*)malloc(n*sizeof(int))))
			execerror("out of memory",(char *)0);
		memlist[i] = p + i;
		*(int **)(p + n - i) = 0;
		while ((n -= i) > i)
			*(int **)(p + n - i) = p + n;
	}
#ifdef DEBUGING
	*(int**)p = 0;
	p += OVRHD;
	i -= OVRHD;
#endif
	return (int*)memset(p,'\0',i*sizeof(int));
}

void
freemem (p, i)
int *p;
/*
* Free the i words of memory located at p.
*/
{
#ifdef DEBUGING
	p -= OVRHD;
	if (*(int**)p)
		execerror("freemem: tried to free twice",(char *)0);
	i += OVRHD;
#endif
	*(int**)p = memlist[i];
	memlist[i] = p;
}
