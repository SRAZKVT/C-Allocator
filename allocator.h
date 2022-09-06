#ifndef allocator_h_INCLUDED
#define allocator_h_INCLUDED
#include <sys/types.h>

typedef struct Allocator {
	struct AllocList {
		size_t size;
		void **buffer;
		size_t buffer_size;
	} list;
} Allocator;

/**
 * Instanciates a new allocator
 * 
 * @return pointer to the newly instanciated allocator
 */
Allocator *allocator_init();

/**
 * Uses an instanciated allocator to allocate memory.
 * Will also add the pointer returned by malloc to the allocator's internal buffer
 * 
 * @param alloc the instanciated allocator which should wrap the malloc call
 * @param size the size of the buffer requested
 * 
 * @return pointer to the requested buffer
 */
void *allocator_alloc(Allocator *alloc, size_t size);

/**
 * Free all pointers stored within the allocator, essentially resetting it. Allows to use an allocator in a loop, and have all memory needed within the loop freed by this function. Is implicitely called by allocator_destroy, so call this function before isn't necessary.
 * 
 * @param alloc the instanciated allocator to reset
 */
void allocator_freeAll(Allocator *alloc);

/**
 * Frees all pointers stored within the allocator, and destroy the allocator itself.
 * 
 * @param alloc the instanciated allocator to destroy
 */
void allocator_destroy(Allocator *alloc);

#endif // allocator_h_INCLUDED
