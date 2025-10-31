
#define _GNU_SOURCE

#include <string.h>

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
	
	struct pollfd fds[MAX_FDS]; // one struct per file descriptor 
	
	int nfds = 1;	 // starts with one 

	fds[0].fd = listen_fd;
	fds[0].events = POLLIN;

	printf("[POLL] server listening to port -> %d\n", PORT);


	while (1) {
		int ready = poll(fds, nfds, -1);

		if (read == -1) {
			if (errno == EINTR)
				continue;
			perror("poll");
			break;
		}

		for (int i = 0; i < nfds; i++) {
		
			if (fds[i].revents == 0)
				continue;

			if (fds[i].fd == listen_fd) {
				struct sockaddr_in client_addr;
				socklen_t len = sizeof(client_addr);
				int client_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &len);
				if (client_fd == -1) {
					perror("accept");
					continue;
				}

				char ip[INET_ADDRSTRLEN];
				inet_ntop(AF_INET, &client_addr.sin_addr, ip, sizeof(ip));
				printf("New Client: %s:%d (fd=%d)\n", ip, ntohs(client_addr.sin_port), client_fd);
				if (nfds < MAX_FDS) {
					fds[nfds].fd = client_fd;
					fds[nfds].events = POLLIN;
					nfds++;
				} else {
					printf("Too Many Clients ---- -> ");
					close(client_fd);
				}
			} else {
				// Client Socket: data or closed
				if (fds[i].revents & (POLLERR | POLLHUP | POLLNVAL)) {
					printf("Client fd=%d disconnected  or error\n", fds[i].fd);
					close(fds[i].fd);
					// remove from the array, shif-left
					memmove(&fds[i], &fds[i+1], (nfds - i - 1) * sizeof(struct pollfd));
					nfds--;
					i--;
					continue;
				}

				if (fds[i].revents & POLLIN) {
					// now data is available in the new connection, read the data...
				
					char buf[BUF_SIZE];
					ssize_t n = read(fds[i].fd, buf, sizeof(buf));
					if (n <= 0) {
						if (n == 0) 
							printf("Client fd=%d closed\n", fds[i].fd);
						else
							perror("read");

						close(fds[i].fd);
						memmove(&fds[i], &fds[i+1], (nfds - i - 1) * sizeof(struct pollfd));
						nfds--;
						i--;
						continue;
					}

					write(fds[i].fd, buf, n);
				}
			}
		}
	}

	close(listen_fd);
	return 0;
}
