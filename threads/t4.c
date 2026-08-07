
#include "../headers.h"
#include <pthread.h>

void * f1(void *);
void * f2(void *);

struct data {
    char character;
    int count;
};

int main() {
    pthread_t thread1, thread2;
    struct data d1 = {0};
    struct data d2 = {0};

    d1.character = 'x';
    d1.count = 100;
    d2.character = 'o';
    d2.count = 98;

    pthread_create(&thread1, NULL, f1, (void *)&d1);
    pthread_create(&thread2, NULL, f2, (void *)&d2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("\n bye bye from main thread\n");
    return EXIT_SUCCESS;

}

void * f1(void * args) {

    struct data tmp = *(struct data *)args;
    for (size_t i = 0; i < tmp.count; i++)
        fprintf(stderr, "%c", tmp.character);

    pthread_exit(NULL);

}

void * f2(void * args) {

    struct data tmp = *(struct data *)args;
    for (size_t i = 0; i < tmp.count; i++)
        fprintf(stderr, "%c", tmp.character);

    pthread_exit(NULL);
}