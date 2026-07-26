
#include "headers.h"
#include <fcntl.h>

char * return_str() {

	char * str = malloc(100);
	char data[] = {"Tarokh is a moderate programmer\n"};
	for (int i = 0; i < strlen(data); i++) {
		str[i] = data[i];
	}

	return str;
}

int main() {

	char * res = return_str();
	printf("res data => [%s]\n", res);
	free(res);
	
	printf("dereference after free = %s\n", res);
	
	return EXIT_SUCCESS;
}
