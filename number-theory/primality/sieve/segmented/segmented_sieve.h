#ifndef SEGMENTED_SIEVE_H
#define SEGMENTED_SIEVE_H

#include <cstdint>

#include "../common/common.h"

// Segmented sieve method.
// Example usage:
// constexpr int32_t size = 1 << 20;
// bool prime[size / 2];
// SegmentedSieve(size, prime);
// IsPrime(n, prime);
void SegmentedSieve(uint32_t n, bool prime[]);

// Example usage:
// constexpr int32_t size = 1 << 20;
// uint32_t prime[size / 64 + 1];
// SegmentedSieveBit(size, prime);
// IsPrimeBit(n, prime);
void SegmentedSieveBit(uint64_t n, uint32_t prime[]);

#endif
