#include "memory_manager.h"

int main()
{
  Block *memoryHead = NULL;

  printf("--- INITIALIZING MEMORY POOL ---\n");

  memoryHead = initializeMemoryPool(memoryHead, 5);
  displayMemoryState(memoryHead);

  printf("\n--- TESTING ALLOCATION (my_malloc) ---\n");

  Block *allocatedBlock1 = my_malloc(memoryHead, 50);

  displayMemoryState(memoryHead);

  Block *allocatedBlock2 = my_malloc(memoryHead, 40);
  displayMemoryState(memoryHead);

  printf("\n--- TESTING DEALLOCATION (my_free) ---\n");
  my_free(memoryHead, 1);

  displayMemoryState(memoryHead);

  return 0;
}