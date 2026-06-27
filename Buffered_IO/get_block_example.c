

#include "../headers.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/fs.h>

struct BlockMapping {
	int logical;
	int physical;
};

int compare_blocks(const void * first, const void * second) {

	struct BlockMapping * first_block = (struct BlockMapping *)first;
	struct BlockMapping * second_block = (struct BlockMapping *)second;
	return (first_block->physical - second_block->physical);
}

int get_block(int fd, int logical_block) {

	int ret;
	ret = ioctl(fd, FIBMAP, &logical_block);
	if (ret < 0) {
		perror("ioctl");
		return EXIT_FAILURE;
	}

	return logical_block;
}

int get_nr_blocks(int fd) {
	struct stat buffer;
	int ret;
	memset(&buffer, 0, sizeof(struct stat));

	ret = fstat(fd, &buffer);
	if (ret < 0) {
		perror("fstat");
		return EXIT_FAILURE;
	}

	return buffer.st_blocks;
}

void print_blocks(int fd) {
	int nr_blocks, i;
	
	nr_blocks = get_nr_blocks(fd);

	if (nr_blocks < 0) {
		fprintf(stderr, "get_nr_blocks failed\n");
		return;
	}

	if (nr_blocks == 0) {
		printf("no allocated blocks\n");
		return;
	} else
		printf("number of allocated blocks [%d]\n", nr_blocks);

	for (i = 0; i < nr_blocks; i++) {
		int phys_block;

		phys_block = get_block(fd, i);
		if (phys_block < 0) {
			fprintf(stderr, "get_block failed\n");
			return;
		}

		if (!phys_block)
			continue;

		printf("(%u, %u) ", i, phys_block);
	}

	putchar('\n');
}


void process_blocks_in_physical_order(int fd) {
	int nr_blocks = get_nr_blocks(fd);
	int block_size;

	if (nr_blocks < 0) {
		fprintf(stderr, "No allocated blocks to process\n");
		return;
	}

	// GET THE FILE SYSTEM BLOCK SIZE
	if (ioctl(fd, FIGETBSZ, &block_size) < 0) {
		perror("ioctl FIGETBSZ");
		return;
	}

	// allocate memory for mappings
	struct BlockMapping * map = malloc(nr_blocks * sizeof(struct BlockMapping));
	if (!map) {
		perror("malloc");
		return;
	}

	int valid_blocks = 0;
	for (int i = 0; i < nr_blocks; i++) {
		int phys_block = get_block(fd, i);
		if (phys_block > 0) {
			map[valid_blocks].logical = i;
			map[valid_blocks].physical = phys_block;
			valid_blocks++;
		}
	}

	// sort the array by physical block number
	qsort(map, valid_blocks, sizeof(struct BlockMapping), compare_blocks);

	printf("Blocks sorted by physical layout: \n");
	
	char * buffer = malloc(block_size);
	if (!buffer) {
		perror("malloc");
		free(map);
		return;
	}

	for (int i = 0; i < valid_blocks; i++) {
		printf("Reading physical block [%d] (logical = %d)...\n", map[i].physical, map[i].logical);

		// calculate the logical offset to read from the file
		off_t offset = (off_t)map[i].logical * block_size;

		ssize_t bytes_read = pread(fd, buffer, block_size, offset);
		if (bytes_read < 0) {
			perror("pread");
			break;
		}
		printf("buffer data when i is =>[%d] === => [%s]\n", i, buffer);
	}

	free(buffer);
	free(map);
}


int main(int argc, char * argv[]) {
	
	int fd;

	if (argc < 2) {
		fprintf(stderr, "%s <filename>\n", argv[0]);
		return EXIT_FAILURE;
	}

	fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		perror("open");
		return EXIT_FAILURE;
	}

	// print_blocks(fd);
	process_blocks_in_physical_order(fd);

	return EXIT_SUCCESS;
}


