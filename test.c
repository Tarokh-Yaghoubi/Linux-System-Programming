
#include "headers.h"


int main() {

	char buffer[64] = {0};
	char * key = "D8C91584B7633E7D";
	for (int i = 0; i < strlen(key); i += 2) {
		sprintf(&buffer[i], "0x%s", key[i]);
	}

	printf("buffer ==== > %s", buffer);
	return 0;


}
