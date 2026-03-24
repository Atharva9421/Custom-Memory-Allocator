#include <stdio.h>
#include <string.h>

#include "allocator.h"
#include "allocator_internal.h"

/* ===== Global heap ===== */

static unsigned char heap[HEAP_SIZE];
static block_header_t *heap_head = NULL;

/* ===== Trace logging ===== */

static void trace_log(const char *action, size_t size, void *old_ptr, void *new_ptr)
{
#if ENABLE_ALLOCATOR_TRACE
    if (old_ptr && new_ptr)
        printf("[TRACE] %s %zu bytes | %p -> %p\n", action, size, old_ptr, new_ptr);
    else if (new_ptr)
        printf("[TRACE] %s %zu bytes -> %p\n", action, size, new_ptr);
    else if (old_ptr)
        printf("[TRACE] %s %p\n", action, old_ptr);
#endif
}

/* ===== Alignment ===== */

static size_t align_size(size_t size)
{
    return (size + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1);
}

/* ===== Allocator initialization ===== */

void allocator_init(void)
{
    heap_head = (block_header_t *)heap;

    heap_head->size = HEAP_SIZE - sizeof(block_header_t);
    heap_head->free = 1;
    heap_head->next = NULL;
    heap_head->prev = NULL;
}

/* ===== Find free block (First Fit) ===== */

static block_header_t *find_free_block(size_t size)
{
    block_header_t *current = heap_head;

    while (current != NULL)
    {
        if (current->free && current->size >= size)
            return current;

        current = current->next;
    }

    return NULL;
}

/* ===== Split block ===== */

static void split_block(block_header_t *block, size_t size)
{
    unsigned char *block_start = (unsigned char *)block;

    block_header_t *new_block =
        (block_header_t *)(block_start + sizeof(block_header_t) + size);

    new_block->size = block->size - size - sizeof(block_header_t);
    new_block->free = 1;
    new_block->next = block->next;
    new_block->prev = block;

    if (new_block->next)
        new_block->next->prev = new_block;

    block->size = size;
    block->next = new_block;
}

/* ===== malloc ===== */

void *my_malloc(size_t size)
{
    if (size == 0)
        return NULL;

    if (!heap_head)
        allocator_init();

    size = align_size(size);

    block_header_t *block = find_free_block(size);

    if (!block)
        return NULL;

    if (block->size >= size + sizeof(block_header_t) + ALIGNMENT)
        split_block(block, size);

    block->free = 0;

    void *ptr = (void *)(block + 1);

    trace_log("ALLOC", size, NULL, ptr);

    return ptr;
}

/* ===== Convert pointer to block ===== */

static block_header_t *get_block(void *ptr)
{
    if (!ptr)
        return NULL;

    return ((block_header_t *)ptr) - 1;
}

/* ===== Coalesce blocks ===== */

static void coalesce(block_header_t *block)
{
    if (block->next && block->next->free)
    {
        block->size += sizeof(block_header_t) + block->next->size;
        block->next = block->next->next;

        if (block->next)
            block->next->prev = block;
    }

    if (block->prev && block->prev->free)
    {
        block->prev->size += sizeof(block_header_t) + block->size;
        block->prev->next = block->next;

        if (block->next)
            block->next->prev = block->prev;
    }
}

/* ===== free ===== */

void my_free(void *ptr)
{
    block_header_t *block = get_block(ptr);

    if (!block)
        return;

    block->free = 1;

    trace_log("FREE", 0, ptr, NULL);

    coalesce(block);
}

/* ===== realloc ===== */

void *my_realloc(void *ptr, size_t new_size)
{
    if (!ptr)
        return my_malloc(new_size);

    if (new_size == 0)
    {
        my_free(ptr);
        return NULL;
    }

    block_header_t *block = get_block(ptr);

    new_size = align_size(new_size);

    if (block->size >= new_size)
        return ptr;

    void *new_ptr = my_malloc(new_size);

    if (!new_ptr)
        return NULL;

    size_t copy_size = block->size < new_size ? block->size : new_size;

    memcpy(new_ptr, ptr, copy_size);

    trace_log("REALLOC", new_size, ptr, new_ptr);

    my_free(ptr);

    return new_ptr;
}

/* ===== calloc ===== */

void *my_calloc(size_t num, size_t size)
{
    size_t total = num * size;

    void *ptr = my_malloc(total);

    if (ptr)
        memset(ptr, 0, total);

    trace_log("CALLOC", total, NULL, ptr);

    return ptr;
}

/* ===== Heap dump ===== */

void allocator_dump_heap(void)
{
    block_header_t *current = heap_head;
    int i = 0;

    printf("\n===== HEAP STATE =====\n");

    while (current)
    {
        printf("Block %d | size=%zu | free=%d\n",
               i, current->size, current->free);

        current = current->next;
        i++;
    }

    printf("======================\n");
}

/* ===== Heap statistics ===== */

size_t allocator_get_total_free(void)
{
    block_header_t *current = heap_head;
    size_t total = 0;

    while (current)
    {
        if (current->free)
            total += current->size;

        current = current->next;
    }

    return total;
}

size_t allocator_get_total_used(void)
{
    block_header_t *current = heap_head;
    size_t total = 0;

    while (current)
    {
        if (!current->free)
            total += current->size;

        current = current->next;
    }

    return total;
}

size_t allocator_get_largest_free_block(void)
{
    block_header_t *current = heap_head;
    size_t largest = 0;

    while (current)
    {
        if (current->free && current->size > largest)
            largest = current->size;

        current = current->next;
    }

    return largest;
}

double allocator_get_fragmentation_percent(void)
{
    size_t total_free = allocator_get_total_free();
    size_t largest = allocator_get_largest_free_block();

    if (total_free == 0)
        return 0.0;

    return 100.0 * (1.0 - ((double)largest / (double)total_free));
}

/* ===== Print statistics ===== */

void allocator_print_stats(void)
{
    printf("\n===== HEAP STATS =====\n");

    printf("Total heap size      : %zu bytes\n", (size_t)HEAP_SIZE);
    printf("Used memory          : %zu bytes\n", allocator_get_total_used());
    printf("Free memory          : %zu bytes\n", allocator_get_total_free());
    printf("Largest free block   : %zu bytes\n", allocator_get_largest_free_block());

    printf("Fragmentation        : %.2f%%\n",
           allocator_get_fragmentation_percent());

    printf("======================\n");
}

/* ===== Fragmentation visualization ===== */

void allocator_visualize_heap(void)
{
    block_header_t *current = heap_head;

    printf("\n===== FRAGMENTATION MAP =====\n");

    while (current)
    {
        if (current->free)
            printf("[FREE:%zu]", current->size);
        else
            printf("[USED:%zu]", current->size);

        current = current->next;
    }

    printf("\n=============================\n");
}