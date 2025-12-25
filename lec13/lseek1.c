

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

extern int errno;

int
main() {

    int rv = lseek(0, 54, SEEK_SET);
    if (rv == -1) {
        perror("lseek");
        return -1;
    } else
        printf("SEEK OK");


    return 0;
}
