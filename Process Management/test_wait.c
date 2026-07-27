
#include "../headers.h"
#include <errno.h>

int
main() {
	int val = 34;
 	pid_t pid = wait(&val);
	if (pid < 0) {
		if (errno == ECHILD)
			printf("There is no child for this process");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
} 
