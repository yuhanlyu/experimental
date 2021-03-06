#include "segmented_sieve.h"

#include <cstdint>

#include "../eratosthenes/eratosthenes.h"
#include "gtest/gtest.h"

namespace {

constexpr uint32_t size = 1 << 20;

TEST(SieveTest, SegmentedSieve) {
  bool prime1[size / 2];
  bool prime2[size / 2];

  Sieve(size, prime1);
  SegmentedSieve(size, prime2);
  for (uint32_t i = 2; i <= size; ++i) {
    EXPECT_EQ(IsPrime(i, prime1), IsPrime(i, prime2));
  }
}

TEST(SieveTest, SegmentedSieveBitset) {
  bool prime1[size / 2];
  uint32_t prime2[size / 64 + 1];

  Sieve(size, prime1);
  SegmentedSieveBit(size, prime2);
  for (uint32_t i = 2; i <= size; ++i) {
    EXPECT_EQ(IsPrime(i, prime1), IsPrimeBit(i, prime2));
  }
}

}  // namespace
