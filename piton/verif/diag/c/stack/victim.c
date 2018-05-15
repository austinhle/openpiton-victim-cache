#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  // Create array larger than the primary L1.5 cache.
  int magnifyFactor = 100;
  int size = 3000;
  uint32_t* arr = (uint32_t*) malloc(size * sizeof(uint32_t));

  // Fill the array.
  for (int i = 0; i < size; i++) {
    arr[i] = i;
  }

  // Piece out the appropriate sizes for the tag/index/offset.
  uint32_t tag = (uint32_t) (0xFFFFF800 & (unsigned int) arr); // 21 bits
  uint32_t idx = (uint32_t) (0x000007F0 & (unsigned int) arr); // 7  bits
  uint32_t off = (uint32_t) (0x0000000F & (unsigned int) arr); // 4  bits
  uint32_t inc = 0x00000800;

  // Fill in the cache with correct accesses.
  uint32_t tag0 = tag;
  uint32_t tag1 = tag0 + inc;
  uint32_t tag2 = tag1 + inc;
  uint32_t tag3 = tag2 + inc;
  uint32_t tag4 = tag3 + inc;

  // Try to access the fifth line;
  for (int i = 0; i < magnifyFactor; i++) {
    uint32_t elem0 = *(uint32_t*)(tag0|idx|off);
    uint32_t elem1 = *(uint32_t*)(tag1|idx|off);
    uint32_t elem2 = *(uint32_t*)(tag2|idx|off);
    uint32_t elem3 = *(uint32_t*)(tag3|idx|off);
    uint32_t elem4 = *(uint32_t*)(tag4|idx|off); // Victim cache has line, L1.5 doesn't
  }

  free(arr);

  return 0;
}
