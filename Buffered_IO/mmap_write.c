
#include "../headers.h"
#include <sys/mman.h>
#include <fcntl.h>

int
main(void) {
	int fd = open("test.dat", O_RDWR);
	if (fd < 0) {
		perror("open");
		return -1;
	}

	char buffer[100];
	ssize_t read_size = read(fd, buffer, sizeof(buffer));
	printf("%d-%d\n", read_size, strlen(buffer));

	// mmap way: 
	char  * map = mmap(NULL, 100, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	map[0] = 'G';	// this directly changes the files first byte. no write() needed.
	printf("data => [%s]\n", map);	
	return EXIT_SUCCESS;
}

