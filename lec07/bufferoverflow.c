

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display(char* data) {
    char buff[10];
    strcpy(buff, data);
    printf("Data is -> [%s]\n", buff);
}

int 
main(int argc, char* argv[]) {

    if (argc > 1)
        display(argv[1]);
    else
        printf("No commandline received\n");

    
    exit(0);
}