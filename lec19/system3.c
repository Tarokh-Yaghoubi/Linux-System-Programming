

#include "../headers.h"

int 
main() {
	char cmd[50] = {0};
	int cpid;

	do {
		printf("PUCIT : - ");
		fgets(cmd, 50, stdin);
		system(cmd);
	} while(1);

	return EXIT_SUCCESS;
}
