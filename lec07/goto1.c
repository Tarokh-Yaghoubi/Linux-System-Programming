

#include <stdio.h>

int
main() {

    printf("Start of loop. \n");
    int ctr = 1;
    
    label1: {
        printf(" TAROKH\n");
        ctr++;
    
        if (ctr == 6)
            goto label2;
    
        goto label1;
    }

    label2: {
        printf(" OUT OF THE LOOP\n");
    }
    
    return 0;
}   