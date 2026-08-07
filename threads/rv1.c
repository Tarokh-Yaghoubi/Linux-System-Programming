
#include "../headers.h"
#include <pthread.h>

void * f1(void *);

int main(int argc, char * argv[]) {

    if (argc != 3) {
        printf("invalid arguments please enter two integers: \n");
        exit(EXIT_FAILURE);
    }

    int first = atoi(argv[1]);
    int second = atoi(argv[2]);

    pthread_t thread1, thread2;

    pthread_create(thread1, NULL, f1, (void *)&first);
    pthread_create(thread1, NULL, f1, (void *)&second);

    void * rv, * rv1;
    pthread_join(thread1, &rv);
    pthread_join(thread2, &rv1);

    long prime1 = *(long *)rv;
    long prime2 = *(long *)rv1;

    printf("\n The %dth prime number as returned by the child thread is => %ld\n", first, prime1);
    printf("\n The %dth prime number as returned by the child thread is => %ld\n", second, prime2);

    return EXIT_SUCCESS;
}

