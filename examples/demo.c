#include <stdio.h>
#include "allocator.h"

int main(void)
{
    allocator_init();

    printf("Initial heap\n");
    allocator_dump_heap();
    allocator_print_stats();
    allocator_visualize_heap();

    printf("\n--- Allocating A (100 bytes) ---\n");
    void *a = my_malloc(100);

    allocator_dump_heap();
    allocator_print_stats();
    allocator_visualize_heap();

    printf("\n--- Allocating B (200 bytes) ---\n");
    void *b = my_malloc(200);

    allocator_dump_heap();
    allocator_print_stats();
    allocator_visualize_heap();

    printf("\n--- Freeing A ---\n");
    my_free(a);

    allocator_dump_heap();
    allocator_print_stats();
    allocator_visualize_heap();

    printf("\n--- Allocating C (50 bytes) ---\n");
    void *c = my_malloc(50);
    (void)c; /* avoid unused variable warning */

    allocator_dump_heap();
    allocator_print_stats();
    allocator_visualize_heap();

    printf("\n--- Reallocating B to 300 bytes ---\n");
    b = my_realloc(b, 300);

    allocator_dump_heap();
    allocator_print_stats();
    allocator_visualize_heap();

    printf("\nDemo complete.\n");

    return 0;
}