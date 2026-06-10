
#include "headers.h"

int main() {

	int pipefds[2];
	int pipefds_sec[2];

	pipe(pipefds);
	pipe(pipefds_sec);

	struct pollfd fds[2];

	if (fork() == 0) {
		char buffer[] = {"Write data to the pipe\n"};
		sleep(1);
		ssize_t ret = write(pipefds[1], buffer, strlen(buffer));
		write(pipefds_sec[1], "Write data to the pipe2\n", strlen(buffer) + 1);
		if (ret == strlen(buffer))
			printf("wrote full data to pipe => %d|%d\n", ret, strlen(buffer));
		else
			printf("did not write full data to pipe => %d|%d\n", ret, strlen(buffer));
		
	}

	fds[0].fd = pipefds[0];
	fds[0].events = POLLIN;

	fds[1].fd = pipefds_sec[0];
	fds[1].events = POLLIN;

	int ret = poll(fds, 2, 3000);
	if (ret == -1) {
		perror("poll");
		return EXIT_FAILURE;
	}

	sleep(2);
	if (fds[0].revents & POLLIN) {
		char buffer[100] = {0};
		ssize_t rt = read(pipefds[0], buffer, sizeof(buffer) - 1);
		buffer[rt] = '\0';
		printf("read data from pipe => [%s]\n", buffer);
	}
	
	if (fds[1].revents & POLLIN) {
		char buffer[100] = {0};
		ssize_t rt = read(pipefds_sec[0], buffer, sizeof(buffer) - 1);
		buffer[rt] = '\0';
		printf("read data from second pipe => [%s]\n", buffer);
		return EXIT_SUCCESS;
	}

	return EXIT_SUCCESS;

}
