

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define _GNU_SOURCE
#include <limits.h>


int main() {

	FILE* in, *out;

	struct pirate {
		char name[100];
		unsigned long booty;
		unsigned int beard_len;
	} p, blackbeard = { "Edward", 950, 48 };

	out = fopen("data", "w");
	if (out == NULL) {
		perror("fopen");
		return EXIT_FAILURE;
	}

	if (!fwrite(&blackbeard, sizeof(struct pirate), 1, out)) {
		perror("fwrite");
		return EXIT_FAILURE;
	}

	if (fclose(out)) {
		perror("fclose");
		return EXIT_FAILURE;
	}

	in = fopen("data", "r");
	if (in == NULL) {
		perror("fopen");
		return EXIT_FAILURE;
	}

	if (!fread(&p, sizeof(struct pirate), 1, in)) {
		perror("fread");
		return EXIT_FAILURE;
	}

	if (fclose(in)) {
		perror("fclose");
		return EXIT_FAILURE;
	}

	printf("name=\"%s\" booty=%lu beard_len=%u\n", p.name, p.booty, p.beard_len);
	return EXIT_SUCCESS;
}

