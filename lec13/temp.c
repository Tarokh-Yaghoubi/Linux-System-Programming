

// i wanna open one file with two open syscalls and try read/writing on that
// using both fds

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

extern int errno;


int
main(int argc, char ** argv) {

    int fd1, fd2, n;
    char buff[10];
    fd1 = open("temp", O_RDONLY);
    fd2 = open("temp", O_RDONLY);

    n = read(fd1, buff, 5);
    write (1, buff, n);

    n = read(fd2, buff, 5);
    write(1, buff, n);
    
    n = read(fd1, buff, 5);
    write(1, buff, n);


    return 0;
    
}