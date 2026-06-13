
#include "../headers.h"
#include <sys/epoll.h>

int
main() {
	// first, you ask the kernel to create a watchlist. 
	// this is a kernel structure that holds the list of fds you have registered to watch,
	// what events you care about for each fd, and a ready list which contains the fds that currently have events pending.
	
	int epfd = epoll_create1(0);
	if (epfd < 0) {
		perror("epoll_create1");
		return EXIT_FAILURE;
	}



}
