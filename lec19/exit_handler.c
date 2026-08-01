

#include "../headers.h"
#include <wait.h>

void
exit_handler() {
	printf("Exit Handler\n");
}

int
main(void) {
	atexit(exit_handler);

	pid_t cpid = fork();
	switch (cpid) {
		case -1:
			perror("fork");
			exit(EXIT_FAILURE);
		case 0:
			printf("This is the child Process\n");
			exit(EXIT_SUCCESS);
		default:
			printf("This is the parent Process\n");
			exit(EXIT_SUCCESS);
	}
}

