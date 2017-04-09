#ifndef LINEAR_SIEVE_H
#define LINEAR_SIEVE_H

#include "../common/common.h"

#include <cstdint>

// Pritchard's linear sieve method.
// Example usage:
// constexpr int32_t size = 1 << 20;
// bool prime[size / 2];
// LinearSieve(size, prime);
// IsPrime(n, prime);
void LinearSieve(uint32_t n, bool prime[]);

// Example usage:
// constexpr int32_t size = 1 << 20;
// uint32_t prime[size / 64 + 1];
// LinearSieveBit(size, prime);
// IsPrimeBit(n, prime);
void LinearSieveBit(uint64_t n, uint32_t prime[]);

#endif
