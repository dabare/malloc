#include "mymalloc.h"

block memory[MEMSZ];

block *head = NULL;

void *MyMalloc(int size){
	meta found = NULL;
	if(size<1){
		return NULL;
	}
	if (!head){
		initMaloc();
	}
	found = findFreeSegment(size);
	if(found){
		*getFree(found) = 0;
		splitSegment(found,size);
	}
	return getSegment(found);
}

void initMaloc(){
	*getFree(memory) = 1;
	*getPrev(memory) = 0;
	*getNext(memory) = 0;
	*getSize(memory) = MEMSZ - METASZ;
	head = memory;
}

meta findFreeSegment(int size){
	meta current = head;
	while(current && !(*getFree(current) && *getSize(current) >= size)){
		current = *getNext(current);
	}
	return current;
}

void splitSegment(meta current,int usedSize){
	if(*getSize(current) > usedSize + METASZ){
		meta new = current + METASZ + usedSize;
		*getSize(new) = *getSize(current) - usedSize - METASZ;
		*getFree(new) = 1;
		*getPrev(new) = current;
		*getNext(new) = *getNext(current);
		*getNext(current) = new;
		*getSize(current) = usedSize;
		if(*getNext(new)){
			*getPrev(*getNext(new)) = new;
		}
	}
}


void MyFree(void *ptr){
	if(ptr){
		meta current = getMeta(ptr);
		*getFree(current) = 1;
		mergeSegment(current);
	}
}

void mergeSegment(meta current){
	if(*getPrev(current) &&  *getFree(*getPrev(current))==1){
		*getNext(*getPrev(current)) = *getNext(current);
		if(*getNext(current)){
			*getPrev(*getNext(current)) = *getPrev(current);
		}
		*getSize(*getPrev(current)) += *getSize(current) + METASZ; 
		current = *getPrev(current);
	}
	if(*getNext(current) && *getFree(*getNext(current))==1){
		mergeSegment(*getNext(current));
	}
}

size getSize(meta m){
	return (size)(m + FREESZ + PREVSZ + NEXTSZ);
}

free getFree(meta m){
	return m;
}

prev getPrev(meta m){
	return (prev)(m + FREESZ);
}

next getNext(meta m){
	return  (prev)(m + FREESZ + PREVSZ);
}

void* getSegment(meta m){
	return (void*)(m + METASZ);
}

meta getMeta(void *ptr){
	return (meta)(ptr) - METASZ;
}


void printMemory(){
	int i;
	for(i =0; i<MEMSZ ; i++){
		printf("[%d] %d\t",i, memory[i]);
	}
	printf("\n");
}

void printLinkList(){
	meta current = head;
	printf("size\tfree\tdata\n");
	while(current){
		printf("%d\t%d\t",*getSize(current),*getFree(current));
		int i;
		for(i = 0; i<*getSize(current); i++){
			printf("%d-", *(current + METASZ + i));
		}
		printf("\n");
		current = *getNext(current);
	}		
}