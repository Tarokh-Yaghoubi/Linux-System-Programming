

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {

	int ret = truncate("./test", 45);
	if (ret == -1) {
		perror("truncate");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

