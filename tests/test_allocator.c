#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "allocator.h"

static void test_basic_malloc(void)
{
    allocator_init();
    void *p = my_malloc(100);
    assert(p != NULL);
}

static void test_multiple_malloc(void)
{
    allocator_init();

    void *a = my_malloc(64);
    void *b = my_malloc(128);
    void *c = my_malloc(256);

    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);
}

static void test_free_reuse(void)
{
    allocator_init();

    void *a = my_malloc(128);
    assert(a != NULL);

    my_free(a);

    void *b = my_malloc(128);
    assert(b != NULL);
}

static void test_realloc(void)
{
    allocator_init();

    char *p = (char *)my_malloc(10);
    assert(p != NULL);

    strcpy(p, "hello");
    p = (char *)my_realloc(p, 20);

    assert(p != NULL);
    assert(strcmp(p, "hello") == 0);
}

static void test_calloc(void)
{
    allocator_init();

    int *arr = (int *)my_calloc(4, sizeof(int));
    assert(arr != NULL);

    for (int i = 0; i < 4; i++)
    {
        assert(arr[i] == 0);
    }
}

int main(void)
{
    test_basic_malloc();
    test_multiple_malloc();
    test_free_reuse();
    test_realloc();
    test_calloc();

    printf("All tests passed!\n");
    return 0;
}