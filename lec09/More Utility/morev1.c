

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <string.h>

// morev0.c: get multiple file-names from command-line arguments, print the entire content
// of all the files in the output, and exit.

#define LINELEN 512

void do_more(FILE *filename);

int
main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("This is the help page\n");
        exit (0);
    }

    int i = 0;

    FILE* fp;

    while (++i < argc) {
        printf("=================FILE NUM [%d]=================\n", i);
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            perror("fopen");
            exit(-1);
        }
    
        do_more(fp);
        fclose(fp);
        
    }

    return 0;
}

void
do_more(FILE* filename) {
    char buffer[LINELEN];
    while (fgets(buffer, LINELEN, filename)) {
        fputs(buffer, stdout);
    }
}