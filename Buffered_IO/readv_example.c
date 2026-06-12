

#include "../headers.h"
#include <sys/uio.h>
#include <fcntl.h>

#define MAX_BUFFER 3

int 
main() {

	char first[35], second[29], third[27];

	struct iovec iov[MAX_BUFFER];
	ssize_t nr = 0;
	int fd, i;

	fd = open("test.dat", O_RDONLY);
	if (fd == -1) {
		perror("open");
		return EXIT_FAILURE;
	}

	iov[0].iov_base = first;
	iov[0].iov_len = sizeof(first);
	iov[1].iov_base = second;
	iov[1].iov_len = sizeof(second);
	iov[2].iov_base = third;
	iov[2].iov_len = sizeof(third);

	nr = readv(fd, iov, MAX_BUFFER);
	if (nr < 0) {
		perror("readv");
		return EXIT_FAILURE;
	}

	for (int i = 0; i < MAX_BUFFER; i++) {
		printf("%d-%s\n", i, (char*)iov[i].iov_base);
	}

	int err = close(fd);
	if (err < 0) {
		perror("close");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
