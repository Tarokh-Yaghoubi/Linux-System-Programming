
//multithreaded version of t0 programme 

#include "../headers.h"

void * f1(void *);
void * f2(void *);

int main() {

	pthread_t thread_id1, thread_id2;

	// create two child threads and wait for their termination
	pthread_create(&thread_id1, NULL, f1, NULL);
	pthread_create(&thread_id2, NULL, f2, NULL);

	pthread_join(thread_id1, NULL);
	pthread_join(thread_id2, NULL);

	printf("bye bye from main\n");
	return EXIT_SUCCESS;
}

void * f1(void *) {
	for (int i = 0; i < 5; i++) {
		printf("%s", "TAROKH");
		fflush(stdout);
		sleep(1);
	}
}

void * f2(void *) {
	for (int i = 0; i < 5; i++) {
		printf("%s", "JACOBS");
		fflush(stdout);
		sleep(1);
	}
}

