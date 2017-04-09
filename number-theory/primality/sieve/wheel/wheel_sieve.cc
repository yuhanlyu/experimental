#include "wheel_sieve.h"

#include <cmath>
#include <cstring>
#include <iostream>

#include "../common/common.h"

namespace {

// L1 Data Cache size.
constexpr uint32_t L1DCacheSize = 1 << 16;

template <typename Wheel>
void WheelSieveImpl(uint32_t n, bool prime[]) {
  uint32_t bound = sqrt(n);
  uint32_t max_index = Wheel::WheelIndex(n);
  std::memset(prime, 1, n >> 1);
  if (n <= 15) return;

  uint32_t step_index = 1;
  for (uint32_t i = Wheel::steps[0] + 1, index = 1; i <= bound; ++index) {
    if (prime[index]) {
      uint32_t quo = i / Wheel::primorial, mod = i % Wheel::primorial;
      uint32_t inc[Wheel::number_of_coprimes], m_step_index = step_index;
      for (uint32_t j = 0; j < Wheel::number_of_coprimes; ++j) {
        inc[j] = Wheel::increments[Wheel::coprime_indices[mod]][j] +
                 quo * Wheel::base_increment[j];
      }
      for (uint32_t j_index = Wheel::WheelIndex(i * i); j_index <= max_index;) {
        prime[j_index] = false;
        j_index += inc[m_step_index];
        m_step_index = Wheel::NextStepIndex(m_step_index);
      }
    }
    i += Wheel::steps[step_index];
    step_index = Wheel::NextStepIndex(step_index);
  }
}

template <typename Wheel>
void SegmentedWheelSieveImpl(uint32_t n, bool prime[]) {
  uint32_t bound = sqrt(n);
  std::memset(prime, 1, n >> 1);
  if (n <= 15) return;

  Wheel::WheelSieve(bound, prime);
  uint32_t primes[UpperBoundOfPi(bound)], number_of_primes = 0;
  uint32_t step_index = 1, bound_index = Wheel::WheelIndex(bound);
  for (uint32_t i = Wheel::steps[0] + 1, index = 1; index <= bound_index;
       ++index) {
    if (prime[index]) primes[number_of_primes++] = i;
    i += Wheel::steps[step_index];
    step_index = Wheel::NextStepIndex(step_index);
  }
  uint32_t next[number_of_primes], next_step[number_of_primes];
  uint32_t segment_size = L1DCacheSize >> 1;
  for (uint32_t low = bound + 1, s = 0,
                high = low + segment_size > n ? n : low + segment_size;
       low <= n; low += segment_size) {
    uint32_t high_index = Wheel::WheelIndex(high);
    for (uint32_t h = 0; h < number_of_primes; ++h) {
      uint32_t i = primes[h], j_index;
      if (i * i > high) break;
      if (h < s) {
        j_index = next[h];
        step_index = next_step[h];
      } else {
        uint64_t m = ((low + (i - 1)) / i);
        m += Wheel::need[m % Wheel::primorial];
        step_index = Wheel::coprime_indices[m % Wheel::primorial];
        j_index = Wheel::WheelIndex(m * i);
        ++s;
      }
      if (j_index <= high_index) {
        uint64_t quo = i / Wheel::primorial, mod = i % Wheel::primorial;
        while (j_index <= high_index) {
          prime[j_index] = false;
          j_index +=
              Wheel::increments[Wheel::coprime_indices[mod]][step_index] +
              quo * Wheel::base_increment[step_index];
          step_index = Wheel::NextStepIndex(step_index);
        }
      }
      next[h] = j_index;
      next_step[h] = step_index;
    }
    high = (high + segment_size > n) ? n : high + segment_size;
  }
}

template <typename Wheel>
void WheelSieveBitImpl(uint64_t n, uint32_t prime[]) {
  uint64_t bound = sqrtl(n);
  uint64_t max_index = Wheel::WheelIndex(n);
  std::memset(prime, 0xFF, (max_index >> 3) + 1);
  if (n <= 15) return;

  uint32_t step_index = 1;
  for (uint64_t i = Wheel::steps[0] + 1, index = 1; i <= bound; ++index) {
    if (BitGet(index, prime)) {
      uint64_t quo = i / Wheel::primorial, mod = i % Wheel::primorial;
      uint32_t inc[Wheel::number_of_coprimes], m_step_index = step_index;
      for (uint32_t j = 0; j < Wheel::number_of_coprimes; ++j) {
        inc[j] = Wheel::increments[Wheel::coprime_indices[mod]][j] +
                 quo * Wheel::base_increment[j];
      }
      for (uint64_t j_index = Wheel::WheelIndex(i * i); j_index <= max_index;) {
        BitReset(j_index, prime);
        j_index += inc[m_step_index];
        m_step_index = Wheel::NextStepIndex(m_step_index);
      }
    }
    i += Wheel::steps[step_index];
    step_index = Wheel::NextStepIndex(step_index);
  }
}

template <typename Wheel>
void SegmentedWheelSieveBitImpl(uint64_t n, uint32_t prime[]) {
  uint64_t bound = sqrtl(n);
  uint64_t max_index = Wheel::WheelIndex(n);
  std::memset(prime, 0xFF, (max_index >> 3) + 1);
  if (n <= 15) return;

  Wheel::WheelSieveBit(bound, prime);
  uint32_t primes[UpperBoundOfPi(bound)], number_of_primes = 0;
  uint32_t step_index = 1, bound_index = Wheel::WheelIndex(bound);
  for (uint32_t i = Wheel::steps[0] + 1, index = 1; index <= bound_index;
       ++index) {
    if (BitGet(index, prime)) primes[number_of_primes++] = i;
    i += Wheel::steps[step_index];
    step_index = Wheel::NextStepIndex(step_index);
  }
  uint64_t next[number_of_primes], next_step[number_of_primes];
  uint64_t segment_size = L1DCacheSize << 6;
  for (uint64_t low = bound + 1, s = 0,
                high = low + segment_size > n ? n : low + segment_size;
       low <= n; low += segment_size) {
    uint64_t high_index = Wheel::WheelIndex(high);
    for (uint32_t h = 0; h < number_of_primes; ++h) {
      uint64_t i = primes[h], j_index;
      if (i * i > high) break;
      if (h < s) {
        j_index = next[h];
        step_index = next_step[h];
      } else {
        uint64_t m = ((low + (i - 1)) / i);
        m += Wheel::need[m % Wheel::primorial];
        step_index = Wheel::coprime_indices[m % Wheel::primorial];
        j_index = Wheel::WheelIndex(m * i);
        ++s;
      }
      if (j_index <= high_index) {
        uint64_t quo = i / Wheel::primorial, mod = i % Wheel::primorial;
        while (j_index <= high_index) {
          BitReset(j_index, prime);
          j_index +=
              Wheel::increments[Wheel::coprime_indices[mod]][step_index] +
              quo * Wheel::base_increment[step_index];
          step_index = Wheel::NextStepIndex(step_index);
        }
      }
      next[h] = j_index;
      next_step[h] = step_index;
    }
    high = (high + segment_size > n) ? n : high + segment_size;
  }
}

// TODO(C++17): remove this method when std::size is supported by the compiler.
template <class T, std::size_t N>
constexpr size_t size(const T (&array)[N]) noexcept {
  return N;
}

inline uint64_t WheelIndex(uint64_t n, uint64_t primorial,
                           uint64_t number_of_coprimes,
                           const uint64_t coprime_indices[]) {
  return (n / primorial) * number_of_coprimes + coprime_indices[n % primorial];
}

// This is a producing the values of all required values for a Wheel class.
template <typename Wheel>
void Precompute() {
  uint64_t n = size(Wheel::wheel_primes);
  uint64_t primorial = 1;
  for (int i = 0; i < n; ++i) primorial *= Wheel::wheel_primes[i];
  bool is_coprime[primorial + 1];
  is_coprime[0] = is_coprime[1] = false;
  uint64_t number_of_coprimes = 0;
  for (int i = 1; i < primorial; ++i) {
    bool divisible = false;
    for (int j = 0; j < n; ++j)
      if (i % Wheel::wheel_primes[j] == 0) divisible = true;
    is_coprime[i] = !divisible;
    if (is_coprime[i]) ++number_of_coprimes;
  }

  uint64_t coprimes[number_of_coprimes], coprime_indices[primorial];
  coprime_indices[0] = 0;
  for (int i = 1, s = 0; i < primorial; ++i) {
    coprime_indices[i] = s;
    if (is_coprime[i]) coprimes[s++] = i;
  }

  uint64_t steps[number_of_coprimes];
  for (int i = 0; i < number_of_coprimes - 1; ++i)
    steps[i] = coprimes[i + 1] - coprimes[i];
  steps[number_of_coprimes - 1] =
      primorial - coprimes[number_of_coprimes - 1] + coprimes[0];

  uint64_t next = 0;
  uint64_t need[primorial];
  for (int i = 0; i < primorial; ++i) {
    need[i] = coprimes[next] - i;
    if (need[i] == 0) ++next;
  }

  uint64_t base_increment[number_of_coprimes];
  uint64_t increments[number_of_coprimes][number_of_coprimes];
  for (int i = 0; i < number_of_coprimes; ++i) {
    uint64_t base = WheelIndex(coprimes[i], primorial, number_of_coprimes,
                               coprime_indices),
             acc = 1;
    for (int j = 0; j < number_of_coprimes; ++j) {
      uint64_t temp = WheelIndex(coprimes[i] * (acc + steps[j]), primorial,
                                 number_of_coprimes, coprime_indices);
      increments[i][j] = temp - base;
      base = temp;
      acc += steps[j];
    }
    base_increment[i] = WheelIndex(steps[i] * primorial, primorial,
                                   number_of_coprimes, coprime_indices);
  }

  std::cout << "static constexpr uint64_t wheel_primes[] = {"
            << Wheel::wheel_primes[0];
  for (int i = 1; i < n; ++i) std::cout << ", " << Wheel::wheel_primes[i];
  std::cout << "};\n";

  std::cout << "static constexpr uint64_t primorial = " << primorial << ";\n";
  std::cout << "static constexpr uint64_t number_of_coprimes = "
            << number_of_coprimes << ";\n";

  std::cout << "static constexpr uint64_t steps[] = {" << steps[0];
  for (int i = 1; i < number_of_coprimes; ++i) std::cout << ", " << steps[i];
  std::cout << "};\n";

  std::cout << "static constexpr uint64_t coprime_indices[] = {"
            << coprime_indices[0];
  for (int i = 1; i < primorial; ++i) std::cout << ", " << coprime_indices[i];
  std::cout << "};\n";

  std::cout << "static constexpr uint64_t need[] = {" << need[0];
  for (int i = 1; i < primorial; ++i) std::cout << ", " << need[i];
  std::cout << "};\n";

  std::cout << "static constexpr uint64_t base_increment[] = {"
            << base_increment[0];
  for (int i = 1; i < number_of_coprimes; ++i)
    std::cout << ", " << base_increment[i];
  std::cout << "};\n";

  std::cout
      << "static constexpr uint64_t increments[][number_of_coprimes] = {\n";
  std::cout << "{" << increments[0][0];
  for (int j = 1; j < number_of_coprimes; ++j)
    std::cout << ", " << increments[0][j];
  std::cout << '}';
  for (int i = 1; i < number_of_coprimes; ++i) {
    std::cout << ",\n{" << increments[i][0];
    for (int j = 1; j < number_of_coprimes; ++j)
      std::cout << ", " << increments[i][j];
    std::cout << "}\n";
  }
  std::cout << "};\n";
}

}  // namespace

constexpr uint64_t WheelSieve6::wheel_primes[];
constexpr uint64_t WheelSieve6::primorial;
constexpr uint64_t WheelSieve6::number_of_coprimes;
constexpr uint64_t WheelSieve6::steps[];
constexpr uint64_t WheelSieve6::coprime_indices[];
constexpr uint64_t WheelSieve6::need[];
constexpr uint64_t WheelSieve6::base_increment[];
constexpr uint64_t WheelSieve6::increments[][WheelSieve6::number_of_coprimes];
constexpr uint64_t WheelSieve30::wheel_primes[];
constexpr uint64_t WheelSieve30::primorial;
constexpr uint64_t WheelSieve30::number_of_coprimes;
constexpr uint64_t WheelSieve30::steps[];
constexpr uint64_t WheelSieve30::coprime_indices[];
constexpr uint64_t WheelSieve30::need[];
constexpr uint64_t WheelSieve30::base_increment[];
constexpr uint64_t WheelSieve30::increments[][WheelSieve30::number_of_coprimes];
constexpr uint64_t WheelSieve210::wheel_primes[];
constexpr uint64_t WheelSieve210::primorial;
constexpr uint64_t WheelSieve210::number_of_coprimes;
constexpr uint64_t WheelSieve210::steps[];
constexpr uint64_t WheelSieve210::coprime_indices[];
constexpr uint64_t WheelSieve210::need[];
constexpr uint64_t WheelSieve210::base_increment[];
constexpr uint64_t WheelSieve210::increments[]
                                            [WheelSieve210::number_of_coprimes];

void WheelSieve6::WheelSieve(uint32_t n, bool prime[]) {
  WheelSieveImpl<WheelSieve6>(n, prime);
}

void WheelSieve6::SegmentedWheelSieve(uint32_t n, bool prime[]) {
  SegmentedWheelSieveImpl<WheelSieve6>(n, prime);
}

void WheelSieve6::WheelSieveBit(uint64_t n, uint32_t prime[]) {
  WheelSieveBitImpl<WheelSieve6>(n, prime);
}

void WheelSieve6::SegmentedWheelSieveBit(uint64_t n, uint32_t prime[]) {
  SegmentedWheelSieveBitImpl<WheelSieve6>(n, prime);
}

void WheelSieve30::WheelSieve(uint32_t n, bool prime[]) {
  WheelSieveImpl<WheelSieve30>(n, prime);
}

void WheelSieve30::SegmentedWheelSieve(uint32_t n, bool prime[]) {
  SegmentedWheelSieveImpl<WheelSieve30>(n, prime);
}

void WheelSieve30::WheelSieveBit(uint64_t n, uint32_t prime[]) {
  WheelSieveBitImpl<WheelSieve30>(n, prime);
}

void WheelSieve30::SegmentedWheelSieveBit(uint64_t n, uint32_t prime[]) {
  SegmentedWheelSieveBitImpl<WheelSieve30>(n, prime);
}

void WheelSieve210::WheelSieve(uint32_t n, bool prime[]) {
  WheelSieveImpl<WheelSieve210>(n, prime);
}

void WheelSieve210::SegmentedWheelSieve(uint32_t n, bool prime[]) {
  SegmentedWheelSieveImpl<WheelSieve210>(n, prime);
}

void WheelSieve210::WheelSieveBit(uint64_t n, uint32_t prime[]) {
  WheelSieveBitImpl<WheelSieve210>(n, prime);
}

void WheelSieve210::SegmentedWheelSieveBit(uint64_t n, uint32_t prime[]) {
  SegmentedWheelSieveBitImpl<WheelSieve210>(n, prime);
}
