

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

	// there is also a specific call that contains that O_WRONLY | O_CREAT | O_TRUNC in it itself.
	// it is called creat() (without an 'e')
	
	int creat_fd = creat(file, 0644); // this is how it works
					  // this is identical to the open() syscall with O_WRONLY, ... flags
	if (creat_fd == -1)
		perror("creat");

	return EXIT_SUCCESS;
}
