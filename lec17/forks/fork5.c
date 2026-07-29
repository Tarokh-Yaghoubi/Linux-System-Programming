

#define _GNU_SOURCE 

#include "../../headers.h"
#include <fcntl.h>

int
main(void) {
	char first[] = {"First buffer is written by parent process\n"};
	char second[] = {"Second buffer is written by the parent process as well\n"};
	char third[] = {"Last one is from child\n"};

	int fd = open("f1.dat", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1) {
		perror("open");
		return EXIT_FAILURE;
	}
	
	write(fd, first, strlen(first));
	int cpid = fork();
	if (cpid != 0) {
		write(fd, second, strlen(second));
	} else {
		write(fd, third, strlen(third));
	}

	close(fd);
	return EXIT_SUCCESS;
	
}
