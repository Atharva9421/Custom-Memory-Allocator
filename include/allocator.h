#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>

/* ===== Core allocator API ===== */

void allocator_init(void);

void *my_malloc(size_t size);
void my_free(void *ptr);
void *my_realloc(void *ptr, size_t new_size);
void *my_calloc(size_t num, size_t size);

/* ===== Debug utilities ===== */

void allocator_dump_heap(void);

/* ===== Heap statistics ===== */

void allocator_print_stats(void);

size_t allocator_get_total_free(void);
size_t allocator_get_total_used(void);
size_t allocator_get_largest_free_block(void);
double allocator_get_fragmentation_percent(void);

/* ===== Visualization ===== */

void allocator_visualize_heap(void);

#endif