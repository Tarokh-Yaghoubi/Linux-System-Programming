

#include "headers.h"

int 
main(void) {
	char buffer[] = {"Tarokh is a moderate programmer\n"};
	char test[] = {"Tarokh\n"};
	int testlen = sizeof(test) / sizeof(test[0]);
	int teststrlen = strlen(test);
	printf("teststrlen=%d\ttestlen=%d\n", teststrlen, testlen);

	FILE * stream = fopen("test.dat", "w+");
	int fd = fileno(stream);	// obtain the file descriptor backing the stream 
	printf("fd is => %d\n", fd);
	ssize_t written = fwrite(buffer, sizeof(char), strlen(buffer), stream);
	if (written == strlen(buffer))
		printf("size and len => [%d][%d]\n", written, strlen(buffer));
	else {
		printf("size and len [neq] => [%d][%d]\n", written, strlen(buffer));
		return EXIT_FAILURE;
	}

	int res = ferror(stream);
	printf("Res=[%d]\n", res);


	fflush(stream);
	fclose(stream);

	return EXIT_SUCCESS;
}
