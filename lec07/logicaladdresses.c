

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


extern int etext, edata, end;

int I = 54;	// Initialized global variable
int J;	// uninitialized global variable

int main(int argc, char* argv[]) {

	int i = 10; 	// stack variable
	int *iPtr = NULL;

	printf("Page size: %d\n\n", getpagesize());

	printf("main = %p\n", main);
	printf("&etext = %p\n\n", &etext);
	printf("&I(initialized var)	= %p\n", &I);
	printf("&edata => %p\n", &edata);
	printf("&J(uninitialized var)	= %p\n", &J);

	printf("&end = %p\n\n", &end);
	
	iPtr = (int *) malloc (sizeof(int));
	printf("iPtr (addr of heap)	= %p\n\n", iPtr);
	
	printf("&argc = %p\n", &argc);
	printf("&i = %p\n", &i);
	printf("&iPtr = %p\n", &iPtr);


	return 0;

}
