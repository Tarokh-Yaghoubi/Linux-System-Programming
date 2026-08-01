

#include "../headers.h"

int mysys(char *);

int
main() {
	printf("Running ls command using mysys()\n\n");
	mysys("ls -l /home");
	printf("\nDone.. \n");
	exit(EXIT_SUCCESS);

}

int 
mysys( char * cmd) {
	pid_t cpid = fork();
	switch (cpid) {
		case -1:
			perror("fork");
			return EXIT_FAILURE;
		case 0:
			execlp("/bin/bash", "mybash", "-c", cmd, '\0');
			perror("execlp");
			return EXIT_FAILURE;
		default:
			waitpid(cpid, NULL, 0);
			return EXIT_SUCCESS;
	
	}
}

