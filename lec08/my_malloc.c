

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void*
my_malloc(size_t size) {
    void* old_brk = sbrk(size);
    if (old_brk == (void*)-1) {
        return NULL;
    }

    // return the start of the new space 
    return old_brk;
}

int
main() {
    char* p = my_malloc(sizeof(char) * 10);
    if (p != NULL) {
        sprintf(p, "(Tarokh)");
        printf("%s\n", p);
    }

    // free(p);
    return 0;
}