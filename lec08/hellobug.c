

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

extern int errno;

int
main(int argc, char * argv[]) {

    char* arr = (char *) malloc (sizeof(char) * 10);
    if (arr == NULL) {
        perror("malloc");
        exit(errno);
    }

    arr[0] = 't';
    arr[1] = 'a';
    arr[2] = 'r';
    arr[3] = 'o';
    arr[4] = 'k';
    arr[5] = 'h';
    arr[6] = '\0';
    printf("[%s]\n", arr);

    free(arr);

    arr[0] = 'X';   // this causes bug because memory is freed

    return 0;
}

