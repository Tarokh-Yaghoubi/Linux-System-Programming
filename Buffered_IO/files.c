#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {

    FILE* stream;

    int fd = open("test", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    stream = fopen("/etc/manifest", "r");
    if (stream == NULL) {
        perror("fopen");
        return -1;
    } else {
        printf("CORRECT\n");
    }

    stream = fdopen(fd, "r");
    if (!stream) {
        printf("failed on fdopen");
        return EXIT_FAILURE;
    }


    fclose(stream);
    
    // this closes all streams, flushes remained data, and closes the stream.
    // on error they return EOF
    fcloseall();
    return EXIT_SUCCESS;
}
