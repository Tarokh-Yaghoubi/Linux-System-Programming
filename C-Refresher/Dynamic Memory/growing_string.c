
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int
main() {

    char* line = (char *)malloc(1);     // [ |\0| ]
    line[0] = '\0';

    char ch;
    int bytes_allocated = 0;
    printf("Enter a sentence of any size you want and I will store it: \n");

    do {
        ch = getchar();
        if (ch == '\n')
            break;
        
        if (line[0] == '\0')
            line = (char *) realloc(line, 2);   // allocate two bytes

        else
            line = (char *)realloc(line, bytes_allocated + 2);

        line[bytes_allocated++] = ch;

    } while (ch != '\n');


    line[bytes_allocated] = '\0';
    printf("%s \n", line);
    free(line);
    return 0;

}