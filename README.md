# 🛠️ Custom Memory Allocator in C

A low-level systems programming project that implements a custom memory management system. This project replicates the behavior of standard library functions like `malloc`, `free`, `realloc`, and `calloc` using a fixed-size heap. It serves as a practical demonstration of memory management concepts, fragmentation handling, and allocator design.

---

## ✨ Features

### **Core Allocator Functionality**
Custom implementation of:
* `my_malloc`
* `my_free`
* `my_realloc`
* `my_calloc`
* **Fixed-size heap:** Uses a simulated memory area (fixed-size byte array).
* **First-fit strategy:** Allocation searches for the first available block that fits the requested size.

### **Memory Management Techniques**
* **Block Metadata:** Each memory block contains a header with its size, free/used flag, and pointers.
* **Doubly Linked List:** Manages memory blocks efficiently using next and previous pointers.
* **Block Splitting:** Minimizes internal waste by dividing large blocks during allocation.
* **Block Coalescing:** Merges adjacent free blocks during deallocation to reduce external fragmentation.
* **Alignment Handling:** Ensures memory is correctly aligned for system integrity.

### **Advanced Debugging & Visualization**
* **Heap State Dump:** Detailed view showing all blocks with their size and allocation status.
* **Heap Statistics:** Tracks total heap size, used memory, free memory, the largest free block, and fragmentation percentage.
* **Allocation Tracing:** Real-time logs for monitoring behavior:
  `[TRACE] ALLOC 104 bytes -> 0x1234`
* **Fragmentation Visualization:** A visual representation of the memory layout:
  `[USED:56][FREE:248][USED:304][FREE:64800]`

---

## 📂 Project Structure

```text
custom-memory-allocator/
├── include/
│   ├── allocator.h
│   └── allocator_internal.h
├── src/
│   └── allocator.c
├── examples/
│   └── demo.c
├── tests/
│   └── test_allocator.c
├── Makefile
└── README.md
```
---

## ⚙️ How It Works
Simulation: A fixed-size byte array simulates the heap memory.

Headers: Every block includes metadata (size, status, pointers).

Allocation:

Finds a suitable free block using the first-fit strategy.

Splits the block if the remaining space is large enough to be useful.

Deallocation:

Marks the target block as free.

Immediately merges adjacent free blocks (coalescing) to maintain large free spaces.

Reallocation: * Attempts to expand the current block in-place if possible.

Otherwise, it allocates new memory, copies the existing data, and frees the old block.

---

## 🚀 Build & Run Instructions
### Step 1: Navigate to Project
Open your terminal and enter the project directory:
cd "C:/Users/Aditi/Desktop/C++ project/custom-memory-allocator"

### Step 2: Clean & Compile
make clean
make
This generates the following binaries:
bin/demo
bin/test_allocator

### Step 3: Run Demo

./bin/demo
Output includes: Heap state, allocation behavior, fragmentation statistics, and visual memory layout.

### Step 4: Run Tests

./bin/test_allocator
Expected output: All tests passed!


**Next Step:** Would you like me to help you write the `allocator.c` source code for the `my_malloc` and `my_free` functions?
