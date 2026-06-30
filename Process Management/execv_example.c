

#include "../headers.h"
#include <fcntl.h>


int
main(void) {

	int ret;
	char * argv[] = {"vim", "~/note", NULL };
	ret = execvp("vim", argv);
	if (ret == -1) {
		perror("execvp");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;

}
