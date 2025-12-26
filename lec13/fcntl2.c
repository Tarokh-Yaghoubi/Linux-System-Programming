#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int
main(int argc, char* argv[]) {

    int fd = open("/etc/passwd", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    int ret = fcntl(fd, F_GETFL, 0);
    ret = ret & O_ACCMODE;
    switch (ret)
    {
        case O_RDONLY:
            printf("Access mode : O_RDONLY\n");
            break;
        case O_WRONLY:
            printf("Access mode : O_WRONLY\n");
            break;
        case O_RDWR:
            printf("Access mode : O_RDWR\n");
            break;
        default:
            printf("None of above\n");
            break;
    }

    if (ret & O_APPEND)
        printf("Flag: O_APPEND (append mode)\n");

    if (ret & O_NONBLOCK)
        printf("Flag: O_NONBLOCK (non-blocking I/O)\n");


    close(fd);
    return 0;

}
