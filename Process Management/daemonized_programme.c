
#include "../headers.h"
#include <sys/stat.h>
#include <linux/fs.h>


int
main(void) {
	pid_t pid;
	int i;

	pid = fork();
	if (pid == -1)
		return EXIT_FAILURE;
	else if (pid != 0)
		exit(EXIT_SUCCESS);

	if (setsid() == -1)
		return EXIT_FAILURE;

	if (chdir("/") == -1)
		return EXIT_FAILURE;


	for (i = 0; i < NR_OPEN; i++)
		close(i);

	open("/dev/null", O_RDWR);
	dup(0);
	dup(0);


	// DO ITS DAEMON THING

	return EXIT_SUCCESS;

}
