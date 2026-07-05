
#include "../headers.h"
#include <fcntl.h>

int
main(int argc, char * argv[]) {

	struct stat buffer = {0};

	if (argc < 2) {
		fprintf(stderr, "The programme does not work like this! \n");
		return EXIT_FAILURE;
	}

	pid_t pid = fork();
	
	if (pid == -1) {
		perror("fork");
		return EXIT_FAILURE;
	} else if (pid == 0) {
		// child process is running here.
		char * argv_exec[] = {"vim", argv[1], NULL };
		int iRet = execvp("vim", &argv_exec[0]);
		if (iRet == -1) {
			perror("execvp");
			return EXIT_FAILURE;
		}
	} else {
		// parent is running here

		waitpid(pid, NULL, 0);
		printf("child is done, back to parent\n");
		int fd = open(argv[1], O_RDONLY);
		if (fd < 0) {
			perror("open");
			return EXIT_FAILURE;
		}
		fstat(fd, &buffer);
		printf("filesize is => [%d]\n", (off_t)buffer.st_size);
		close(fd);

		return EXIT_SUCCESS;
	}
	return EXIT_SUCCESS;
}
