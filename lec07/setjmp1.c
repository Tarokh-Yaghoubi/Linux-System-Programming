

#include <stdio.h>
#include <setjmp.h>

static jmp_buf envbuf;

int
main() {

    int i;
    printf("This is main()\n");

    if ((i = setjmp(envbuf)) == 0) {
        printf("VALUE OF I = %d\n", i);
        func();
        printf("This will not be printed\n");
    }

    printf("This is main() again.\n");
    printf("Value of i = %d\n", i);
    return 0;

}

void 
func() {
    printf("This is fun\n");
    longjmp(envbuf, 50);
}
