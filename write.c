

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {

	// SSIZE write(int fd, const void *buf, size_t count);
	// write is defined in POSIX.1
	// writes up to count bytes starting at &buf[0] to 'fd'
	// write returns the number of bytes written , or 0 if no bytes are written
	const char * buf = "My name was Jacob\n";
	ssize_t nr;

	// STDOUT_FILENO to write to stdout for test, it could be a file descriptor.
	// If count is larger that SSIZE_MAX, the result of the call to write() is undefined.
	
	nr = write(STDOUT_FILENO, buf, strlen(buf));
	if (nr == -1)
		perror("write");

	return EXIT_SUCCESS;
}

