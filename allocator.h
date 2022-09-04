#ifndef allocator_h_INCLUDED
#define allocator_h_INCLUDED
#include <sys/types.h>

typedef struct Allocator {
	struct AllocList {
		size_t size;
		long *buffer;
		size_t buffer_size;
	} list;
} Allocator;

Allocator *allocator_init();

void *allocator_alloc(Allocator *alloc, size_t size);

void allocator_free(Allocator *alloc);

void allocator_destroy(Allocator *alloc);

#endif // allocator_h_INCLUDED
