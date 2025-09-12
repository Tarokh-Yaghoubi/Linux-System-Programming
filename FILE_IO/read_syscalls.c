

// both creat() and open() return a file descriptor on success
// and they both return -1 on failure, and set errno to an appropriate error value


// READING DATA FROM FILES
// POSIX.1 introduced the most basic way to read data from files using the read() syscall.

// ssize_t read (int fd, void* buf, size_t len);
// each call reads 'len' bytes and writes to memory which 'buf' is pointing to from the current offset of the file referenced by 'fd'.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

	unsigned long word;
	ssize_t 	nr;

	char readBuffer[100] = {0};

	int fd = creat("file.txt", 0644);
	
	char buf[] = "last is last\n";

	write(fd, buf, sizeof(buf));

	dprintf(fd, "first is first\n");

	nr = read(fd, &readBuffer, sizeof(readBuffer));
	if (nr == -1) {
		perror("read");
		return EXIT_FAILURE;
	}
	printf("READ [%ld] LINES ->\n", nr);

	printf("BUFFER after read() -> [%s]\n", readBuffer);



	close(fd);

	return EXIT_SUCCESS;

}

