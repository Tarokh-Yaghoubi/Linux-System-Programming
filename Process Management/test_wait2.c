

#include "../headers.h"

int
main(int argc, char * argv[]) {
	int status;
	pid_t pid;

	if (!fork())
		return EXIT_FAILURE;

	pid = wait(&status);
	if (pid == -1)
		perror("wait");

	printf("pid=%d\n", pid);

	// these functions are for realising how the child process is died so we can handle it in different ways
	// for this programme because we had a normal termination, we expect to see the first if condition working.
	if (WIFEXITED(status))
		printf("Normal termination with exit status = %d\n", WEXITSTATUS(status));

	if (WIFSIGNALED(status))
		printf("Killed By Signal=%d%s\n", WTERMSIG(status), WCOREDUMP(status) ? "(dumped core)" : "");

	if (WIFSTOPPED(status))
		printf("Stopped by signal=%d\n", WSTOPSIG(status));

	if (WIFCONTINUED(status))
		printf("Continued\n");


	return EXIT_SUCCESS;
}
