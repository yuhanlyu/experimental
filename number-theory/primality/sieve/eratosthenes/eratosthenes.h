#ifndef SIEVE_H
#define SIEVE_H

#include <cstdint>

// After use Sieve or ImprovedSieve to build a prime table, this function tests
// whether n is a prime or not.
bool IsPrime(uint32_t n, const bool prime[]);

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

// After use SieveBit or ImprovedSieveBit to build a prime table, this function
// tests whether n is a prime or not.
bool IsPrimeBit(uint64_t n, const uint32_t bitset[]);

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
