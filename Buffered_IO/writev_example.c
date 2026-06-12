


#include "../headers.h"
#include <sys/types.h>
#include <sys/stat.h>

#include <sys/uio.h>

#define MAX_BUFFER 3


int main() {
	
	char first[] = {"This is the first sentence\n"};
	char second[] = {"This is the second sentence\n"};
	char third[] = {"This is the third sentence\n"};

 	FILE * stream = fopen("test.dat", "a+");
	int fd = fileno(stream);
	printf("fd for stream => %d\n", fd);

	struct iovec iov[MAX_BUFFER] = {
		{first, sizeof(first) },
		{second, sizeof(second) },
		{third, sizeof(third) },
	};

	ssize_t written = writev(fd, iov, MAX_BUFFER);
	if (written > 0)
		printf("written data => %d\n", written);
	else {
		perror("writev");
		return EXIT_FAILURE;
	}


	return EXIT_SUCCESS;
}
