#ifndef SIEVE_H
#define SIEVE_H

#include "../common/common.h"

#include <cstdint>

// Sieve of Eratosthenes.
// Example usage:
// constexpr int32_t size = 1 << 20;
// bool prime[size / 2];
// Sieve(size, prime);
// IsPrime(n, prime);
void Sieve(uint32_t n, bool prime[]);

// This improvement is from Chapter 13 in Algorithms Unplugged.
// Example usage:
// constexpr int32_t size = 1 << 20;
// bool prime[size / 2];
// ImprovedSieve(size, prime);
// IsPrime(n, prime);
void ImprovedSieve(uint32_t n, bool prime[]);

// Use bitset to reduce the memory usege of sieve of Eratosthenes.
// Example usage:
// constexpr int32_t size = 1 << 20;
// uint32_t prime[size / 64 + 1];
// SieveBit(size, prime);
// IsPrimeBit(n, prime);
void SieveBit(uint64_t n, uint32_t prime[]);

// Use bitset to reduce the memory usege of improved sieve of Eratosthenes.
// Example usage:
// constexpr int32_t size = 1 << 20;
// uint32_t prime[size / 64 + 1];
// ImprovedSieveBit(size, prime);
// IsPrimeBit(n, prime);
void ImprovedSieveBit(uint64_t n, uint32_t prime[]);

#endif
