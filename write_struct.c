

#include "headers.h"
#include <stddef.h>

int
main() {


	FILE * in, * out;

#pragma pack(push, 1) // this forces the compiler to dont commit the alignment
	struct pirate {
		char name[100];
		unsigned long booty;
		unsigned int board_len;
	} p, blackbeard = {"Tarokh", 430, 23};
#pragma pack(pop)

	printf("sizeof struct pirate = %zu\n", sizeof(struct pirate));
	printf("offsetof(name)		= %zu\n", offsetof(struct pirate, name));
	printf("offsetof(booty)		= %zu\n", offsetof(struct pirate, booty));
	printf("offsetof(board_len)	= %zu\n", offsetof(struct pirate, board_len));


	out = fopen("test.dat", "w");
	if (out == NULL) {
		perror("fopen");
		return EXIT_FAILURE;
	}

	if (!fwrite(&blackbeard, sizeof (struct pirate), 1, out)) {
		perror("fwrite");
		return EXIT_FAILURE;
	}

	if (fclose(out)) {
		perror("fclose");
		return EXIT_FAILURE;
	}

	in = fopen("test.dat", "r");
	if (!in) {
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

	printf("name=%s\tbooty=%lu\tboardlen=%u\n", p.name, p.booty, p.board_len);

	return EXIT_SUCCESS;

}

