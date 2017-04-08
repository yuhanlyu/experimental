#include "eratosthenes.h"

#include <cmath>
#include <cstring>

void Sieve(uint32_t n, bool prime[]) {
  std::memset(prime, 1, n >> 1);
  const uint32_t bound = sqrt(n);
  for (uint32_t i = 3; i <= bound; i += 2) {
    if (prime[NumberToIndex(i)]) {
      for (uint32_t j = i * i; j <= n; j += (i << 1))
        prime[NumberToIndex(j)] = false;
    }
  }
}

void ImprovedSieve(uint32_t n, bool prime[]) {
  std::memset(prime, 1, n >> 1);
  const uint32_t bound = sqrt(n);
  for (uint32_t i = 3; i <= bound; i += 2) {
    if (prime[NumberToIndex(i)]) {
      for (uint32_t k = n / i - (((n / i) & 1) == 0), j = i * k;;
           k -= 2, j -= (i << 1)) {
        if (prime[NumberToIndex(k)]) {
          prime[NumberToIndex(j)] = false;
          if (k == i) break;
        }
      }
    }
  }
}

void SieveBit(uint64_t n, uint32_t prime[]) {
  std::memset(prime, 0xFF, Bytes(n));
  const uint64_t bound = sqrtl(n), max_index = NumberToBitIndex(n);
  for (uint64_t i = 3, index = 0; i <= bound; i += 2, ++index) {
    if (BitGet(index, prime)) {
      for (uint64_t j_index = NumberToBitIndex(i * i); j_index <= max_index;
           j_index += i)
        BitReset(j_index, prime);
    }
  }
}

void ImprovedSieveBit(uint64_t n, uint32_t prime[]) {
  std::memset(prime, 0xFF, Bytes(n));
  const uint64_t bound = sqrtl(n);
  for (uint64_t i = 3, index = 0; i <= bound; i += 2, ++index) {
    if (BitGet(index, prime)) {
      for (uint64_t k = n / i - ((n / i) % 2 == 0),
                    k_index = NumberToBitIndex(k),
                    j_index = NumberToBitIndex(i * k);
           ; j_index -= i, --k_index) {
        if (BitGet(k_index, prime)) {
          BitReset(j_index, prime);
          if (k_index == index) break;
        }
      }
    }
  }
}
