
#include "../headers.h"

int
main() {

	pid_t cpid = fork();
	if (cpid == -1) {
		perror("fork");
		return EXIT_FAILURE;
	}

	if (cpid == 0) {
		printf("running child, pid=%ld ppid=%ld\n", (long)getpid(), (long)getppid());
		while(1);
	} else {

		printf("Terminating the parent,  pid=%ld ppid=%ld\n", (long)getpid(), (long)getppid());
		exit(EXIT_SUCCESS);
	}
	return EXIT_SUCCESS;
}
