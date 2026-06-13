

#include "headers.h"

// This programme changes output streams behaviour.

int
main() {
	char buffer[BUFSIZ];
	
	setvbuf (stdout, buffer, _IOFBF, BUFSIZ);

	printf("ARRRRR\n");

	return EXIT_SUCCESS;

}
