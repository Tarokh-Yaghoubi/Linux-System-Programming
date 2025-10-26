

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>


int main() {
	int ret;
	ret =  truncate("./test", 59);
	if (ret == -1) {
		perror("truncate");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

