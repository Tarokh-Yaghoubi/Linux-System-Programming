

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
    

    // here i used dup() func, just to duplicate the file-descriptor of the file 
    // as a test, these two file descriptors now point to the same file
    // so we can read from 'fd' but write to 'dupfd', and the same file 
    // is getting affected.
    
    int dupfd = dup(fd);

    if (dupfd == -1) {
        perror("open");
        return -1;
    }

    write(dupfd, "TAROKH", 6);
    for (size_t i = 0; i < holes; i++)
    {
        lseek(dupfd, 10, SEEK_CUR);
        write(fd, "TAROKH", 6); 
    }

    close(fd);
    return 0;
}