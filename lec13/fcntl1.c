

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// fcntl systemcall can be used instead of dup() to return a duplicate fd of an 
// already opened file. the second argumen passed to fcntl() for this purpose is 
// F_DUPFD. it will return the lowest-numbered available file descriptor greater than
// or equal to the third argument.

int
main() {

    char line [100] = {0};
    fgets(line, 100, stdin);
    printf("%s\n", line);

    int fd = open("/etc/passwd", O_RDONLY); 
    close(0);
    int ret = fcntl(fd, F_DUPFD, 0);
    close(fd);
    printf("Duplicated file descriptor is ------> %d\n", ret);

    fgets(line, 100, stdin);
    printf("%s\n", line);

    close(ret);
    return 0;
}