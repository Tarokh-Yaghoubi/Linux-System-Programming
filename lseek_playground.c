


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
// SEEK_CUR, SEEK_END, SEEK_SET

int
main(void) {

	off_t ret;
	char buf[] = "a";
	int fd = open("test", O_CREAT | O_RDWR, 0644);
	if (fd < 0) {
		perror("open");
		return EXIT_FAILURE;
	}

	ret = lseek(fd, 10, SEEK_SET);
	if (ret == (off_t) -1) {
		perror("lseek");
		return EXIT_FAILURE;
	}

	ret = lseek(fd, 0, SEEK_CUR);
	if (ret == (off_t) -1) {
		perror("lseek");
		return EXIT_FAILURE;
	}

	printf("LSEEK RETURN ---- -> [%ld]\n", (off_t)ret);
	
	for (int i = 0; i < 15; i+=2)
		pwrite(fd, buf, 1, i);
}

