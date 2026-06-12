
#include "../headers.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>

#define MAX_BUFFER 3

int main() {

	struct iovec iov[MAX_BUFFER];
	ssize_t nr;
	int fd, i;

	char *buf[] = {
		"This is the first sentence in mem\n",
		"This is the second sentence\n",
		"This is the last sentence\n"
	};

	fd = open("test.dat", O_RDWR | O_CREAT, 0644);
	if (fd == -1) {
		perror("open");
		return EXIT_FAILURE;
	}

	for (int i = 0; i < MAX_BUFFER; i++) {
		iov[i].iov_base = buf[i];
		iov[i].iov_len = strlen(buf[i]);
	}

	nr = writev(fd, iov, MAX_BUFFER);
	if (nr < 0) {
		perror("writev");
		return EXIT_FAILURE;
	}

	close(fd);

	return EXIT_SUCCESS;

}

