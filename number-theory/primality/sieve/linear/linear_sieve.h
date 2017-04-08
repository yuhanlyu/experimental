#ifndef LINEAR_SIEVE_H
#define LINEAR_SIEVE_H

#include "../common/common.h"

#include <cstdint>

// Pritchard's linear sieve method.
void LinearSieve(uint32_t n, bool prime[]);

void LinearSieveBit(uint64_t n, uint32_t prime[]);

#endif
