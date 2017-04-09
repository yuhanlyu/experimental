#include "wheel_sieve.h"

#include <algorithm>
#include <cstdint>

#include "../segmented/segmented_sieve.h"
#include "benchmark/benchmark_api.h"

namespace {

constexpr uint32_t size = 1U << 30;
constexpr uint64_t bitset_size = 1LLU << 34;
constexpr uint32_t bitset_size_limit = bitset_size >> 10;
constexpr uint32_t m = 2;

bool prime[size / 2];
uint32_t prime_bit[bitset_size / 64 + 1];

static void BM_SegmentedSieve(benchmark::State& state) {
  while (state.KeepRunning()) {
    SegmentedSieve(state.range(0), prime);
  }
}
BENCHMARK(BM_SegmentedSieve)->RangeMultiplier(m)->Range(1024, size);

static void BM_WheelSieve6(benchmark::State& state) {
  while (state.KeepRunning()) {
    WheelSieve6::WheelSieve(state.range(0), prime);
  }
}
BENCHMARK(BM_WheelSieve6)->RangeMultiplier(m)->Range(1024, size);

static void BM_WheelSieve30(benchmark::State& state) {
  while (state.KeepRunning()) {
    WheelSieve30::WheelSieve(state.range(0), prime);
  }
}
BENCHMARK(BM_WheelSieve30)->RangeMultiplier(m)->Range(1024, size);

static void BM_WheelSieve210(benchmark::State& state) {
  while (state.KeepRunning()) {
    WheelSieve210::WheelSieve(state.range(0), prime);
  }
}
BENCHMARK(BM_WheelSieve210)->RangeMultiplier(m)->Range(1024, size);

static void BM_SegmentedWheelSieve6(benchmark::State& state) {
  while (state.KeepRunning()) {
    WheelSieve6::SegmentedWheelSieve(state.range(0), prime);
  }
}
BENCHMARK(BM_SegmentedWheelSieve6)->RangeMultiplier(m)->Range(1024, size);

static void BM_SegmentedWheelSieve30(benchmark::State& state) {
  while (state.KeepRunning()) {
    WheelSieve30::SegmentedWheelSieve(state.range(0), prime);
  }
}
BENCHMARK(BM_SegmentedWheelSieve30)->RangeMultiplier(m)->Range(1024, size);

static void BM_SegmentedWheelSieve210(benchmark::State& state) {
  while (state.KeepRunning()) {
    WheelSieve210::SegmentedWheelSieve(state.range(0), prime);
  }
}
BENCHMARK(BM_SegmentedWheelSieve210)->RangeMultiplier(m)->Range(1024, size);

// Since the Range parameter is int, which is too small, the input unit is 1024.
static void BM_SegmentedSieveBitset(benchmark::State& state) {
  while (state.KeepRunning()) {
    int64_t n = state.range(0);
    SegmentedSieveBit(n << 10, prime_bit);
  }
}
BENCHMARK(BM_SegmentedSieveBitset)
    ->RangeMultiplier(m)
    ->Range(1, bitset_size_limit);

// Since the Range parameter is int, which is too small, the input unit is 1024.
static void BM_WheelSieve6Bitset(benchmark::State& state) {
  while (state.KeepRunning()) {
    int64_t n = state.range(0);
    WheelSieve6::WheelSieveBit(n << 10, prime_bit);
  }
}
BENCHMARK(BM_WheelSieve6Bitset)
    ->RangeMultiplier(m)
    ->Range(1, bitset_size_limit);

// Since the Range parameter is int, which is too small, the input unit is 1024.
static void BM_WheelSieve30Bitset(benchmark::State& state) {
  while (state.KeepRunning()) {
    int64_t n = state.range(0);
    WheelSieve30::WheelSieveBit(n << 10, prime_bit);
  }
}
BENCHMARK(BM_WheelSieve30Bitset)
    ->RangeMultiplier(m)
    ->Range(1, bitset_size_limit);

// Since the Range parameter is int, which is too small, the input unit is 1024.
static void BM_WheelSieve210Bitset(benchmark::State& state) {
  while (state.KeepRunning()) {
    int64_t n = state.range(0);
    WheelSieve210::WheelSieveBit(n << 10, prime_bit);
  }
}
BENCHMARK(BM_WheelSieve210Bitset)
    ->RangeMultiplier(m)
    ->Range(1, bitset_size_limit);

// Since the Range parameter is int, which is too small, the input unit is 1024.
static void BM_SegmentedWheelSieve6Bitset(benchmark::State& state) {
  while (state.KeepRunning()) {
    int64_t n = state.range(0);
    WheelSieve6::SegmentedWheelSieveBit(n << 10, prime_bit);
  }
}
BENCHMARK(BM_SegmentedWheelSieve6Bitset)
    ->RangeMultiplier(m)
    ->Range(1, bitset_size_limit);

// Since the Range parameter is int, which is too small, the input unit is 1024.
static void BM_SegmentedWheelSieve30Bitset(benchmark::State& state) {
  while (state.KeepRunning()) {
    int64_t n = state.range(0);
    WheelSieve30::SegmentedWheelSieveBit(n << 10, prime_bit);
  }
}
BENCHMARK(BM_SegmentedWheelSieve30Bitset)
    ->RangeMultiplier(m)
    ->Range(1, bitset_size_limit);

// Since the Range parameter is int, which is too small, the input unit is 1024.
static void BM_SegmentedWheelSieve210Bitset(benchmark::State& state) {
  while (state.KeepRunning()) {
    int64_t n = state.range(0);
    WheelSieve210::SegmentedWheelSieveBit(n << 10, prime_bit);
  }
}
BENCHMARK(BM_SegmentedWheelSieve210Bitset)
    ->RangeMultiplier(m)
    ->Range(1, bitset_size_limit);

}  // namespace

BENCHMARK_MAIN()
