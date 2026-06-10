

#include "headers.h"

#define LINE_MAX 1024

int main() {
	
	char buffer[LINE_MAX] = {0};
	FILE * f = fopen("test.dat", "a+");
	
	char f_chr = 'f';
	int res = fputc(f_chr, f);
	if (res == EOF) {
		perror("fputc faced error");
		return EXIT_FAILURE;
	}


	char write_buffer[] = {"Tarokh is a good man, but also he things devilish sometimes\n"};
	int len = sizeof(write_buffer);
	write_buffer[len] = '\0';
	res = fputs(write_buffer, f);

	if (res == EOF) {
		perror("fputs faced error");
		return EXIT_FAILURE;
	}


	int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	size_t written = fwrite(numbers, sizeof(int), sizeof(numbers)/sizeof(numbers[0]), f);
	printf("written using fwrite ======== => [%d]\n", written);

	long current = ftell(f);
	printf("current offset is %d\n", current);
	rewind(f);
	current = ftell(f);
	printf("current after rewind ==== ==> %d\n", current);
	
	char * ret = fgets(buffer, LINE_MAX, f);
	if (ret != NULL)
		printf("buffer ====== => [%s]\n", buffer);
	else
		printf("ret is null == => \n");

	
	fclose(f);

	return EXIT_SUCCESS;

}
