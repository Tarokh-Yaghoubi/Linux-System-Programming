

#include "../headers.h"

void f1();
void f2();

int main() {
	f1();
	f2();
	printf("bye bye from main\n");
	return EXIT_SUCCESS;
}

void f1() {
	for (int i = 0; i < 5; i++) {
		printf("%s", "TAROKH");
		fflush(stdout);
		sleep(1);
	}
}

void f2() {
	for (int i = 0; i < 5; i++) {
		printf("%s", "JACOBS");
		fflush(stdout);
		sleep(1);
	}
}

