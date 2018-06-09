#include "mymalloc.h"

int main(){
	char *a = (char*)MyMalloc(2);
	char *b = (char*)MyMalloc(50);
	char *c = (char*)MyMalloc(10);
	char *d = (char*)MyMalloc(2);
	
	MyFree(c);
	MyFree(a);
	MyFree(b);
	MyFree(d);
	printLinkList();

	return 0;
}
