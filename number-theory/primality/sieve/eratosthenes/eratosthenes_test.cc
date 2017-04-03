#include "eratosthenes.h"

#include <cstdint>

#include "gtest/gtest.h"

namespace {

constexpr uint32_t size = 1 << 20;

TEST(SieveTest, ImprovedSieve) {
  bool prime1[size / 2];
  bool prime2[size / 2];

  Sieve(size, prime1);
  ImprovedSieve(size, prime2);
  for (uint32_t i = 2; i <= size; ++i) {
    EXPECT_EQ(IsPrime(i, prime1), IsPrime(i, prime2));
  }
}

TEST(SieveTest, SieveBitset) {
  bool prime1[size / 2];
  uint32_t prime2[size / 64 + 1];

  Sieve(size, prime1);
  SieveBit(size, prime2);
  for (uint32_t i = 2; i <= size; ++i) {
    EXPECT_EQ(IsPrime(i, prime1), IsPrimeBit(i, prime2));
  }
}

TEST(SieveTest, ImprovedSieveBitset) {
  bool prime1[size / 2];
  uint32_t prime2[size / 64 + 1];

  Sieve(size, prime1);
  ImprovedSieveBit(size, prime2);
  for (uint32_t i = 2; i <= size; ++i) {
    EXPECT_EQ(IsPrime(i, prime1), IsPrimeBit(i, prime2));
  }
}

}  // namespace
