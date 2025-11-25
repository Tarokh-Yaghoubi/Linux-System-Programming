#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include <errno.h>

#define _GNU_SOURCE
#include <limits.h>

char* my_fgets_delim(char* str, int n, int d, FILE* stream);

int main() {

    FILE* stream;

    stream = fopen("/etc/manifest", "r");
    if (stream == NULL) {
        perror("fopen");
        return -1;
    } else {
        printf("CORRECT\n");
    }
    
    fseek(stream, 2, SEEK_SET);

    int c = fgetc(stream);
    if (c == EOF) {
        perror("fgetc");
        return EXIT_FAILURE;
    } else {
        printf("c=%c\n", (char)c);
        if ((char)c == 'a')
            printf("AAAAAAAAAAAAA\n");
    }
    // fseek(stream, 0, SEEK_SET);
    errno = 0;
    rewind(stream);
    if (errno) {
	perror("rewind");
    }
    char buffer[LINE_MAX];
    
    // now my stream has opened a file, so i can read its data line by line 
    
    if (!fgets(buffer, 100, stream)) {
        perror("fgets");
        return EXIT_FAILURE;
    }

    printf("BUFFER -> [%s]\n", buffer);

    char buf[100];
    my_fgets_delim(buf, sizeof(buf), ':', stdin);


    int fd = open("test", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    stream = fdopen(fd, "r");
    if (!stream) {
        printf("failed on fdopen");
        return EXIT_FAILURE;
    }


    fclose(stream);
    
    // this closes all streams, flushes remained data, and closes the stream.
    // on error they return EOF
    // fcloseall();
    return EXIT_SUCCESS;
}



char* my_fgets_delim(char* str, int n, int d, FILE* stream) {
    char* s = str;
    int c;

    // now i will pass a buffer with its size, it will start taking inputs 
    // that fits the size of the buffer, and when it meets a delimiter or EOF 
    // it will null-terminate and stop.

    while (--n > 0 && (c = fgetc(stream)) != EOF && (*s = c) != d) {
        s++;
    }

    if (c == d) {
        *s = '\0';
    } else {
        *s = '\0';
    }

    return (c == EOF && s == str) ? NULL : str;

}
