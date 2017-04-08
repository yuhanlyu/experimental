#ifndef SEGMENTED_SIEVE_H
#define SEGMENTED_SIEVE_H

#include <cstdint>

#include "../common/common.h"

// Segmented sieve method from the following paper:
// Carter Bays and Richard H. Hudson
// The segmented sieve of eratosthenes and primes in
// arithmetic progressions to 10^12
// BIT Numerical Mathematics June 1977, Volume 17, Issue 2, pp 121 - 127
void SegmentedSieve(uint32_t n, bool prime[]);

void SegmentedSieveBit(uint64_t n, uint32_t prime[]);

#endif
