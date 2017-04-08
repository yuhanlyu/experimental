#ifndef LINEAR_SIEVE_H
#define LINEAR_SIEVE_H

#include "../common/common.h"

#include <cstdint>

// This is Pritchard's linear sieve method from the following paper:
// Paul Pritchard
// Linear prime-number sieves: A family tree
// Science of Computer Programming
// Volume 9, Issue 1, August 1987, Pages 17-35
void LinearSieve(uint32_t n, bool prime[]);

void LinearSieveBit(uint64_t n, uint32_t prime[]);

#endif
