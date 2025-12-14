

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void myexit1() {
	printf("First Exit Handler\n");
}

void myexit2() {
	printf("Second Exit Handler\n");
}

int main () {
	atexit(myexit1);
	atexit(myexit1);
	atexit(myexit2);
	printf("Main is Done\n");
	exit(0);
}
