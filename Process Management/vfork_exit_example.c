

#include "../headers.h"

int main() {
	fprintf(stdout, "hello");

	pid_t pid = vfork();
	if (pid == 0) {
		// here is the child
		exit(0);	// this is wrong, u must use _exit(), when vfork()
	}

	fprintf(stdout, "world\n");	 // undefined behaviour
	
	return EXIT_SUCCESS;
}
