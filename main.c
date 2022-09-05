#include <stdio.h>
#include "allocator.h"

int main(void) {
	Allocator *alloc = allocator_init();
	void *ptr = allocator_alloc(alloc, 16);
	allocator_freeAll(alloc);
	ptr = allocator_alloc(alloc, 16);
	allocator_destroy(alloc);
}
