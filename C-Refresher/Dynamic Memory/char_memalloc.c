
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int
main(int argc, char* argv[]) {

    int size;
    printf("Enter maximum size of sentence you want to enter and store : ");
    scanf("%d", &size);
    getchar();  // to eat the \n in scanf

    char* line = (char *) malloc(sizeof(char) * size);
    printf("Now enter the sentence: \n");
    fgets(line, size, stdin);

    char* q;
    if ((q = strchr(line, '\n')) != '\0')
        *q = '\0';

    fputs(line, stdout);
    free(line);

    return 0;

}