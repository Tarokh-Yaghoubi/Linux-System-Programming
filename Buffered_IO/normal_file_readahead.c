

/*

⣿⡇⠄⡴⠁⡜⣵⢗⢀⠄⢠⡔⠁⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄
⣿⡇⡜⠄⡜⠄⠄⠄⠉⣠⠋⠠⠄⢀⡄⠄⠄⣠⣆⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢸
⣿⠸⠄⡼⠄⠄⠄⠄⢰⠁⠄⠄⠄⠈⣀⣠⣬⣭⣛⠄⠁⠄⡄⠄⠄⠄⠄⠄⢀⣿
⣏⠄⢀⠁⠄⠄⠄⠄⠇⢀⣠⣴⣶⣿⣿⣿⣿⣿⣿⡇⠄⠄⡇⠄⠄⠄⠄⢀⣾⣿
⣿⣸⠈⠄⠄⠰⠾⠴⢾⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⢁⣾⢀⠁⠄⠄⠄⢠⢸⣿⣿
⣿⣿⣆⠄⠆⠄⣦⣶⣦⣌⣿⣿⣿⣿⣷⣋⣀⣈⠙⠛⡛⠌⠄⠄⠄⠄⢸⢸⣿⣿
⣿⣿⣿⠄⠄⠄⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠈⠄⠄⠄⠄⠄⠈⢸⣿⣿
⣿⣿⣿⠄⠄⠄⠘⣿⣿⣿⡆⢀⣈⣉⢉⣿⣿⣯⣄⡄⠄⠄⠄⠄⠄⠄⠄⠈⣿⣿
⣿⣿⡟⡜⠄⠄⠄⠄⠙⠿⣿⣧⣽⣍⣾⣿⠿⠛⠁⠄⠄⠄⠄⠄⠄⠄⠄⠃⢿⣿
⣿⡿⠰⠄⠄⠄⠄⠄⠄⠄⠄⠈⠉⠩⠔⠒⠉⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠐⠘⣿ 

*/

/*

	REMEMBER THIS IMAGE, FOR (CHS)

outer track (track 0)
       ╭─────────────╮
      ╱   middle track  ╲
     │   ╭───────────╮   │
     │  ╱ inner track  ╲  │
     │ │  ╭─────────╮  │ │
     │ │ │           │ │ │
     │ │  ╰─────────╯  │ │
     │  ╲             ╱  │
     │   ╰───────────╯   │
      ╲                 ╱
       ╰─────────────╯

    ╭───╮
  ╱ 1 │ 2 ╲
 │ 8  │  3 │
 │ 7  │  4 │
  ╲ 6 │ 5 ╱
    ╰───╯

*/


#define _GNU_SOURCE

#include "../headers.h"
#include <fcntl.h>
#include <sys/stat.h>


int
main(void) {

	char * buffer;	
	int ret = 0, fd;
	struct stat st;
	
	memset(&st, 0, sizeof(struct stat));

	fd = open("test.dat", O_RDWR);
	if (fd < 0) {
		perror("open");
		return EXIT_FAILURE;
	}

	if (fstat(fd, &st) == -1) {
		perror("fstat");
		close(fd);
		return EXIT_FAILURE;
	}

	off_t file_size = st.st_size;
	
	ret = readahead(fd, 0, file_size);
	if (ret < 0) {
		perror("posix_fadvise");
		close(fd);
		return EXIT_FAILURE;
	}

	printf("wait for three seconds...\n");
	sleep(3);

	buffer = malloc(file_size);

	ssize_t read_size = read(fd, buffer, file_size);
	if (read_size == 0) {
		perror("read");
		close(fd);
		return EXIT_FAILURE;
	}

	printf("read_size=%d\ndata=>%s\n", read_size, buffer);
	free(buffer);
	close(fd);
	return EXIT_SUCCESS;
}


