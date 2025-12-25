
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

extern int errno;

int
main() {

  
    if (access("f1", F_OK) == 0) 
        remove("f1");
    else {
        printf("file does not exist, creating it...");
    }
  

    int fd = open("f1", O_RDWR | O_CREAT | O_TRUNC, 0622);
    printf("[tarokh]- returned fd = %d\n", fd);

    int cfo = lseek(fd, 0, SEEK_CUR);
    printf("Location of CFO is -> [%d]\n", cfo);


    lseek(fd, 100, SEEK_END);   // MOVE 100 BYTES TO THE END OF THE FILE (CREATING HOLES)
    write(fd, "ABCDE", 5);
    cfo = lseek(fd, 0, SEEK_CUR);
    printf("Location of CFO after writing \"ABCDE\" is => [%d]\n", cfo);


    close(fd);

    return 0;
}
