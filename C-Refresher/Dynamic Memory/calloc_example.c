
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Man {
    int rollno;
    char name[30];
} s1;

int
main() {

    int i;
    int size = 5;

    struct Man* arrayOfMen = (struct Man*)calloc(size, sizeof(s1) * size);
    if (arrayOfMen == NULL) {
        perror("calloc");
        return -1;
    }

    int j  = 0;
    for (size_t i = 0; i < size; i++)
    {
        arrayOfMen[i].rollno = ++j;
        strcpy(arrayOfMen[i].name, "Default");
    }

    for (size_t i = 0; i < size; i++)
    {
        printf("The rollno is -> %d\n", arrayOfMen[i].rollno);
        printf("The name is -> [%s]\n", arrayOfMen[i].name);
        printf("\n");
    }

    free(arrayOfMen);
    
    return 0;

}