
#define _GNU_SOURCE

#include "../../headers.h"

int
main(int argc, char * argv[]) {

	// describe what happens if fork() is called multiple times
	
	if (argc != 2) {
		printf("Must enter one argument (an integer)\n");
		return EXIT_FAILURE;
	}

	int n = atoi(argv[1]);
	int i;

	for (i = 1; i <= n; i++)
		fork();

	printf("PUCIT\n");
	return EXIT_SUCCESS;

}
