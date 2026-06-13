
#define _GNU_SOURCE 

#include "headers.h"

int
main(void) {

	char buffer[] = {"Tarokh is a moderate programmer\n"};

	FILE * stream;
	stream = fopen("test.dat", "a+");
	if (stream == NULL) {
		perror("fopen");
		return EXIT_FAILURE;
	}

	flockfile(stream);
	fputs_unlocked(buffer, stream);
	fputs_unlocked(buffer, stream);
	fputs_unlocked(buffer, stream);
	funlockfile(stream);

	fflush(stream);
	fclose(stream);

	return	EXIT_SUCCESS;
}
