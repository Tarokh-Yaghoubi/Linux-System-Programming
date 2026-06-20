
#define __GNU_SOURCE

#include "../headers.h"
#include <fcntl.h>

void * 
my_realloc(void * addr, size_t len) {
	size_t old_size = look_up_mapping_size(addr);
	void * p;

	p = mremap(addr, old_size, len, MREMAP_MAYMOVE);
	if (p == MAP_FAILED) return NULL;

	return p;
}

