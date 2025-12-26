
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int
main() {

    int fd = open("fcntl_lock.c", O_WRONLY);
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();
    int rv = fcntl(fd, F_SETLK, &lock);
    if (rv == -1) {
        printf("Lock cant be acquired \n");
        exit(1);
    }

    printf("File is successfully locked...\n");
    while(1) {}
    return 0;
}