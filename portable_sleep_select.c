

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


int
main() {

	struct timeval val;
	val.tv_sec = 0;
	val.tv_usec = 500;
	// sleep for 500 milliseconds
	select(0, NULL, NULL, NULL, &val);

	return EXIT_SUCCESS;
}

