
// the same program, instead of dup() I'll use dup2()


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int
main() {

    char line[100] = {0};
    fgets(line, 100, stdin);
    printf("%s\n", line);

    int fd = open("/etc/passwd", O_RDONLY);
    close(0);
    int newfd = dup2(fd, 0);
    printf("new file descriptor is ----- -> %d\n", newfd);
    close(fd);

    fgets(line, 100, stdin);
    printf("%s\n", line);

    close(newfd);
    return 0;
}
