
#include "../../headers.h"

int
main() {

	// vfork guarantees that the parent will wait until the child 
	// returns, and then it continue execution. 
	// so if you want concurrency, you must use fork() and not vfork()
	// vfork() waits for a return or exit from the child.
	pid_t cpid = vfork();
	if (cpid == -1) {
		perror("vfork");
		return EXIT_FAILURE;
	}

	if (cpid == 0) {
		sleep(1);
		printf("Hello I am a child\n");
		sleep(2);
		printf("I am stilll the child\n");
		sleep(2);
		_exit(EXIT_SUCCESS);
	} else {
		printf("\nHello I am the parent, my child has terminated\n");
		exit(EXIT_SUCCESS);
	}

	return EXIT_SUCCESS;

}
