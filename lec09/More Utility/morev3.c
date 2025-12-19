

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <string.h>

// morev0.c: get multiple file-names from command-line arguments, print the entire content
// of all the files in the output, and exit.

// added reverse-video feature

#define PAGELEN 10
#define LINELEN 512

void do_more(FILE *filename);
int get_input();

int
main(int argc, char* argv[]) {
    
    FILE* fp;
    int i = 0;

    if (argc == 1) {
        printf("This is the help page\n");
        exit (0);
    }

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
    int num_of_lines = 0;
    int rv;

    while (fgets(buffer, LINELEN, filename)) {

        fputs(buffer, stdout);
        num_of_lines++;
        if (num_of_lines == PAGELEN) {
            rv = get_input();
            if (rv == 0)    // user pressed q
            {   
                printf("\033[1A \033[2K \033[1G"); 
                break;
            }
            else if (rv == 1)   // user presses space
            {
                printf("\033[1A \033[2K \033[1G");
                num_of_lines -= PAGELEN;
            } 
            else if (rv == 2)   // user presses enter
            {
                printf("\033[1A \033[2K \033[1G");
                num_of_lines -= 1;
            }
            else if (rv == 3)   // something else / invalid character 
            {
                printf("\033[1A \033[2K \033[1G");
                break;
            }
        }
    }
}

int
get_input() {
    
    int c;
    printf("\033[7m --more--(%%) \033[m");
    c = getchar();
    
    if (c == 'q')
        return 0;
    else if (c == ' ')
        return 1;
    else if (c == '\n')
        return 2;
    else
        return 3;

    return 0;
}