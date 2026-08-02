

#include "../headers.h"

void create_daemon();

int main() {

	create_daemon();
	while (1) {}
}

void create_daemon() {

	pid_t cpid = fork();
	if (cpid > 0)
		exit(EXIT_SUCCESS);

	struct rlimit r;
	getrlimit(RLIMIT_NOFILE, &r);
	for (int i = 3; i < r.rlim_max; i++)
		close(i);

	int fd = open("f1.txt", O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fd == -1) {
		perror("open");
	}

	struct flock lock;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	int rv = fcntl(fd, F_SETLK, &lock);
	if (rv == -1) {
		printf("This process is already running\n");
		close(fd);
		exit(EXIT_FAILURE);
	}

	fprintf(stderr, "Daemon has started running with pid = %d\n", getpid());

	int fd0 = open("/dev/null", O_RDWR);
	dup2(fd0, 1);
	dup2(fd0, 2);

	// make the daemon session leader, and set umask to 0 and its pwd to ROOT
	setsid();
	umask(0);
	chdir("/");

	// ignore the sighup signal
	signal(SIGHUP, SIG_IGN);
}
