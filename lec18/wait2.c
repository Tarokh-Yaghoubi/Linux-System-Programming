
#include "../headers.h"

int
main() {
	pid_t cpid = fork();
	if (cpid == 0) {
		printf("Hello I am child\n");
		sleep(1);
		printf("I am child again, and my pid is %ld\n",(long) getpid());
		sleep(1);
		exit(7);
	} else {
		int status = 0;
		pid_t ret = wait(&status);
		
		int low_8 = status & 0xff;
		int hight_8 = status >> 8;
		if (low_8 == 0)
			printf("return value of wait is %d, status is => %d\n", ret, hight_8);

		printf("Hello I am parent => %d\n", status);
		exit(54);
	}

	return EXIT_SUCCESS;
}
