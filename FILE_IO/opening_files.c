

#include <stdio.h>
#include <unistd.h>


int main() {

	int fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP | S_IROTH);

	// we could have written this for identical effect
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// 4 -> read
	// 2 -> write
	// 1 -> execute
	// 0777 -> read/write/exec for all users and groups

	if (fd == -1)
		perror("open");

	return EXIT_SUCCESS;
}
