#ifndef SEGMENTED_SIEVE_H
#define SEGMENTED_SIEVE_H

#include <cstdint>

#include "../common/common.h"

// Segmented sieve method.
void SegmentedSieve(uint32_t n, bool prime[]);

void SegmentedSieveBit(uint64_t n, uint32_t prime[]);

#endif
