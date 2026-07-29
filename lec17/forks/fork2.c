
#define _GNU_SOURCE

#include "../../headers.h"

int
main() {
	int cpid = fork();
	if (cpid == -1)
		return EXIT_FAILURE;

	if (cpid == 0) {
		while (1)
			putchar('x');
	} else {
		while(1)
			putc('o', stdout);
	}

	return EXIT_SUCCESS;

}
