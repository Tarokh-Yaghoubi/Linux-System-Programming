
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define _GNU_SOURCE 


int main() {

	FILE* stream = fopen("hugefile.bin", "rb");
	if (stream == NULL) {
		perror("fopen");
		return EXIT_FAILURE;
	}

	fpos_t saved_position;	// this can hold ANY valid position.
	char buffer[100];
	
	fread(buffer, 1, 100, stream);

	if (fgetpos(stream, &saved_position) != 0) {
		perror("fgetpos");
		return EXIT_FAILURE;
	}

	fseek(stream, 1000000000L, SEEK_SET);

	if (fsetpos(stream, &saved_position) != 0) {
		perror("fsetpos");
		return EXIT_FAILURE;
	}

	fread(buffer, 1, 50, stream);

	if (ferror(stream)) {
		printf("Error on stream\n");
		return EXIT_FAILURE;
	} 

	if (peof(stream)) {
		printf("EOF on stream\n");
		return EXIT_FAILURE;
	}

	// This function clears error and the EOF indicators for the stream.
	clearerr(stream);

	fclose(stream);

	return EXIT_SUCCESS;
}
