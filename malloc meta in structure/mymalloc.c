#include "mymalloc.h"

block memory[MEMSZ];

metaData *head = NULL;

void *MyMalloc(int size){
	void * segment = NULL;
	if(size<1){
		return NULL;
	}
	if (!head){
		initMaloc();
	}
	metaData *found = findFreeSegment(size);
	if(found){
		segment = (block*)found + METASZ;
		found->free = 0;
		splitSegment(found,size);
	}

	return segment;
}

void MyFree(void *ptr){
	if(!ptr){
		return;
	}
	metaData *current = getMetaData(ptr);
	current->free = 1;	
	mergeSegment(current);
}

void mergeSegment(metaData * current){
	if(current->prev && current->prev->free==1){
		current->prev->next = current->next;
		if(current->next){
			current->next->prev = current->prev;
		}
		current->prev->size = current->prev->size + current->size + METASZ;
		current = current->prev;
	}
	if(current->next && current->next->free==1){
		mergeSegment(current->next);
	}
}

metaData * getMetaData(void *ptr){
	return (metaData*)((block*)ptr - METASZ);
}

void initMaloc(){
	metaData *new = (metaData *)memory;
	new->size = MEMSZ-METASZ;
	new->prev = NULL;
	new->next = NULL;
	new->free = 1;
	head = new;
}

void splitSegment(metaData *current,int usedSize){
	if(current->size > usedSize+METASZ){
		metaData *new = (metaData*)((block*)current + METASZ + usedSize);
		new->size = current->size - usedSize  -METASZ;
		new->prev = current;
		new->next = current->next;
		current->next = new;
		new->free = 1;
		current->size = usedSize;
	}
}

metaData * findFreeSegment(int size){
	metaData *current = head;
	while(current && !(current->free && current->size >= size)){
		current = current->next;
	}
	return current;
}

void printMemory(){
	int i;
	for(i =0; i<MEMSZ ; i++){
		printf("[%d] %d\t",i, memory[i]);
	}
	printf("\n");
}

void printLinkList(){
	metaData *current = head;
	printf("size\tfree\tdata\n");
	while(current){
		printf("%d\t%d\t",current->size,current->free );
		int i;
		if(!current->free){
			for(i = 0; i<current->size; i++){
				printf("%d ", *((block*)current + METASZ + i));
			}
		}
		printf("\n");
		current=current->next;
	}
}