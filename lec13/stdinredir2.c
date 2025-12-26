

// this time i wanna open the file first, then i wanna close the '0' descriptor
// so when i use dup(), it will choose the lowest descriptor which is '0'

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int
main() {


    char line[100] = {0};

    fgets(line, 100, stdin);

    int fd = open("/etc/passwd", O_RDONLY);
    close(0);
    int newfd = dup(fd);    // this will now attach descriptor '0' to the file
    close(fd);  // now i close the old descriptor as well. 
    printf("the new fd is ----- -> %d\n", newfd);
    fgets(line, 100, stdin);
    printf("%s\n", line);

    return 0;

}
