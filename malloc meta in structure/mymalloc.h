#include <stdio.h>

#define MEMSZ 25000
#define METASZ sizeof(metaData)

typedef unsigned char block;
typedef struct meta metaData;

struct meta{
	int size; 
	metaData *prev;
	metaData *next; 
	char free; 
};

void *MyMalloc(int size);
metaData * findFreeSegment(int size);
void initMaloc();
void splitSegment(metaData *current,int usedSize);

void MyFree(void *ptr);
metaData * getMetaData(void *ptr);
void mergeSegment(metaData * current);


//for debugging
void printMemory();
void printLinkList();
