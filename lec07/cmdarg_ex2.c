
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

    if (strcmp(argv[0], "./a.out") == 0)
        printf("I am called by the name a.out\n");
    else
        printf("I am called by another name\n");

    
    return 0;
}
