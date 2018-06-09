#include "mymalloc.h"

int main(){
char *a = (char*)MyMalloc(2);
	char *b = (char*)MyMalloc(50);
	char *c = (char*)MyMalloc(10);
	char *d = (char*)MyMalloc(5);

	MyFree(b);
	MyFree(c);
	MyFree(a);

	char *e = (char*)MyMalloc(50);
	char *f = (char*)MyMalloc(33);

	MyFree(f);
	MyFree(d);
	printLinkList();
	return 0;
}
