/*
 *	A programme that shows how mmap works for reading a files data directly from kernel.
 *	Also, it shows how munmap works in the end.
 *
*/


#include "../headers.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

int
main(int argc, char * argv[]) {

	struct stat sb;
	off_t len = 0;
	char * p;
	int fd;

	if (argc < 2) {
		fprintf(stderr, "usage : %s <file>\n", argv[0]);
		return EXIT_FAILURE;
	}

	fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		perror("open");
		return EXIT_FAILURE;
	}

	if (fstat (fd, &sb) == -1) {
		perror("fstat");
		return EXIT_FAILURE;
	}
	
	if ( !S_ISREG(sb.st_mode) ) {
		fprintf(stderr, "%s is not a regular file\n", argv[1]);
		return EXIT_FAILURE;
	}

	p = mmap(0, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (p == MAP_FAILED) {
		perror("mmap");
		return EXIT_FAILURE;
	}

	if (close(fd) == -1) {
		perror("close");
		return EXIT_FAILURE;
	}

	for (len = 0; len < sb.st_size; len++)
		putchar (p[len]);

	// And now we unmap:
	if (munmap(p, sb.st_size) == -1) {
		perror("munmap");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
