

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void exit_handler() {
	printf("Exit Handler\n");
}


int main () {

	atexit(exit_handler);
	printf("Main Is Done\n");
//	return 0;	// or exit(0);
	_exit(0);
}

