#include "linear_sieve.h"

#include <cmath>
#include <cstring>

#include "../eratosthenes/eratosthenes.h"

void LinearSieve(uint32_t n, bool prime[]) {
  std::memset(prime, 1, n >> 1);
  uint32_t bound = sqrt(n);
  Sieve(bound, prime);
  uint32_t primes[UpperBoundOfPi(bound)], number_of_primes = 0;
  for (uint32_t i = 3; i <= bound; i += 2) {
    if (prime[NumberToIndex(i)]) primes[number_of_primes++] = i;
  }
  for (uint32_t i = 3; i <= n / 3; i += 2) {
    for (uint32_t j = 0; j < number_of_primes && primes[j] <= n / i; ++j) {
      prime[NumberToIndex(primes[j] * i)] = false;
      if (i % primes[j] == 0) break;
    }
  }
}

void LinearSieveBit(uint64_t n, uint32_t prime[]) {
  std::memset(prime, 0xFF, Bytes(n));
  uint64_t bound = sqrtl(n);
  SieveBit(bound, prime);
  uint32_t primes[UpperBoundOfPi(bound)], number_of_primes = 0;
  for (uint32_t i = 3, index = 0; i <= bound; i += 2, ++index) {
    if (BitGet(index, prime)) primes[number_of_primes++] = i;
  }
  for (uint64_t i = 3; i <= n / 3; i += 2) {
    for (uint32_t j = 0; j < number_of_primes && primes[j] <= n / i; ++j) {
      BitReset(NumberToBitIndex(primes[j] * i), prime);
      if (i % primes[j] == 0) break;
    }
  }
}
