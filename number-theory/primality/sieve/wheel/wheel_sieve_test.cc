#include "wheel_sieve.h"

#include <cstdint>

#include "../eratosthenes/eratosthenes.h"
#include "gtest/gtest.h"

namespace {

constexpr uint32_t size = 1 << 20;

TEST(SieveTest, WheelSieve6) {
  bool prime1[size / 2];
  bool prime2[size / 2];

  Sieve(size, prime1);
  WheelSieve6::WheelSieve(size, prime2);
  for (uint32_t i = 2; i <= size; ++i) {
    EXPECT_EQ(IsPrime(i, prime1), WheelSieve6::IsPrime(i, prime2));
  }
}

TEST(SieveTest, SegmentedWheelSieve6) {
  bool prime1[size / 2];
  bool prime2[size / 2];

  Sieve(size, prime1);
  WheelSieve6::SegmentedWheelSieve(size, prime2);
  for (uint32_t i = 2; i <= size; ++i) {
    EXPECT_EQ(IsPrime(i, prime1), WheelSieve6::IsPrime(i, prime2));
  }
}

TEST(SieveTest, WheelSieve6Bit) {
  bool prime1[size / 2];
  uint32_t prime2[size / 64 + 1];

  Sieve(size, prime1);
  WheelSieve6::WheelSieveBit(size, prime2);
  for (uint32_t i = 2; i <= size; ++i) {
    EXPECT_EQ(IsPrime(i, prime1), WheelSieve6::IsPrimeBit(i, prime2));
  }
}

TEST(SieveTest, SegmentedWheelSieve6Bit) {
  bool prime1[size / 2];
  uint32_t prime2[size / 64 + 1];

  Sieve(size, prime1);
  WheelSieve6::SegmentedWheelSieveBit(size, prime2);
  for (uint32_t i = 2; i <= size; ++i) {
    EXPECT_EQ(IsPrime(i, prime1), WheelSieve6::IsPrimeBit(i, prime2));
  }
}

TEST(SieveTest, WheelSieve30) {
  bool prime1[size / 2];
  bool prime2[size / 2];

  Sieve(size, prime1);
  WheelSieve30::WheelSieve(size, prime2);
  for (uint32_t i = 2; i <= size; ++i) {
    EXPECT_EQ(IsPrime(i, prime1), WheelSieve30::IsPrime(i, prime2));
  }
}

TEST(SieveTest, SegmentedWheelSieve30) {
  bool prime1[size / 2];
  bool prime2[size / 2];

  Sieve(size, prime1);
  WheelSieve30::SegmentedWheelSieve(size, prime2);
  for (uint32_t i = 2; i <= size; ++i) {
    EXPECT_EQ(IsPrime(i, prime1), WheelSieve30::IsPrime(i, prime2));
  }
}

TEST(SieveTest, WheelSieve30Bit) {
  bool prime1[size / 2];
  uint32_t prime2[size / 64 + 1];

  Sieve(size, prime1);
  WheelSieve30::WheelSieveBit(size, prime2);
  for (uint32_t i = 2; i <= size; ++i) {
    EXPECT_EQ(IsPrime(i, prime1), WheelSieve30::IsPrimeBit(i, prime2));
  }
}

TEST(SieveTest, SegmentedWheelSieve30Bit) {
  bool prime1[size / 2];
  uint32_t prime2[size / 64 + 1];

  Sieve(size, prime1);
  WheelSieve30::SegmentedWheelSieveBit(size, prime2);
  for (uint32_t i = 2; i <= size; ++i) {
    EXPECT_EQ(IsPrime(i, prime1), WheelSieve30::IsPrimeBit(i, prime2));
  }
}

TEST(SieveTest, WheelSieve210) {
  bool prime1[size / 2];
  bool prime2[size / 2];

  Sieve(size, prime1);
  WheelSieve210::WheelSieve(size, prime2);
  for (uint32_t i = 2; i <= size; ++i) {
    EXPECT_EQ(IsPrime(i, prime1), WheelSieve210::IsPrime(i, prime2));
  }
}

TEST(SieveTest, SegmentedWheelSieve210) {
  bool prime1[size / 2];
  bool prime2[size / 2];

  Sieve(size, prime1);
  WheelSieve210::SegmentedWheelSieve(size, prime2);
  for (uint32_t i = 2; i <= size; ++i) {
    EXPECT_EQ(IsPrime(i, prime1), WheelSieve210::IsPrime(i, prime2));
  }
}

TEST(SieveTest, WheelSieve210Bit) {
  bool prime1[size / 2];
  uint32_t prime2[size / 64 + 1];

  Sieve(size, prime1);
  WheelSieve210::WheelSieveBit(size, prime2);
  for (uint32_t i = 2; i <= size; ++i) {
    EXPECT_EQ(IsPrime(i, prime1), WheelSieve210::IsPrimeBit(i, prime2));
  }
}

TEST(SieveTest, SegmentedWheelSieve210Bit) {
  bool prime1[size / 2];
  uint32_t prime2[size / 64 + 1];

  Sieve(size, prime1);
  WheelSieve210::SegmentedWheelSieveBit(size, prime2);
  for (uint32_t i = 2; i <= size; ++i) {
    EXPECT_EQ(IsPrime(i, prime1), WheelSieve210::IsPrimeBit(i, prime2));
  }
}

}  // namespace
