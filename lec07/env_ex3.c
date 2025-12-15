
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int 
main() {

    char * historysize = getenv("HISTSIZE");
    printf("ORIGINAL HISTSIZE IS -> [%s]\n", historysize);

    putenv("HISTSIZE=500");
    historysize = getenv("HISTSIZE");
    printf("CHANGED HISTSIZE IS -> [%s]\n", historysize);

    setenv("HISTSIZE", "300", 1);
    historysize = getenv("HISTSIZE");
    printf("Changed value of HISTSIZE after setenv: %s\n", historysize);

    return 0;

}
