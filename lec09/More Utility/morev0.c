

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <string.h>

// morev0.c: get single filename from command-line arguments, print the entire content
// in the output, and exit.

#define LINELEN 512
void do_more(FILE *filename);

int
main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("This is the help page\n");
        exit (0);
    }

    FILE* fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("fopen");
        exit(-1);
    }
    do_more(fp);
    fclose(fp);
    return 0;
}

void
do_more(FILE* filename) {
    char buffer[LINELEN];
    while (fgets(buffer, LINELEN, filename)) {
        fputs(buffer, stdout);
    }
}