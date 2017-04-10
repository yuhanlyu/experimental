#include "binary_search.h"

#include <algorithm>
#include <cstdlib>
#include <limits>
#include <random>

#include "benchmark/benchmark_api.h"

namespace {

constexpr int min_size = 1 << 10;
constexpr int max_size = 1 << 28;
constexpr int multiplier = 4;
int test[max_size];

class SearchBenchmark : public benchmark::Fixture {
 public:
  void SetUp(const ::benchmark::State& state) override {
    generator_.seed();
    for (int i = 0; i < state.range(0); ++i) {
      test[i] = 2 * i + 1;
    }
    distribution_ =
        std::uniform_int_distribution<int>(0, state.range(0) * 2 + 1);
  }
  std::default_random_engine generator_;
  std::uniform_int_distribution<int> distribution_;
};

BENCHMARK_DEFINE_F(SearchBenchmark, Random)(benchmark::State& state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(distribution_(generator_));
  }
}
BENCHMARK_REGISTER_F(SearchBenchmark, Random)->Arg(1 << 20);

BENCHMARK_DEFINE_F(SearchBenchmark, BranchfreeBinarySearch)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    int r = distribution_(generator_);
    benchmark::DoNotOptimize(
        BranchfreeBinarySearch(test, test + state.range(0), r));
  }
}
BENCHMARK_REGISTER_F(SearchBenchmark, BranchfreeBinarySearch)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(SearchBenchmark, SkewedBinarySearch)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    int r = distribution_(generator_);
    benchmark::DoNotOptimize(
        SkewedBinarySearch(test, test + state.range(0), r));
  }
}
BENCHMARK_REGISTER_F(SearchBenchmark, SkewedBinarySearch)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(SearchBenchmark, STLSearch)(benchmark::State& state) {
  while (state.KeepRunning()) {
    int r = distribution_(generator_);
    benchmark::DoNotOptimize(std::lower_bound(test, test + state.range(0), r));
  }
}
BENCHMARK_REGISTER_F(SearchBenchmark, STLSearch)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

int compare(const void* p, const void* q) {
  int x = *reinterpret_cast<const int*>(p);
  int y = *reinterpret_cast<const int*>(q);
  return (x == y) ? 0 : ((x < y) ? -1 : 1);
}

BENCHMARK_DEFINE_F(SearchBenchmark, BSearch)(benchmark::State& state) {
  while (state.KeepRunning()) {
    int r = distribution_(generator_);
    benchmark::DoNotOptimize(
        bsearch(&r, test, state.range(0), sizeof(int), compare));
  }
}
BENCHMARK_REGISTER_F(SearchBenchmark, BSearch)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);
}  // namespace

BENCHMARK_MAIN()
