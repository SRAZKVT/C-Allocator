#include "allocator.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Allocator *allocator_init() {
	Allocator *alloc = malloc(sizeof(Allocator));
	if (!alloc) {
		fprintf(stderr, "Unable to initialise allocator\n");
		return NULL;
	}
	alloc->list.size = 0;
	alloc->list.buffer = calloc(16, sizeof(void *));
	if (!alloc->list.buffer) {
		fprintf(stderr, "Unable to initialise internal buffer for allocator");
		free(alloc);
		return NULL;
	}
	alloc->list.buffer_size = 16;
	return alloc;
}

static void allocator_grow(Allocator *alloc) {
	size_t new_size = alloc->list.buffer_size * 2;
	void* ptr = realloc(alloc->list.buffer, new_size);
	// If growing internal buffer isn't succesful, panic and abort
	if (!ptr) assert(0 && "Unable to grow allocator");
	alloc->list.buffer = ptr;
	alloc->list.buffer_size = new_size;
}

static void allocator_add_pointer(Allocator *alloc, void *ptr) {
	if (alloc->list.size >= alloc->list.buffer_size)
		allocator_grow(alloc);
	for (int i = 0; i != alloc->list.size; i++) {
		if (alloc->list.buffer[i] == NULL) {
			alloc->list.buffer[i] = ptr;
			ptr = NULL;
			break;
		}
	}
	if (ptr != NULL) {
		alloc->list.buffer[alloc->list.size] = ptr;
		alloc->list.size++;
	}
}

void *allocator_alloc(Allocator *alloc, size_t size) {
	void *ptr = malloc(size);
	if (ptr) allocator_add_pointer(alloc, ptr);
	else fprintf(stderr, "Failed to allocate buffer of size %zu\n", size);
	return ptr;
}

void allocator_free(Allocator *alloc, void *ptr) {
	for (int i = 0; i != alloc->list.size; i++)
		if (alloc->list.buffer[i] == ptr) {
				free(ptr);
				alloc->list.buffer[i] = NULL;
		}
}

void allocator_freeAll(Allocator *alloc) {
	for (int i = 0; i != alloc->list.size; i++)
		if (alloc->list.buffer[i] != NULL)
			free(alloc->list.buffer[i]);
	memset(alloc->list.buffer, 0, alloc->list.size * sizeof(long));
	alloc->list.size = 0;
}

void allocator_destroy(Allocator *alloc) {
	allocator_freeAll(alloc);
	free(alloc->list.buffer);
	free(alloc);
}
