

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void myexit(int exitStatus, void* arg) {
	printf("Exit handler called with exit status = %d and arg = %ld \n", exitStatus, (long)arg);

}

int main() {

	on_exit(myexit, (void*)7);
	printf("This is Main\n");
	exit(54);
}
