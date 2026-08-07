
#include "../headers.h"
#include <pthread.h>

void * f1(void *);
void * f2(void *);

int
main() {

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, f1, NULL);
    pthread_create(&thread2, NULL, f2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("BYE BYE \n");
    return EXIT_SUCCESS;
}

void * f1(void * arg) {
    for (int i = 0; i < 1000; i++)
        fprintf(stderr, "%c", 'x');
        
    
    pthread_exit(NULL);
}


void * f2(void * arg) {
    for (int i = 0; i < 800; i++)
        fprintf(stderr, "%c", 'O');
    
    pthread_exit(NULL);
}
