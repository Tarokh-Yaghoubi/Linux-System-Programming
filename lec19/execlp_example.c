
#include "../headers.h"

int
main(void) {

	int status;
	pid_t cpid = fork();
	if (cpid == -1) {
		perror("fork");
		return EXIT_FAILURE;
	}

	if (cpid == 0) {
		execlp("ls", "myls", "-l", "/home", NULL);
		printf("This line will not be printed\n");
	} else {
		wait(&status);
		printf("Hello, I am the parent\n");
	}

	return EXIT_SUCCESS;
}
