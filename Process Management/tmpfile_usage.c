
#include "../headers.h"

int
main(void) {

	FILE * tmp = tmpfile();
	if (!tmp) {
		perror("tmpfile");
		return EXIT_FAILURE;
	}

	fprintf(tmp, "a test sentence in the temp file\n");

	rewind(tmp);

	char buf[64] = {0};
	fgets(buf, sizeof(buf), tmp);

	printf("buf=%s", buf);

	fclose(tmp);
	return EXIT_SUCCESS;

}
