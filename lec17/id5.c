
#define _GNU_SOURCE

#include "../headers.h"

int
main() {
	uid_t ruid, euid, suid;
	getresuid(&ruid, &euid, &suid);
	printf("my real user id is => %d\n", (long)ruid);
	printf("my effective user id is => %ld\n", (long)euid);
	printf("my saved  set-user id  is => %ld\n", (long)suid);

	int rv = setresuid(100, 2000, 3000);
	if (rv == -1) {
		perror("setresuid");
		return EXIT_FAILURE;
	}

	getresuid(&ruid, &euid, &suid);
	printf("\n\nafter setuid(2000) the IDS are => \n");
	printf("my real user id is => %ld\n", (long)ruid);
	printf("my effective user id is => %ld\n", (long)euid);
	printf("my saved  set-user id  is => %ld\n", (long)suid);

	return EXIT_SUCCESS;
}
