
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>

int main() {

	sigset_t mask;
	fd_set readfds;
	int ret;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);

	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);

	ret = pselect(STDIN_FILENO + 1, &readfds, NULL, NULL, NULL, &mask);

	if (ret == -1 && errno == EINTR) {
		printf("Got a signal! handle it! ... \n");
		exit(EXIT_FAILURE);
	} else if (ret > 0) {
		printf("Got I/O! Process Data... \n");
		if (FD_ISSET(STDIN_FILENO, &readfds)) {
			char buf[100 + 1];
			int len;

			len = read(STDIN_FILENO, buf, 100);
			if (len == -1) {
				perror("read");
				return 1;
			}

			if (len) {
				buf[len] = '\0';
				printf("read: %s\n", buf);
			}
		}

		return EXIT_SUCCESS;
	}
	fprintf(stderr, "you must not see this\n");
	return 0;
}
