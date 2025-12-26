
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int
main() {

    char line[100];

    fgets(line, 100, stdin);
    printf("%s\n", line);

    close(0);

    int fd = open("/etc/passwd", O_RDONLY);
    printf("fd is -> %d\n", fd);
    fgets(line, 100, stdin);
    printf("%s\n", line);

    return 0;

}