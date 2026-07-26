

#include "../headers.h"
#include <signal.h>

void handler(int signo) {
	printf("caught signal = %d\n", signo);
	exit(EXIT_SUCCESS);
}

int
main(int argc, char * argv[]) {
	// take a file from params, open and write something with the child process
	
	if (argc == 1) {
		fprintf(stderr, "usage: ./%s <filename>", argv[0]);
		return EXIT_FAILURE;
	}

	pid_t pid = fork();
	if (pid == -1) {
		perror("fork");
		return EXIT_FAILURE;
	} else if (pid == 0) {
		
		char * command[] = {"vim", argv[1], NULL};

		int ret = execvp("vim", &command[0]);
		if (ret == -1) {
			perror("execvp");
			return EXIT_FAILURE;
		}

	} else {
		struct sigaction act = {0};

		act.sa_handler = handler;
		sigemptyset(&act.sa_mask);
		act.sa_flags = 0;

		sigaction(SIGCHLD, &act, NULL);

		pause();
		return EXIT_SUCCESS;	
	
	}
}
