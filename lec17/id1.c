
#include "../headers.h"

int
main() {

	printf("My pid is => %ld\n", (long)getpid());
	printf("My parent id => %ld\n", (long)getppid());

	return EXIT_SUCCESS;
}
