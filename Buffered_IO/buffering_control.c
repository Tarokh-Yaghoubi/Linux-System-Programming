
#define _GNU_SOURCE

#include  <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include  <errno.h>

int main() {

	char* buf = "read-only test line to write\n";

	FILE* stream;
	stream = fopen("test", "w");
	if (!stream) {
		perror("fopen");
		return EXIT_FAILURE;
	}

	// now the stream is opened, i can use setvbuf()
	
	int ret = setvbuf(stream, NULL, _IOLBF, 4096);
	if (ret != 0) {
		perror("setvbuf");
		return EXIT_FAILURE;
	}

	size_t n = fwrite(buf, 1, strlen(buf), stream);
	if (n == 0) {
		perror("fwrite");
		return EXIT_FAILURE;
	} else {
		printf("DATA WRITE SUCCESS --- -> [%d]\n", n);
	}

	return EXIT_SUCCESS;
}

