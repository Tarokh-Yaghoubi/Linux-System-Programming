#include <stdio.h>
#include <unistd.h>

/*
 * this shows that even your programme has a parent ID which the SHELL that runs it
 */

// echo $$ after running the programme to see the SHELL PID

int main(void) {
    printf("My PID:    %d\n", getpid());
    printf("My PPID:   %d\n", getppid());
    return 0;
}
