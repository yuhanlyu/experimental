#include "segmented_sieve.h"

#include <cmath>
#include <cstring>

#include "../eratosthenes/eratosthenes.h"

// L1 Data Cache size.
constexpr uint32_t L1DCacheSize = 1 << 16;

void SegmentedSieve(uint32_t n, bool prime[]) {
  std::memset(prime, 1, n >> 1);
  if (n <= 8) return;
  uint32_t bound = sqrt(n);
  Sieve(bound, prime);
  uint32_t primes[UpperBoundOfPi(bound)], number_of_primes = 0;
  for (uint32_t i = 3; i <= bound; i += 2) {
    if (prime[NumberToIndex(i)]) {
      primes[number_of_primes++] = i;
    }
  }
  uint32_t next[number_of_primes], s = 0, segment_size = L1DCacheSize;
  for (uint32_t low = bound + 1,
                high = low + segment_size > n ? n : low + segment_size;
       low <= n; low += segment_size) {
    for (uint32_t h = 0; h < number_of_primes; ++h) {
      uint32_t i = primes[h], j;
      if (i * i > high) break;
      if (h < s) {
        j = next[h];
      } else {
        j = ((low + (i - 1)) / i) * i;
        j += i * ((j & 1) == 0);
        ++s;
      }
      for (; j <= high; j += (i << 1)) prime[NumberToIndex(j)] = false;
      next[h] = j;
    }
    high = (high + segment_size > n) ? n : high + segment_size;
  }
}

void SegmentedSieveBit(uint64_t n, uint32_t prime[]) {
  std::memset(prime, 0xFF, Bytes(n));
  if (n <= 8) return;
  uint64_t bound = sqrtl(n);
  SieveBit(bound, prime);
  uint32_t primes[UpperBoundOfPi(bound)], number_of_primes = 0;
  for (uint32_t i = 3, index = 0; i <= bound; i += 2, ++index) {
    if (BitGet(index, prime)) primes[number_of_primes++] = i;
  }
  uint64_t next[number_of_primes], s = 0;
  uint64_t segment_size = L1DCacheSize << 7;
  for (uint64_t low = bound + 1,
                high = low + segment_size > n ? n : low + segment_size;
       low <= n; low += segment_size) {
    uint64_t high_index = NumberToBitIndex(high);
    for (uint64_t h = 0; h < number_of_primes; ++h) {
      uint64_t i = primes[h], j_index;
      if (i * i > high) break;
      if (h < s) {
        j_index = next[h];
      } else {
        uint64_t j = ((low + (i - 1)) / i) * i;
        j += i * ((j & 1) == 0);
        j_index = NumberToBitIndex(j);
        ++s;
      }
      for (; j_index <= high_index; j_index += i) BitReset(j_index, prime);
      next[h] = j_index;
    }
    high = (high + segment_size > n) ? n : high + segment_size;
  }
}
