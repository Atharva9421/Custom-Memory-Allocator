#ifndef ALLOCATOR_INTERNAL_H
#define ALLOCATOR_INTERNAL_H

#include <stddef.h>

/* ===== Heap configuration ===== */

/* Total simulated heap size (64 KB) */
#define HEAP_SIZE 65536

/* Memory alignment (8 bytes typical for 64-bit systems) */
#define ALIGNMENT 8

/* ===== Debug / tracing options ===== */

/*
   Set to 1 to enable allocation tracing logs.
   Set to 0 to disable logs.
*/
#define ENABLE_ALLOCATOR_TRACE 1

/* ===== Internal block metadata ===== */

typedef struct block_header
{
    size_t size;               /* Size of memory block */
    int free;                  /* 1 = free, 0 = allocated */
    struct block_header *next; /* Next block in linked list */
    struct block_header *prev; /* Previous block */
} block_header_t;

#endif