

// both creat() and open() return a file descriptor on success
// and they both return -1 on failure, and set errno to an appropriate error value


// READING DATA FROM FILES
// POSIX.1 introduced the most basic way to read data from files using the read() syscall.

// ssize_t read (int fd, void* buf, size_t len);
// each call reads 'len' bytes and writes to memory which 'buf' is pointing to from the current offset of the file referenced by 'fd'.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// Using fcntl for debug 

#include <fcntl.h>

// include errno.h to play with errno and errors 
#include <errno.h>

int main() {

	unsigned long word;
	ssize_t 	nr;

	char readBuffer[100] = {0};

	char testBuffer[10] = { 0 };

	int fd = creat("file.txt", 0644);
	
	char buf[] = "last is last\n";

	write(fd, buf, sizeof(buf));
	close(fd);	// closing file / opening it with open() because of permissions
	
	fd = open("file_doesnt_exist", O_RDWR | O_NONBLOCK, 0644);
	int numRead = read(fd, &testBuffer, sizeof(testBuffer));
	if (numRead <= 0) {
		// EAGAIN occures when using sockets, pipes, or devices that might have data 
		// later.
		if (errno == EBADF) {
			printf("EBADF detected ------>> \n");
		} else if (errno == EAGAIN) { 
			printf("EAGAIN is here -> ");
		} else {
			perror("read");
		}
		printf("NUM-READ result printed ------>>\n\n");
	}

	close(fd);

	fd = open("file.txt", O_RDWR, 0644);

	dprintf(fd, "first is first\n");

	// I call this because the offset is no more at the beginning of the file
	// because of dprintf()...
	
	lseek(fd, 0, SEEK_SET);

	nr = read(fd, &readBuffer, sizeof(readBuffer));
	if (nr == -1) {
		perror("read");

		int flag = fcntl(fd, F_GETFL);
		if (flag == -1) {
			perror("fcntl F_GETFL");
		} else {
			printf("FILE access mode: ");
			// Here we get O_WRONLY cause we are opening the file using creat()
			switch(flag & O_ACCMODE) {
				case O_RDONLY: printf("O_RDONLY\n"); break;
				case O_WRONLY: printf("O_WRONLY\n"); break;
				case O_RDWR:   printf("O_RDWR\n"); break;
			}
			
		}

		return EXIT_FAILURE;
	}

	printf("READ [%ld] LINES ->\n", nr);

	printf("BUFFER after read() -> [%s]\n", readBuffer);



	close(fd);

	return EXIT_SUCCESS;

}

