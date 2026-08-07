
#include "../headers.h"
#include <pthread.h>

void * f1(void *);
void * f2(void *);


int
main(int argc, char * argv[]) {

    int countofX = atoi(argv[1]);
    int countofO = atoi(argv[2]);
    pthread_t thread1, thread2; 

    // last param expects an address, so we will get the address of what we wanna pass, and then
    // we will cast that to void*
    
    pthread_create(&thread1, NULL, f1, (void *)&countofX);
    pthread_create(&thread2, NULL, f2, (void *)&countofO);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("\n BYE BYE ======> \n");

    return EXIT_SUCCESS;
}


void * f1(void * args) {
    int ctr = *((int *)args);
    for (size_t i = 0; i < ctr; i++)
        fprintf(stderr, "%c", 'x');

    pthread_exit(NULL);
    
}

void * f2(void * args) {
    int ctr = *((int *)args);
    for (size_t i = 0; i < ctr; i++)
        fprintf(stderr, "%c", 'O');

    pthread_exit(NULL);
}