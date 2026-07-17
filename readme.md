# Custom Memory Manager in C

A lightweight, deterministic memory management system written in C. This project simulates how an Operating System manages memory dynamically using a linked-list memory pool, bypassing standard library overhead for dedicated allocation spaces.

## 🚀 Key Features
- **Deterministic Memory Pool Initialization:** Pre-allocates a continuous sequential pool of memory blocks with distinct sizes.
- **First-Fit Custom Allocation (`my_malloc`):** Searches the list sequentially to find the first free block that satisfies the requested memory constraint.
- **Dynamic Block Splitting:** Mitigates *Internal Fragmentation* by splitting oversized free blocks into an allocated chunk and a new smaller free chunk.
- **Memory Deallocation (`my_free`):** Returns allocated blocks back to a `FREE` status instantaneously via unique block identification.
- **Coalescing (Next Feature):** Merges adjacent free blocks together to combat *External Fragmentation*.

## 📂 Project Structure
- `memory_manager.h`: Data structures (`Block` metadata) and generic function headers.
- `memory_manager.c`: Implementation logic for allocation, splitting, deallocation, and coalescing.
- `main.c`: Test driver bench validating allocation thresholds, splits, and states.
- `Makefile`: Single-command automated compilation utility.

## 🛠️ How to Compile and Run
Simply use the included Makefile automation:
```bash
# Compile the project
make

# Run the test driver
./my_memory_manager