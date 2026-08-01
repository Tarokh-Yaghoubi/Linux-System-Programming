

#include "../headers.h"

int execute(char **);
int main() {
	char * arglist[10] = {0};
	arglist[0] = "/bin/ls";
	arglist[1] = "-l";
	arglist[2] = "/home";
	arglist[3] = NULL;
	int rv = execute(&arglist[0]);
	return rv;
}

int 
execute(char * arglist[]) {
	int status;
	pid_t cpid = fork();
	switch(cpid) {
		case -1:
			perror("fork failed");
			exit(EXIT_FAILURE);
		case 0:
			execvp(arglist[0], arglist);
			perror("execvp failed");
			exit(EXIT_FAILURE);
		default:
			waitpid(cpid, &status, 0x00);
			status = status >> 8;
			printf("child exited with status = %d\n", status);
			return status;
	}
}
