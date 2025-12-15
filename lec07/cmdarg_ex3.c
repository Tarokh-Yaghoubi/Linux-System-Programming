

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


extern char **environ;

int main() {

    printf("\n Environ variables: \n");
    for (size_t i = 0; i < environ[i]; i++)
    {
        printf("environ[%d] : %s\n", i, environ[i]);
    }
    
    return 0;

}