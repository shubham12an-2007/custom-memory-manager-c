#include "memory_manager.h"

Block *initializeMemoryPool(Block *head, int num_blocks)
{
  for (int i = 1; i <= num_blocks; i++)
  {
    Block *newBlock = (Block *)malloc(sizeof(Block));
    newBlock->block_id = i;
    newBlock->size = 128 * i;
    newBlock->is_free = 1;
    newBlock->next = NULL;

    if (head == NULL)
    {
      head = newBlock;
    }
    else
    {
      Block *temp = head;
      while (temp->next != NULL)
      {
        temp = temp->next;
      }
      temp->next = newBlock;
      newBlock->next = NULL;
    }
  }

  return head;
}

void displayMemoryState(Block *head)
{
  printf("\n=== CURRENT SYSTEM MEMORY STATE ===\n");
  Block *temp = head;

  while (temp != NULL)
  {
    printf("Block ID: %d | Size: %zu Bytes | Status: %s\n",
           temp->block_id,
           temp->size,
           temp->is_free ? "FREE 🟢" : "ALLOCATED 🔴");
    temp = temp->next;
  }
  printf("===================================\n");
}

Block *my_malloc(Block *head, size_t requested_size)
{
  Block *temp = head;
  while (temp != NULL)
  {

    if (temp->is_free == 1 && temp->size >= requested_size)
    {
      if (temp->size - requested_size >= 32)
      {
        Block *newBlock = (Block *)malloc(sizeof(Block));
        newBlock->block_id = temp->block_id + 100;
        newBlock->size = temp->size - requested_size;
        newBlock->is_free = 1;
        newBlock->next = temp->next;

        temp->size = requested_size;
        temp->next = newBlock;
        printf("Notice: Block ID %d was split. New free block ID is %d.\n", temp->block_id, newBlock->block_id);
      }

      temp->is_free = 0; // Allocated
      printf("Success: Allocated %zu bytes in Block ID %d\n", requested_size, temp->block_id);
      return temp;
    }

    temp = temp->next;
  }

  printf("Error: No free block of size %zu Bytes found!\n", requested_size);
  return NULL;
}

void my_free(Block *head, int block_id)
{
  Block *temp = head;
  while (temp != NULL)
  {

    if (temp->block_id == block_id)
    {
      temp->is_free = 1;
      printf("Success: Freed Block ID %d\n", block_id);

      coalesceMemoryPool(head);
      return;
    }

    temp = temp->next;
  }

  printf("Error: Block ID %d not found in the memory pool!\n", block_id);
}

void coalesceMemoryPool(Block *head)
{
  Block *temp = head;
  while (temp != NULL && temp->next != NULL)
  {
    if (temp->is_free == 1 && temp->next->is_free == 1)
    {
      Block *blockToDelete = temp->next;

      temp->size = temp->size + blockToDelete->size;

      temp->next = blockToDelete->next;

      free(blockToDelete);

      printf("Notice: Coalesced adjacent free blocks. New size of Block ID %d is %zu.\n", temp->block_id, temp->size);
    }
    else
    {
      temp = temp->next;
    }
  }
}

Block *my_best_fit_malloc(Block *head, size_t requested_size)
{
  Block *temp = head;
  Block *best_block = NULL;

  while (temp != NULL)
  {
    if (temp->is_free == 1 && temp->size >= requested_size)
    {
      if (best_block == NULL || best_block->size > temp->size)
      {
        best_block = temp;
      }
    }
    temp = temp->next;
  }

  if (best_block != NULL)
  {

    if (best_block->size - requested_size >= 32)
    {
      Block *newBlock = (Block *)malloc(sizeof(Block));
      newBlock->block_id = best_block->block_id + 500; // Unique ID shift for best-fit splits
      newBlock->size = best_block->size - requested_size;
      newBlock->is_free = 1;
      newBlock->next = best_block->next;

      best_block->size = requested_size;
      best_block->next = newBlock;
      printf("Notice (Best-Fit): Split Block ID %d. New free block ID is %d.\n", best_block->block_id, newBlock->block_id);
    }

    best_block->is_free = 0;
    printf("Success (Best-Fit): Allocated %zu bytes in Block ID %d\n", requested_size, best_block->block_id);
    return best_block;
  }
  printf("Error (Best-Fit): No suitable free block found for size %zu Bytes!\n", requested_size);
  return NULL;
}

void destroyMemoryPool(Block *head)
{
  Block *current = head;
  Block *nextNode = NULL;

  while (current != NULL)
  {
    nextNode = current->next;

    printf("Cleaning up: Freeing Metadata Block ID %d\n", current->block_id);
    free(current);

    current = nextNode;
  }

  printf("Success: Memory pool completely destroyed and cleared!\n");
}
