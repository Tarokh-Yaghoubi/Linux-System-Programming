
#include "../headers.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

ino_t get_inode(int fd) {
	struct stat buf;
	int ret = -1;

	ret = fstat(fd, &buf);
	if (ret < 0) {
		perror("fstat");
		return EXIT_FAILURE;
	}

	return buf.st_ino;

}

int
main(int argc, char * argv[]) {

	if (argc < 2) {
		printf("app => [%s]\n", argv[0]);
		return EXIT_FAILURE;
	}



	int fd = open(argv[1], O_RDWR);
	if (fd < 0) {
		perror("open");
		return EXIT_FAILURE;
	}

	ino_t inode = get_inode(fd);
	printf("file inode is ======== => [%lu]\n", (unsigned long)inode);

	return EXIT_SUCCESS;
}

