
#define _GNU_SOURCE

#include "../../headers.h"

int
main() {
	int i, cpid, ctr = 0;
	cpid = fork();

	if (cpid == 0) {
		ctr = 100;
		for (i = 0; i < 3; i++)
			printf("Child counter is => %d\n", ctr++);
	} else {
		for (i = 0; i < 3; i++)
			printf("Parent counter is => %d\n", ctr++);
	}

	return EXIT_SUCCESS;
}

