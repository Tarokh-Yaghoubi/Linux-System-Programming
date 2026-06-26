#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
/*
 * this shows that even your programme has a parent ID which the SHELL that runs it
 */

// echo $$ after running the programme to see the SHELL PID

int main(void) {
    
    printf ("My pid=%d\n",  getpid ());
    printf ("Parent's pid=%d\n", getppid ());
    
    return 0;
}
