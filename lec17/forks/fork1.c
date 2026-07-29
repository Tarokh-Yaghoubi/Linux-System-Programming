

#include "../headers.h"

int
main() {

	int cpid = fork();
	if (cpid == 0)
		printf("I am the child\n");
	else
		printf("I am the parent\n");

	return EXIT_SUCCESS;
}
