#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <errno.h>

extern int errno;

int main() {

	struct rlimit limit;
	getrlimit(RLIMIT_NOFILE, &limit);

	printf("%s ", "RLIMIT_NOFILE");

	if (limit.rlim_cur == RLIM_INFINITY)
		printf("infinity\n");
	else
		printf("  %d  ", limit.rlim_cur);

	if (limit.rlim_max == RLIM_INFINITY)
		printf(" INFINITY \n");
	else
		printf("  %d  \n", limit.rlim_max);

	return 0;

