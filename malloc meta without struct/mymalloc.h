#include <stdio.h>

#define SIZESZ sizeof(int) //no. bytes to store size 
#define FREESZ sizeof(char) //free`
#define PREVSZ sizeof(block*) //previous node
#define NEXTSZ sizeof(block*) //next node

#define MEMSZ 25000
#define METASZ  (SIZESZ + FREESZ + PREVSZ + NEXTSZ)
//[free][prev][next][size]
//1+8+8+4=21 bytes for metadata
//used a double linked list, (merging free segments is easy)

typedef unsigned char block; //memory block is unsigned byte
typedef unsigned char *  free;	//pointer to a byte which tells the memory segment free or not
typedef unsigned char *  meta;	//pointer to the meta data a segment
typedef unsigned char **  prev;	//pointer to the previous meta data(pointer toa pointer)
typedef unsigned char **  next; //pointer to the next meta data
typedef int * size;


size getSize(meta m); //returns the pointer to the size of the corresponding meta data
free getFree(meta m); //returns the pointer to the free of corresponding meta data
prev getPrev(meta m); //returns the pointer to the prev. meta data
next getNext(meta m); //returns the pointer to the next meta data
void* getSegment(meta m); //when meta data is given returns corresponding the pointer to the memory 
meta getMeta(void *ptr); //when memory is given returns the pointer to the meta data


void *MyMalloc(int size); //My malloc function 
void initMaloc(); //initialize the link list
meta findFreeSegment(int size); //finds a free memory segment which matches the size
void splitSegment(meta current,int usedSize); //splits a free memory segment to two,(free & not free)

void MyFree(void *ptr); //My free function
void mergeSegment(meta current); //merges two nearby free memory segments


//for debugging purpose
void printMemory(); //prints the whole memory
void printLinkList(); //prints the link list