

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int
main() {
    int i;
    int size;
    printf("Enter the size of the array : ");
    scanf("%d", &size);

    // malloc returns a void pointer, 
    // so we know that our array is an int-array
    // so we cast the returned pointer from malloc to an int pointer (int *)
    // so we have a pointer-to-integer in memory.

    int* arr = (int*)malloc(sizeof(int) * size);
    if (arr == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    printf("The initial values in the array are : \n");
    for (size_t i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("Enter %d elements of array: \n", size);
    for (int i = 0; i < size; ++i)
        scanf("%d", &arr[i]);

    printf("Elements of the array : \n");
    for (int i = 0; i < size; ++i)
        printf("data -> %d\n", arr[i]);
    printf("\n");

    int newsize;
    printf("Enter new size of array: ");
    scanf("%d", newsize);

    int* nptr = (int*)realloc(arr, sizeof(int) * newsize);
    if (nptr == NULL) {
        perror("realloc");
        free(arr);
        return EXIT_FAILURE;
    } else {
        arr = nptr;
    }

    printf("The  resized array elements are : \n");
    for (size_t i = 0; i < newsize; i++)
    {
        printf("%d \t", arr[i]);
    }
    printf("\n");

    free(arr);

    return EXIT_SUCCESS;
}