#include "binary_search.h"

#include <algorithm>
#include <cstdlib>
#include <limits>
#include <random>

#include "benchmark/benchmark_api.h"

namespace {

constexpr int size = 1 << 20;
int test[size];

class SearchBenchmark : public benchmark::Fixture {
 public:
  void SetUp(const ::benchmark::State& state) override {
    generator.seed();
    for (int i = 0; i < state.range(0); ++i) {
      test[i] = distribution(generator);
    }
    std::sort(test, test + state.range(0));
  }
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution{
      0, std::numeric_limits<int>::max()};
};

BENCHMARK_DEFINE_F(SearchBenchmark, Random)(benchmark::State& state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(distribution(generator));
  }
}
BENCHMARK_REGISTER_F(SearchBenchmark, Random)->Arg(1 << 20);

BENCHMARK_DEFINE_F(SearchBenchmark, BinarySearch)(benchmark::State& state) {
  while (state.KeepRunning()) {
    int r = distribution(generator);
    benchmark::DoNotOptimize(BinarySearch(test, test + state.range(0), r));
  }
}
BENCHMARK_REGISTER_F(SearchBenchmark, BinarySearch)
    ->RangeMultiplier(4)
    ->Range(1 << 10, size);

BENCHMARK_DEFINE_F(SearchBenchmark, BiasedSearch)(benchmark::State& state) {
  while (state.KeepRunning()) {
    int r = distribution(generator);
    benchmark::DoNotOptimize(
        BiasedBinarySearch(test, test + state.range(0), r));
  }
}
BENCHMARK_REGISTER_F(SearchBenchmark, BiasedSearch)
    ->RangeMultiplier(4)
    ->Range(1 << 10, size);

BENCHMARK_DEFINE_F(SearchBenchmark, STLSearch)(benchmark::State& state) {
  while (state.KeepRunning()) {
    int r = distribution(generator);
    benchmark::DoNotOptimize(std::lower_bound(test, test + state.range(0), r));
  }
}
BENCHMARK_REGISTER_F(SearchBenchmark, STLSearch)
    ->RangeMultiplier(4)
    ->Range(1 << 10, size);

int compare(const void* p, const void* q) {
  int x = *reinterpret_cast<const int*>(p);
  int y = *reinterpret_cast<const int*>(q);
  return (x == y) ? 0 : ((x < y) ? -1 : 1);
}

BENCHMARK_DEFINE_F(SearchBenchmark, BSearch)(benchmark::State& state) {
  while (state.KeepRunning()) {
    int r = distribution(generator);
    benchmark::DoNotOptimize(
        bsearch(&r, test, state.range(0), sizeof(int), compare));
  }
}
BENCHMARK_REGISTER_F(SearchBenchmark, BSearch)
    ->RangeMultiplier(4)
    ->Range(1 << 10, size);
}  // namespace

BENCHMARK_MAIN()
