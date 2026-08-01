

// simple system syscall programme. 

#include "../headers.h"

int
main(int argc, char * argv[]) {
	system(argv[1]);
	printf("\nDone... Bye\n");
	exit(EXIT_SUCCESS);
}
