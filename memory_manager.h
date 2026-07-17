#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stdio.h>
#include <stdlib.h>

// Structure of a Block
typedef struct Block
{
  int block_id;       // Unique id of each Block
  size_t size;        // Block size (eg: 128 , 256 , 512)
  int is_free;        // 1 is Block is free , 0 if Block is occupied
  struct Block *next; // Next Block addres
} Block;

// Functions Prototype

// Intialize memory pool
Block *initializeMemoryPool(Block *head, int num_blocks);

// display memory state
void displayMemoryState(Block *head);

// Memory Allocation
Block *my_malloc(Block *head, size_t requested_size);

// Memory deallocate
void my_free(Block *head, int block_id);

// Coalescing Function
void coalesceMemoryPool(Block *head);

#endif