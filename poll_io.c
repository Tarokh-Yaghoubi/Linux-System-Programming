
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>

// specified header file 
#include <poll.h>

#include <arpa/inet.h>

#define PORT 8080
#define MAX_FDS 1024
#define BUF_SIZE 4096

int main() {

	// poll is a System V Unix System call for waiting on multiple file descriptors, just like select() and pselect(), but better in many ways.
	// - Hey Kernel, watch these three file descriptors, wake me up when any of them have data to read, can accept writes, or have an error.
// poll params:	
// poll(array of struct pollfd[one per fd], how many fd's your're watching, milliseconds to wait: [0 = dont wait, -1 = wait forever, > 0 wait that many ms])
	
	// struct pollfd:
	// int fd; -> the fd => [socket, file, pipe, etc]
	// short events;  -> what YOU want to watch for
	// short revents; -> what Actually happened (filled by kernel)

	int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_fd == -1) {
		perror("socket");
		exit(1);
	}

	int opt = 1;
	setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);

	if (bind(listen_fd, (struct sockaddr_in*)&addr, sizeof(addr)) == -1) {
		perror("bind");
		exit(1);
	}

	if (listen(listen_fd, SOMAXCONN) == -1) {
		perror("listen");
		exit(1);
	}

	// ARRAY OF POLLFD STRUCTURES 

	return 0;
}
