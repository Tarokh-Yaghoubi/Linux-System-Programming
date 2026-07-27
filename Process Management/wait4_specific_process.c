

#include "../headers.h"
#include <sys/resource.h>

int
main(int argc, char * argv[]) {
	pid_t compress_pid, encrypt_pid, upload_pid;
	struct rusage usage;

	compress_pid = fork();
	if (compress_pid == -1) { perror("fork"); return EXIT_FAILURE; }
	if (compress_pid == 0) {
		printf("compressing...\n");
		sleep(2);
		printf("compression done\n");
		_exit(EXIT_SUCCESS);
	}

	encrypt_pid = fork();
	if (encrypt_pid == -1)  { perror("fork"); return EXIT_FAILURE; }
	if (encrypt_pid == 0) {
		printf("encrypting...\n");
		sleep(3);
		printf("encryption done\n");
		_exit(EXIT_SUCCESS);
	}

	// parent waits specifically for the encryption to finish before starting the upload.
	int status;
	pid_t ret = wait4(encrypt_pid, &status, 0, &usage);
	if (ret == -1) {
		perror("waitpid");
		return EXIT_FAILURE;
	}

	printf("some encrypt children data=>\nmemsize=[%ld]\nsignals_received=[%ld]\nvoluntary_context_switch=[%ld]\n", 
			usage.ru_ixrss, usage.ru_nsignals, usage.ru_nvcsw);

	// here we know that the encryption is done, it is safe to start the upload process
	
	upload_pid = fork();
	if (upload_pid == -1)  { perror("fork"); return EXIT_FAILURE; }
	if (upload_pid == 0) {
		printf("uploading encrypted file...\n");
		sleep(2);
		printf("upload done.\n");
		_exit(EXIT_SUCCESS);
	}

	waitpid(upload_pid, NULL, 0);
	waitpid(compress_pid, NULL, 0);

	printf("all done\n");
	return EXIT_SUCCESS;

}
