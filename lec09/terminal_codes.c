
#include <stdio.h>
#include <unistd.h>

int 
main(int argc, char* argv[]) {

    // Some examples using the terminal codes 

    printf("\e[7m This is in reverse video\n");
    printf("\033[m This is in normal video\n");
    printf("\033[1m This is in bold \033[m \n");
    printf("\033[4m This is in underline mode \033[m \n");

    printf("\033[35m \033[40m This is in magenta and black background \n");
    printf("\033[10G This will start from column 10\n");

    return 0;
}