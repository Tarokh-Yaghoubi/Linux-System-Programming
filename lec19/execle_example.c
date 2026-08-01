
#include "../headers.h"

extern char ** environ;

int
main(void) {
	int status;
	pid_t cpid = fork();
	if (cpid == 0) {
		execle("/usr/bin/gnome-calculator ", "mycalc", NULL, environ);
		perror("execle failed");
	} else {
		wait(&status);
		printf("Hello I am the parent\n");	
	}

	return EXIT_SUCCESS;
}
