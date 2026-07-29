
// getresuid and getresgid are linux-specific so we need to define this macro before calling them
#define _GNU_SOURCE

#include "../headers.h"

int
main() {
	uid_t ruid, euid, suid;
	getresuid(&ruid, &euid, &suid);
	printf("My real user-id is: %ld\n", (long)ruid);
	printf("My Effective user-id is => %ld\n", (long)euid);
	printf("My saved set-user is => %ld\n", (long)suid);

	gid_t rgid, egid, sgid;
	getresgid(&rgid, &egid, &sgid);
	printf("My real group ID is => %ld\n", (long)rgid);
	printf("My effective group ID is => %ld\n", (long)egid);
	printf("My saved set-group ID is => %ld\n", (long)sgid);
	return EXIT_SUCCESS;

}	
