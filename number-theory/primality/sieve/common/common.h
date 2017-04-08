#ifndef SIEVE_COMMON_H
#define SIEVE_COMMON_H

#include "bit_set.h"

#include <cstdint>

// Number of bytes having at least n + 1 bits.
inline int64_t Bytes(uint64_t n) { return (n >> 4) + (((n >> 1) & 7) != 0); }

// Mapping from the number to the index in the byte array.
inline int32_t NumberToIndex(uint32_t n) { return (n - 2) >> 1; }

// Mapping from the number to the bit index.
inline int64_t NumberToBitIndex(uint64_t n) { return (n - 2) >> 1; }

// After use Sieve to build a prime table, this function tests whether n is a
// prime or not.
inline bool IsPrime(uint32_t n, const bool prime[]) {
  return (n & 1) == 0 ? (n == 2) : prime[NumberToIndex(n)];
}

// After use SieveBit to build a prime table, this function tests whether n is a
// prime or not.
inline bool IsPrimeBit(uint64_t n, const uint32_t bitset[]) {
  return (n & 1) == 0 ? (n == 2) : (BitGet(NumberToBitIndex(n), bitset) != 0);
}

#endif
