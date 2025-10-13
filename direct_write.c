
#define _GNU_SOURCE

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#define ALIGNMENT 4096
#define FILE_PATH "testfile.bin"

int main() {
	
	int fd;
	ssize_t ret;
	void* buf;


	if (posix_memalign(&buf, ALIGNMENT, ALIGNMENT) != 0) {
		perror("posix_memalign");
		return EXIT_FAILURE;
	}

	fd = open(FILE_PATH, O_WRONLY | O_CREAT | O_DIRECT, 0644);
    	if (fd == -1) {
       		perror("open");
        	free(buf);
        	return 1;
    	}

    	ret = write(fd, buf, ALIGNMENT);
    	if (ret == -1) {
        	perror("write");
    	} else {
        	printf("Wrote %zd bytes directly to disk\n", ret);
    	}

    	close(fd);
    	free(buf);
    	return 0;
}

