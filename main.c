#include "memory_manager.h"

int main()
{
  Block *memoryHead = NULL;

  printf("--- INITIALIZING MEMORY POOL ---\n");
  // 1. Pehle 5 blocks banate hain (Sizes: 128, 256, 384, 512, 640 bytes)
  memoryHead = initializeMemoryPool(memoryHead, 5);
  displayMemoryState(memoryHead);

  printf("\n--- TESTING ALLOCATION (my_malloc) ---\n");
  // 2. 200 Bytes allocate karne ki koshish karte hain (Ye Block ID 2 me jana chahiye!)
  Block *allocatedBlock1 = my_malloc(memoryHead, 50);

  displayMemoryState(memoryHead);

  // 3. 500 Bytes allocate karne ki koshish karte hain (Ye Block ID 4 me jana chahiye!)
  Block *allocatedBlock2 = my_malloc(memoryHead, 500);

  // State check karte hain
  displayMemoryState(memoryHead);

  printf("\n--- TESTING DEALLOCATION (my_free) ---\n");
  // 4. Block ID 2 ko wapas free karte hain
  my_free(memoryHead, 2);

  // State check karte hain ki kya Block ID 2 fir se GREEN hua ya nahi
  displayMemoryState(memoryHead);

  return 0;
}