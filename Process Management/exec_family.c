

#include "../headers.h"
#include <sys/types.h>


int
main(void) {

	printf("created another process...\n");
		
	sleep(2);
		
		
	int ret;
	
	ret = execl("/bin/vim", "vim", "ppid_example.c", NULL);
	if (ret < 0) {
		
		perror("execl");
	
		return EXIT_FAILURE;
	
	}

	return EXIT_SUCCESS;

}
