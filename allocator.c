#include "allocator.h"
#include <stdlib.h>
#include <string.h>

Allocator *allocator_init() {
	Allocator *alloc = malloc(sizeof(Allocator));
	alloc->list.size = 0;
	alloc->list.buffer = malloc(sizeof(long) * 16);
	alloc->list.buffer_size = 16;
	return alloc;
}

void allocator_grow(Allocator *alloc) {
	size_t new_size = alloc->list.buffer_size * 2;
	alloc->list.buffer = realloc(alloc->list.buffer, new_size);
	alloc->list.buffer_size = new_size;
}

void allocator_add_pointer(Allocator *alloc, long ptr) {
	if (alloc->list.size >= alloc->list.buffer_size)
		allocator_grow(alloc);
	alloc->list.buffer[alloc->list.size] = ptr;
	alloc->list.size++;
}

void *allocator_alloc(Allocator *alloc, size_t size) {
	void *ptr = malloc(size);
	allocator_add_pointer(alloc, (long) ptr);
	return ptr;
}

void allocator_free(Allocator *alloc) {
	for (int i = 0; i != alloc->list.size; i++) {
		free((void*) alloc->list.buffer[i]);
	}
	memset(alloc->list.buffer, 0, alloc->list.size * sizeof(long));
	alloc->list.size = 0;
}

void allocator_destroy(Allocator *alloc) {
	allocator_free(alloc);
	free(alloc->list.buffer);
	free(alloc);
}
