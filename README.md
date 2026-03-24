##Custom Memory Allocator in C

A low-level systems programming project that implements a custom memory allocator in C, replicating the behavior of malloc, free, realloc, and calloc using a fixed-size heap.

This project demonstrates core concepts of memory management, fragmentation handling, and allocator design, along with debugging and visualization tools.

#Features

Core Allocator Functionality
Custom implementation of:
my_malloc
my_free
my_realloc
my_calloc
Fixed-size heap (simulated memory)
First-fit allocation strategy

Memory Management Techniques
Block metadata using headers
Doubly linked list of memory blocks
Block splitting (to minimize waste)
Block coalescing (to reduce fragmentation)
Memory alignment handling

Advanced Debugging Features
Heap State Dump
Shows all blocks with size and allocation status
Heap Statistics
Total heap size
Used memory
Free memory
Largest free block
Fragmentation %

Allocation Tracing

[TRACE] ALLOC 104 bytes -> 0x1234
[TRACE] FREE 0x1234
[TRACE] REALLOC 0x1234 -> 0x5678

Fragmentation Visualization

[USED:56][FREE:248][USED:304][FREE:64800]

#Project Structure
custom-memory-allocator/
│── include/
│ ├── allocator.h
│ ├── allocator_internal.h
│
│── src/
│ ├── allocator.c
│
│── examples/
│ ├── demo.c
│
│── tests/
│ ├── test_allocator.c
│
│── Makefile
│── README.md

#How It Works
A fixed-size byte array simulates heap memory.
Each memory block contains a header with:
size
free/used flag
next/previous pointers
Allocation:
Finds a suitable free block (first-fit)
Splits block if necessary
Deallocation:
Marks block free
Merges adjacent free blocks (coalescing)
Reallocation:
Expands in-place if possible
Otherwise allocates new memory and copies data

#Build & Run Instructions

Step 1: Open Terminal

Navigate to the project directory:

cd "C:/Users/Aditi/Desktop/C++ project/custom-memory-allocator"

Step 2: Clean Previous Build
make clean

Step 3: Compile the Project
make

This generates:

bin/demo
bin/test_allocator
Step 4: Run Demo Program
./bin/demo
Output includes:
Heap state
Allocation behavior
Fragmentation statistics
Visual memory layout
Step 5: Run Tests
./bin/test_allocator

Expected output:

All tests passed!
