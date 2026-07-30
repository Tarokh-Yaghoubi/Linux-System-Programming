
#include "../headers.h"

int
main() {
	pid_t cpid = fork();
	if (cpid == 0) {
		printf("Terminating child with pid=%ld\n", (long)getpid());
		exit(EXIT_SUCCESS);
	} else {
		printf("Running parent=%ld", (long)getpid());
		while(1);
	}

	return EXIT_SUCCESS;
}
