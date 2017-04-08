#include "segmented_sieve.h"

#include <algorithm>
#include <cstdint>

#include "../eratosthenes/eratosthenes.h"
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

static void BM_ImprovedSieve(benchmark::State& state) {
  while (state.KeepRunning()) {
    ImprovedSieve(state.range(0), prime);
  }
}
BENCHMARK(BM_ImprovedSieve)->RangeMultiplier(m)->Range(1024, size);

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
static void BM_ImprovedSieveBitset(benchmark::State& state) {
  while (state.KeepRunning()) {
    int64_t n = state.range(0);
    ImprovedSieveBit(n << 10, prime_bit);
  }
}
BENCHMARK(BM_ImprovedSieveBitset)
    ->RangeMultiplier(m)
    ->Range(1, bitset_size_limit);

}  // namespace

BENCHMARK_MAIN()
