#ifndef BIT_SET_H
#define BIT_SET_H

#include <cstdint>

// Get the x-th bit in the bitset.
inline bool BitGet(uint64_t x, const uint32_t bitset[]) {
  return (bitset[x >> 5] & (1 << (x & 31))) != 0;
}

// Clear the x-th bit in the bitset.
inline void BitReset(uint64_t x, uint32_t bitset[]) {
  bitset[x >> 5] &= ~(1 << (x & 31));
}

#endif
