

#include "../headers.h"

#include <sys/user.h>

int
main(void) {
	int page_size = getpagesize(); // this is what linux defines.

	page_size = sysconf(_SC_PAGESIZE); // a more portable way to get pagesize [safest way ].
	printf("page size => %d\n", page_size);

	// a third way to retrieve the page size:
	page_size = PAGE_SIZE;	// this macro is already set to the pagesize statically
	printf("PAGE_SIZE MACRO <sys/user.h> ====> [%d]\n", page_size);

	return 0;

}
