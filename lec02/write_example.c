
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>

int write_direct_syscall() {
	char str[] = {"Tarokh is a normal programmer\n"};
	int rv = syscall(SYS_write, STDOUT_FILENO, str, sizeof(str));
	return rv;
}

int main(){ 
	write(1, "tarokh\n", 7);
	int rv = write_direct_syscall();
	return rv;
}
