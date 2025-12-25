

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

extern int errno;



int
main(int argc, char* argv[]) {

    int holes;
    if (argc > 1)
        holes = atoi(argv[1]);
    else if (argc == 1)
        holes = 2;

    
    if (access("filewithholes", F_OK) == 0)
        remove("filewithholes");

    int fd = open("filewithholes", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    write(fd, "TAROKH", 6);
    for (size_t i = 0; i < holes; i++)
    {
        lseek(fd, 10, SEEK_CUR);
        write(fd, "TAROKH", 6);
    }

    close(fd);
    return 0;
}