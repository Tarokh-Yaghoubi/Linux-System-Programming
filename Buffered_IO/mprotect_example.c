

#define __GNU_SOURCE 

#include "../headers.h"

#include <sys/mman.h>
#include <sys/user.h>

#include <fcntl.h>

int
main(void) {
	int fd = open("test.dat", O_RDWR);
	if (fd < 0) {
		perror("open");
		return EXIT_FAILURE;
	}

	char buffer[100] = {0};
	size_t read_size = read(fd, buffer, sizeof(buffer));
	printf("read data ====== => [%s]\n", buffer);

	char * p = mmap(NULL, 100, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	// If you already know, how you are going to read 
	// the data from the file, you can just give the 
	// kernel an specific advise, for the sake of 
	// efficiency.

	madvise(p, 100, MADV_SEQUENTIAL);
	// madvise(p, 100, MADV_RANDOM);

	p[0] = '$';

	printf("MAP DATA ====== => [%s]\n", p);

	// here, we will use mprotect to change mmap region permissions
	int ret = mprotect(p, PAGE_SIZE, PROT_READ | PROT_EXEC);
	if (ret < 0) {
		perror("mprotect");
		return EXIT_FAILURE;
	}

	p[1] = '&';	// SIGSEGV - page is no longer writeable

	return EXIT_SUCCESS;
}
