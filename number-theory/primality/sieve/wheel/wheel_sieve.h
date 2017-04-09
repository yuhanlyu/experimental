#ifndef WHEEL_SIEVE_H
#define WHEEL_SIEVE_H

#include <cstdint>

#include "../common/bit_set.h"

// Example usage:
// constexpr int32_t size = 1 << 20;
// bool prime[size / 2];
// WheelSieve6::WheelSieve(size, prime);
// WheelSieve6::IsPrime(n, prime);
//
// Example usage for segmented version:
// constexpr int32_t size = 1 << 20;
// bool prime[size / 2];
// WheelSieve6::SegmentedWheelSieve(size, prime);
// WheelSieve6::IsPrime(n, prime);
//
// Example usage for bitset version:
// constexpr int32_t size = 1 << 20;
// uint32_t prime[size / 64 + 1];
// WheelSieve6::WheelSieveBit(size, prime);
// WheelSieve6::IsPrimeBit(n, prime);
//
// Example usage for segmented bitset version:
// constexpr int32_t size = 1 << 20;
// uint32_t prime[size / 64 + 1];
// WheelSieve6::SegmentedWheelSieveBit(size, prime);
// WheelSieve6::IsPrimeBit(n, prime);
struct WheelSieve6 {
  // Mapping from the number to the index.
  static inline uint64_t WheelIndex(uint64_t n) { return (n << 1) / 6; }

  // Find the next index step
  static inline uint32_t NextStepIndex(uint32_t index) {
    return ++index % number_of_coprimes;
  }

  static bool IsPrime(uint32_t n, const bool prime[]) {
    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    if (n % 5 == 0) return n == 5;
    if (n % 7 == 0) return n == 7;
    return prime[WheelIndex(n)];
  }

  static bool IsPrimeBit(uint64_t n, const uint32_t bitset[]) {
    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    if (n % 5 == 0) return n == 5;
    if (n % 7 == 0) return n == 7;
    return BitGet(WheelIndex(n), bitset);
  }

  static void WheelSieve(uint32_t n, bool prime[]);

  static void SegmentedWheelSieve(uint32_t n, bool prime[]);

  static void WheelSieveBit(uint64_t n, uint32_t prime[]);

  static void SegmentedWheelSieveBit(uint64_t n, uint32_t prime[]);

  static constexpr uint64_t wheel_primes[] = {2, 3};
  static constexpr uint64_t primorial = 6;
  static constexpr uint64_t number_of_coprimes = 2;
  static constexpr uint64_t steps[] = {4, 2};
  static constexpr uint64_t coprime_indices[6] = {0, 0, 1, 1, 1, 1};
  static constexpr uint64_t need[] = {1, 0, 3, 2, 1, 0};
  static constexpr uint64_t base_increment[] = {8, 4};
  static constexpr uint64_t increments[][number_of_coprimes] = {{1, 1}, {7, 3}};
};

// Example usage:
// constexpr int32_t size = 1 << 20;
// bool prime[size / 2];
// WheelSieve30::WheelSieve(size, prime);
// WheelSieve30::IsPrime(n, prime);
//
// Example usage for segmented version:
// constexpr int32_t size = 1 << 20;
// bool prime[size / 2];
// WheelSieve30::SegmentedWheelSieve(size, prime);
// WheelSieve30::IsPrime(n, prime);
//
// Example usage for bitset version:
// constexpr int32_t size = 1 << 20;
// uint32_t prime[size / 64 + 1];
// WheelSieve30::WheelSieveBit(size, prime);
// WheelSieve30::IsPrimeBit(n, prime);
//
// Example usage for segmented bitset version:
// constexpr int32_t size = 1 << 20;
// uint32_t prime[size / 64 + 1];
// WheelSieve30::SegmentedWheelSieveBit(size, prime);
// WheelSieve30::IsPrimeBit(n, prime);
struct WheelSieve30 {
  // Mapping from the number to the index.
  static inline uint64_t WheelIndex(uint64_t n) { return (n << 2) / 15; }

  // Find the next index step
  static inline uint32_t NextStepIndex(uint32_t index) {
    return ++index % number_of_coprimes;
  }

  static bool IsPrime(uint32_t n, const bool prime[]) {
    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    if (n % 5 == 0) return n == 5;
    if (n % 7 == 0) return n == 7;
    return prime[WheelIndex(n)];
  }

  static bool IsPrimeBit(uint64_t n, const uint32_t bitset[]) {
    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    if (n % 5 == 0) return n == 5;
    if (n % 7 == 0) return n == 7;
    return BitGet(WheelIndex(n), bitset);
  }

  static void WheelSieve(uint32_t n, bool prime[]);

  static void SegmentedWheelSieve(uint32_t n, bool prime[]);

  static void WheelSieveBit(uint64_t n, uint32_t prime[]);

  static void SegmentedWheelSieveBit(uint64_t n, uint32_t prime[]);

  static constexpr uint64_t wheel_primes[] = {2, 3, 5};
  static constexpr uint64_t primorial = 30;
  static constexpr uint64_t number_of_coprimes = 8;
  static constexpr uint64_t steps[] = {6, 4, 2, 4, 2, 4, 6, 2};
  static constexpr uint64_t coprime_indices[] = {0, 0, 1, 1, 1, 1, 1, 1, 2, 2,
                                                 2, 2, 3, 3, 4, 4, 4, 4, 5, 5,
                                                 6, 6, 6, 6, 7, 7, 7, 7, 7, 7};
  static constexpr uint64_t need[] = {1, 0, 5, 4, 3, 2, 1, 0, 3, 2,
                                      1, 0, 1, 0, 3, 2, 1, 0, 1, 0,
                                      3, 2, 1, 0, 5, 4, 3, 2, 1, 0};
  static constexpr uint64_t base_increment[] = {48, 32, 16, 32, 16, 32, 48, 16};
  static constexpr uint64_t increments[][number_of_coprimes] = {
      {1, 1, 1, 1, 1, 1, 1, 1},         {12, 7, 4, 7, 4, 7, 12, 3},
      {18, 12, 6, 11, 6, 12, 18, 5},    {21, 14, 7, 13, 7, 14, 21, 7},
      {27, 18, 9, 19, 9, 18, 27, 9},    {30, 20, 10, 21, 10, 20, 30, 11},
      {36, 25, 12, 25, 12, 25, 36, 13}, {47, 31, 15, 31, 15, 31, 47, 15}};
};

// Example usage:
// constexpr int32_t size = 1 << 20;
// bool prime[size / 2];
// WheelSieve210::WheelSieve(size, prime);
// WheelSieve210::IsPrime(n, prime);
//
// Example usage for segmented version:
// constexpr int32_t size = 1 << 20;
// bool prime[size / 2];
// WheelSieve210::SegmentedWheelSieve(size, prime);
// WheelSieve210::IsPrime(n, prime);
//
// Example usage for bitset version:
// constexpr int32_t size = 1 << 20;
// uint32_t prime[size / 64 + 1];
// WheelSieve210::WheelSieveBit(size, prime);
// WheelSieve210::IsPrimeBit(n, prime);
//
// Example usage for segmented bitset version:
// constexpr int32_t size = 1 << 20;
// uint32_t prime[size / 64 + 1];
// WheelSieve210::SegmentedWheelSieveBit(size, prime);
// WheelSieve210::IsPrimeBit(n, prime);
struct WheelSieve210 {
  // Mapping from the number to the index.
  static inline uint64_t WheelIndex(uint64_t n) {
    return (n / primorial) * number_of_coprimes +
           coprime_indices[n % primorial];
  }

  // Find the next index step
  static inline uint32_t NextStepIndex(uint32_t index) {
    return ++index % number_of_coprimes;
  }

  static bool IsPrime(uint32_t n, const bool prime[]) {
    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    if (n % 5 == 0) return n == 5;
    if (n % 7 == 0) return n == 7;
    return prime[WheelIndex(n)];
  }

  static bool IsPrimeBit(uint64_t n, const uint32_t bitset[]) {
    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    if (n % 5 == 0) return n == 5;
    if (n % 7 == 0) return n == 7;
    return BitGet(WheelIndex(n), bitset);
  }

  static void WheelSieve(uint32_t n, bool prime[]);

  static void SegmentedWheelSieve(uint32_t n, bool prime[]);

  static void WheelSieveBit(uint64_t n, uint32_t prime[]);

  static void SegmentedWheelSieveBit(uint64_t n, uint32_t prime[]);

  static constexpr uint64_t wheel_primes[] = {2, 3, 5, 7};
  static constexpr uint64_t primorial = 210;
  static constexpr uint64_t number_of_coprimes = 48;
  static constexpr uint64_t steps[] = {
      10, 2, 4, 2, 4, 6, 2, 6, 4, 2, 4, 6, 6, 2, 6, 4, 2, 6, 4, 6, 8, 4, 2,  4,
      2,  4, 8, 6, 4, 6, 2, 4, 6, 2, 6, 6, 4, 2, 4, 6, 2, 6, 4, 2, 4, 2, 10, 2};
  static constexpr uint64_t coprime_indices[] = {
      0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  3,  3,  3,  3,
      4,  4,  5,  5,  5,  5,  6,  6,  6,  6,  6,  6,  7,  7,  8,  8,  8,  8,
      8,  8,  9,  9,  9,  9,  10, 10, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12,
      13, 13, 13, 13, 13, 13, 14, 14, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16,
      17, 17, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 20, 20, 20, 20, 20, 20,
      21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 23, 23, 24, 24, 24, 24,
      25, 25, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28,
      28, 28, 29, 29, 29, 29, 30, 30, 30, 30, 30, 30, 31, 31, 32, 32, 32, 32,
      33, 33, 33, 33, 33, 33, 34, 34, 35, 35, 35, 35, 35, 35, 36, 36, 36, 36,
      36, 36, 37, 37, 37, 37, 38, 38, 39, 39, 39, 39, 40, 40, 40, 40, 40, 40,
      41, 41, 42, 42, 42, 42, 42, 42, 43, 43, 43, 43, 44, 44, 45, 45, 45, 45,
      46, 46, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47};
  static constexpr uint64_t need[] = {
      1, 0, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 0, 3, 2, 1, 0, 1, 0, 3, 2, 1, 0,
      5, 4, 3, 2, 1, 0, 1, 0, 5, 4, 3, 2, 1, 0, 3, 2, 1, 0, 1, 0, 3, 2, 1, 0,
      5, 4, 3, 2, 1, 0, 5, 4, 3, 2, 1, 0, 1, 0, 5, 4, 3, 2, 1, 0, 3, 2, 1, 0,
      1, 0, 5, 4, 3, 2, 1, 0, 3, 2, 1, 0, 5, 4, 3, 2, 1, 0, 7, 6, 5, 4, 3, 2,
      1, 0, 3, 2, 1, 0, 1, 0, 3, 2, 1, 0, 1, 0, 3, 2, 1, 0, 7, 6, 5, 4, 3, 2,
      1, 0, 5, 4, 3, 2, 1, 0, 3, 2, 1, 0, 5, 4, 3, 2, 1, 0, 1, 0, 3, 2, 1, 0,
      5, 4, 3, 2, 1, 0, 1, 0, 5, 4, 3, 2, 1, 0, 5, 4, 3, 2, 1, 0, 3, 2, 1, 0,
      1, 0, 3, 2, 1, 0, 5, 4, 3, 2, 1, 0, 1, 0, 5, 4, 3, 2, 1, 0, 3, 2, 1, 0,
      1, 0, 3, 2, 1, 0, 1, 0, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  static constexpr uint64_t base_increment[] = {
      480, 96,  192, 96,  192, 288, 96,  288, 192, 96,  192, 288,
      288, 96,  288, 192, 96,  288, 192, 288, 384, 192, 96,  192,
      96,  192, 384, 288, 192, 288, 96,  192, 288, 96,  288, 288,
      192, 96,  192, 288, 96,  288, 192, 96,  192, 96,  480, 96};
  static constexpr uint64_t increments[][number_of_coprimes] = {
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {26, 5,  10, 5,  11, 15, 4,  16, 10, 5,  9,  15, 16, 5,  15, 10,
       5,  15, 11, 14, 20, 11, 5,  9,  5,  11, 20, 14, 11, 15, 5,  10,
       15, 5,  16, 15, 9,  5,  10, 16, 4,  15, 11, 5,  10, 5,  26, 3},
      {30, 6,  11, 7,  12, 17, 7,  18, 12, 5,  12, 18, 17, 6,  19, 12,
       6,  17, 12, 18, 24, 12, 6,  11, 6,  12, 24, 18, 12, 17, 6,  12,
       19, 6,  17, 18, 12, 5,  12, 18, 7,  17, 12, 7,  11, 6,  30, 5},
      {39, 7,  17, 8,  15, 24, 7,  23, 16, 7,  16, 24, 22, 9,  23, 15,
       8,  24, 15, 24, 30, 16, 8,  15, 8,  16, 30, 24, 15, 24, 8,  15,
       23, 9,  22, 24, 16, 7,  16, 23, 7,  24, 15, 8,  17, 7,  39, 7},
      {43, 9,  18, 8,  17, 26, 9,  27, 16, 9,  18, 25, 27, 9,  25, 18,
       8,  27, 17, 25, 35, 18, 9,  17, 9,  18, 35, 25, 17, 27, 8,  18,
       25, 9,  27, 25, 18, 9,  16, 27, 9,  26, 17, 8,  18, 9,  43, 9},
      {53, 10, 21, 10, 22, 31, 11, 30, 22, 10, 22, 31, 31, 11, 32, 20,
       11, 31, 22, 31, 42, 21, 11, 21, 11, 21, 42, 31, 22, 31, 11, 20,
       32, 11, 31, 31, 22, 10, 22, 30, 11, 31, 22, 10, 21, 10, 53, 11},
      {67, 12, 28, 12, 27, 40, 13, 40, 26, 14, 26, 40, 40, 13, 40, 26,
       13, 40, 26, 41, 53, 27, 13, 25, 13, 27, 53, 41, 26, 40, 13, 26,
       40, 13, 40, 40, 26, 14, 26, 40, 13, 40, 27, 12, 28, 12, 67, 13},
      {70, 15, 28, 14, 29, 42, 14, 42, 28, 16, 28, 42, 42, 15, 42, 28,
       14, 43, 29, 42, 57, 28, 15, 27, 15, 28, 57, 42, 29, 43, 14, 28,
       42, 15, 42, 42, 28, 16, 28, 42, 14, 42, 29, 14, 28, 15, 70, 15},
      {85, 17, 33, 18, 32, 52, 16, 52, 34, 16, 34, 51, 51, 16, 51, 34,
       17, 51, 33, 51, 68, 33, 18, 33, 18, 33, 68, 51, 33, 51, 17, 34,
       51, 16, 51, 51, 34, 16, 34, 52, 16, 52, 32, 18, 33, 17, 85, 17},
      {94, 19, 37, 18, 38, 56, 18, 58, 37, 19, 37, 57, 56, 18, 56, 38,
       19, 56, 38, 56, 75, 37, 19, 37, 19, 37, 75, 56, 38, 56, 19, 38,
       56, 18, 56, 57, 37, 19, 37, 58, 18, 56, 38, 18, 37, 19, 94, 19},
      {98, 19, 39, 20, 39, 60, 20, 58, 40, 19, 39, 59, 59, 20, 59, 40,
       20, 58, 39, 60, 78, 39, 20, 39, 20, 39, 78, 60, 39, 58, 20, 40,
       59, 20, 59, 59, 39, 19, 40, 58, 20, 60, 39, 20, 39, 19, 98, 21},
      {106, 22, 43, 22, 43, 64, 22, 64, 43, 21, 44, 64, 65, 20, 65,  43,
       22,  64, 43, 65, 85, 43, 21, 45, 21, 43, 85, 65, 43, 64, 22,  43,
       65,  20, 65, 64, 44, 21, 43, 64, 22, 64, 43, 22, 43, 22, 106, 23},
      {120, 25, 49, 23, 49, 73, 24, 73, 49, 23, 49, 73, 72, 25, 72,  49,
       24,  73, 49, 71, 97, 49, 24, 49, 24, 49, 97, 71, 49, 73, 24,  49,
       72,  25, 72, 73, 49, 23, 49, 73, 24, 73, 49, 23, 49, 25, 120, 25},
      {135, 26, 54, 28, 53,  82, 26, 82, 54, 26, 55,  80, 81, 27, 81,  55,
       26,  81, 54, 81, 108, 54, 27, 53, 27, 54, 108, 81, 54, 81, 26,  55,
       81,  27, 81, 80, 55,  26, 54, 82, 26, 82, 53,  28, 54, 26, 135, 27},
      {139, 27, 57, 28, 55,  84, 28, 83, 56, 28, 55,  85, 83, 28, 83,  56,
       29,  84, 55, 83, 112, 56, 28, 55, 28, 56, 112, 83, 55, 84, 29,  56,
       83,  28, 83, 85, 55,  28, 56, 83, 28, 84, 55,  28, 57, 27, 139, 29},
      {153, 31, 61, 30, 62,  92, 30, 92, 61, 31, 61,  92, 92, 30, 93,  60,
       32,  92, 60, 93, 123, 61, 30, 61, 30, 61, 123, 93, 60, 92, 32,  60,
       93,  30, 92, 92, 61,  31, 61, 92, 30, 92, 62,  30, 61, 31, 153, 31},
      {162, 33, 64, 33, 64,  98, 32, 98, 65, 33, 64,  98, 98, 31, 97,  66,
       32,  97, 65, 98, 129, 66, 32, 65, 32, 66, 129, 98, 65, 97, 32,  66,
       97,  31, 98, 98, 64,  33, 65, 98, 32, 98, 64,  33, 64, 33, 162, 33},
      {166, 34, 66,  33,  67, 100, 33, 101, 67,  34, 66,  100,
       100, 34, 100, 66,  34, 99,  67, 101, 133, 67, 33,  67,
       33,  67, 133, 101, 67, 99,  34, 66,  100, 34, 100, 100,
       66,  34, 67,  101, 33, 100, 67, 33,  66,  34, 166, 35},
      {180, 36, 73,  36,  71, 109, 36, 109, 72,  36, 72,  109,
       108, 37, 108, 71,  36, 109, 73, 107, 145, 72, 36,  73,
       36,  72, 145, 107, 73, 109, 36, 71,  108, 37, 108, 109,
       72,  36, 72,  109, 36, 109, 71, 36,  73,  36, 180, 37},
      {190, 37, 76,  38,  76, 113, 39, 113, 77,  37, 76,  115,
       113, 38, 113, 76,  38, 115, 75, 114, 152, 76, 37,  77,
       37,  76, 152, 114, 75, 115, 38, 76,  113, 38, 113, 115,
       76,  37, 77,  113, 39, 113, 76, 38,  76,  37, 190, 39},
      {203, 41, 82,  39,  82, 123, 40, 122, 82,  41, 81,  121,
       123, 40, 123, 81,  41, 121, 82, 122, 163, 81, 40,  83,
       40,  81, 163, 122, 82, 121, 41, 81,  123, 40, 123, 121,
       81,  41, 82,  122, 40, 123, 82, 39,  82,  41, 203, 41},
      {222, 45, 88,  44,  89, 134, 44, 133, 89,  44, 88,  133,
       134, 44, 134, 87,  45, 133, 89, 133, 177, 88, 45,  89,
       45,  88, 177, 133, 89, 133, 45, 87,  134, 44, 134, 133,
       88,  44, 89,  133, 44, 134, 89, 44,  88,  45, 222, 43},
      {232, 46, 92,  46,  92, 140, 45, 138, 93,  46, 92,  139,
       139, 46, 139, 92,  46, 138, 93, 138, 184, 93, 47,  91,
       47,  93, 184, 138, 93, 138, 46, 92,  139, 46, 139, 139,
       92,  46, 93,  138, 45, 140, 92, 46,  92,  46, 232, 45},
      {236, 47, 94,  47,  94, 142, 47, 141, 94,  47, 93,  142,
       142, 47, 141, 94,  47, 141, 94, 141, 189, 95, 47,  93,
       47,  95, 189, 141, 94, 141, 47, 94,  141, 47, 142, 142,
       93,  47, 94,  141, 47, 142, 94, 47,  94,  47, 236, 47},
      {244, 49, 98,  49,  98, 146, 49, 147, 98,  49, 99,  146,
       146, 49, 147, 98,  49, 147, 98, 147, 195, 97, 49,  99,
       49,  97, 195, 147, 98, 147, 49, 98,  147, 49, 146, 146,
       99,  49, 98,  147, 49, 146, 98, 49,  98,  49, 244, 49},
      {248, 50, 100, 50,  100, 148, 51,  150, 99,  50, 100, 149,
       149, 50, 149, 100, 50,  150, 99,  150, 200, 99, 49,  101,
       49,  99, 200, 150, 99,  150, 50,  100, 149, 50, 149, 149,
       100, 50, 99,  150, 51,  148, 100, 50,  100, 50, 248, 51},
      {258, 51,  104, 52,  103, 154, 52,  155, 103, 52,  104, 155,
       154, 52,  154, 105, 51,  155, 103, 155, 207, 104, 51,  103,
       51,  104, 207, 155, 103, 155, 51,  105, 154, 52,  154, 155,
       104, 52,  103, 155, 52,  154, 103, 52,  104, 51,  258, 53},
      {277, 55,  110, 57,  110, 165, 56,  166, 110, 55,  111, 167,
       165, 56,  165, 111, 55,  167, 110, 166, 221, 111, 56,  109,
       56,  111, 221, 166, 110, 167, 55,  111, 165, 56,  165, 167,
       111, 55,  110, 166, 56,  165, 110, 57,  110, 55,  277, 55},
      {290, 59,  116, 58,  116, 175, 57,  175, 115, 59,  116, 173,
       175, 58,  175, 116, 58,  173, 117, 174, 232, 116, 59,  115,
       59,  116, 232, 174, 117, 173, 58,  116, 175, 58,  175, 173,
       116, 59,  115, 175, 57,  175, 116, 58,  116, 59,  290, 57},
      {300, 60,  119, 60,  121, 179, 60,  179, 120, 60,  120, 179,
       180, 59,  180, 121, 60,  179, 119, 181, 239, 120, 60,  119,
       60,  120, 239, 181, 119, 179, 60,  121, 180, 59,  180, 179,
       120, 60,  120, 179, 60,  179, 121, 60,  119, 60,  300, 59},
      {314, 62,  126, 63,  125, 188, 63,  187, 125, 62,  126, 188,
       188, 62,  188, 126, 62,  189, 125, 187, 251, 125, 63,  125,
       63,  125, 251, 187, 125, 189, 62,  126, 188, 62,  188, 188,
       126, 62,  125, 187, 63,  188, 125, 63,  126, 62,  314, 61},
      {318, 63,  128, 63,  128, 190, 64,  190, 127, 63,  128, 190,
       190, 65,  191, 126, 64,  191, 127, 190, 255, 126, 64,  127,
       64,  126, 255, 190, 127, 191, 64,  126, 191, 65,  190, 190,
       128, 63,  127, 190, 64,  190, 128, 63,  128, 63,  318, 63},
      {327, 65,  131, 66,  130, 196, 66,  196, 131, 65,  131, 196,
       196, 66,  195, 132, 64,  196, 132, 195, 261, 131, 66,  131,
       66,  131, 261, 195, 132, 196, 64,  132, 195, 66,  196, 196,
       131, 65,  131, 196, 66,  196, 130, 66,  131, 65,  327, 65},
      {341, 69,  135, 68,  137, 204, 68,  205, 136, 68,  137, 203,
       205, 68,  205, 136, 67,  204, 137, 205, 272, 136, 68,  137,
       68,  136, 272, 205, 137, 204, 67,  136, 205, 68,  205, 203,
       137, 68,  136, 205, 68,  204, 137, 68,  135, 69,  341, 67},
      {345, 70,  138, 68,  139, 206, 70,  206, 138, 70,  137, 208,
       207, 69,  207, 137, 70,  207, 138, 207, 276, 138, 69,  139,
       69,  138, 276, 207, 138, 207, 70,  137, 207, 69,  207, 208,
       137, 70,  138, 206, 70,  206, 139, 68,  138, 70,  345, 69},
      {360, 71,  143, 73,  143, 215, 72,  215, 143, 73,  143, 215,
       216, 71,  216, 143, 72,  215, 143, 217, 287, 143, 72,  143,
       72,  143, 287, 217, 143, 215, 72,  143, 216, 71,  216, 215,
       143, 73,  143, 215, 72,  215, 143, 73,  143, 71,  360, 71},
      {374, 74,  149, 74,  149, 224, 74,  224, 149, 75,  148, 224,
       223, 76,  223, 149, 74,  224, 149, 223, 299, 149, 75,  147,
       75,  149, 299, 223, 149, 224, 74,  149, 223, 76,  223, 224,
       148, 75,  149, 224, 74,  224, 149, 74,  149, 74,  374, 73},
      {382, 77,  153, 76,  153, 228, 76,  230, 152, 77,  153, 229,
       229, 76,  229, 152, 76,  230, 153, 228, 306, 153, 76,  153,
       76,  153, 306, 228, 153, 230, 76,  152, 229, 76,  229, 229,
       153, 77,  152, 230, 76,  228, 153, 76,  153, 77,  382, 75},
      {386, 77,  155, 78,  154, 232, 78,  230, 155, 77,  155, 231,
       232, 78,  232, 154, 77,  232, 154, 232, 309, 155, 77,  155,
       77,  155, 309, 232, 154, 232, 77,  154, 232, 78,  232, 231,
       155, 77,  155, 230, 78,  232, 154, 78,  155, 77,  386, 77},
      {395, 79,  159, 78,  160, 236, 80,  236, 158, 80,  158, 237,
       237, 80,  237, 158, 79,  237, 159, 237, 316, 159, 78,  159,
       78,  159, 316, 237, 159, 237, 79,  158, 237, 80,  237, 237,
       158, 80,  158, 236, 80,  236, 160, 78,  159, 79,  395, 79},
      {410, 81,  164, 82,  163, 246, 82,  246, 164, 80,  164, 246,
       246, 81,  246, 164, 82,  245, 163, 246, 327, 164, 81,  165,
       81,  164, 327, 246, 163, 245, 82,  164, 246, 81,  246, 246,
       164, 80,  164, 246, 82,  246, 163, 82,  164, 81,  410, 81},
      {413, 84,  164, 84,  165, 248, 83,  248, 166, 82,  166, 248,
       248, 83,  248, 166, 83,  248, 166, 247, 331, 165, 83,  167,
       83,  165, 331, 247, 166, 248, 83,  166, 248, 83,  248, 248,
       166, 82,  166, 248, 83,  248, 165, 84,  164, 84,  413, 83},
      {427, 86,  171, 86,  170, 257, 85,  258, 170, 86,  170, 257,
       257, 85,  256, 172, 85,  257, 170, 257, 342, 171, 85,  171,
       85,  171, 342, 257, 170, 257, 85,  172, 256, 85,  257, 257,
       170, 86,  170, 258, 85,  257, 170, 86,  171, 86,  427, 85},
      {437, 87,  174, 88,  175, 262, 87,  261, 176, 87,  174, 263,
       261, 87,  263, 174, 88,  261, 175, 263, 349, 174, 87,  175,
       87,  174, 349, 263, 175, 261, 88,  174, 263, 87,  261, 263,
       174, 87,  176, 261, 87,  262, 175, 88,  174, 87,  437, 87},
      {441, 89,  175, 88,  177, 264, 89,  265, 176, 89,  176, 264,
       266, 87,  265, 177, 88,  264, 177, 264, 354, 176, 88,  177,
       88,  176, 354, 264, 177, 264, 88,  177, 265, 87,  266, 264,
       176, 89,  176, 265, 89,  264, 177, 88,  175, 89,  441, 89},
      {450, 90,  181, 89,  180, 271, 89,  270, 180, 91,  180, 270,
       271, 90,  269, 180, 90,  271, 180, 270, 360, 180, 90,  181,
       90,  180, 360, 270, 180, 271, 90,  180, 269, 90,  271, 270,
       180, 91,  180, 270, 89,  271, 180, 89,  181, 90,  450, 91},
      {454, 91,  182, 91,  181, 273, 92,  272, 182, 91,  183, 273,
       272, 91,  273, 182, 91,  273, 181, 274, 364, 181, 91,  183,
       91,  181, 364, 274, 181, 273, 91,  182, 273, 91,  272, 273,
       183, 91,  182, 272, 92,  273, 181, 91,  182, 91,  454, 93},
      {479, 95,  191, 95,  191, 287, 95,  287, 191, 95,  191, 287,
       287, 95,  287, 191, 95,  287, 191, 287, 383, 191, 95,  191,
       95,  191, 383, 287, 191, 287, 95,  191, 287, 95,  287, 287,
       191, 95,  191, 287, 95,  287, 191, 95,  191, 95,  479, 95}};
};
#endif
