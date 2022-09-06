#include <stdio.h>
#include "allocator.h"

int main(void) {
	Allocator *alloc = allocator_init();
	void *ptr  = allocator_alloc(alloc, 16);
	void *ptr2 = allocator_alloc(alloc, 48);
	allocator_freeAll(alloc);
	ptr  = allocator_alloc(alloc, 16);
	ptr2 = allocator_alloc(alloc, 48);
	allocator_destroy(alloc);
}
