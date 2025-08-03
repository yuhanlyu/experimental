#include <algorithm>
#include <bit>
#include <cstdlib>
#include <limits>
#include <random>

#include "benchmark/benchmark.h"
#include "binary_search.h"

namespace {
// https://quick-bench.com/q/Q_uS8PSTJSkI9f2hQwMwdqZFB-c

constexpr int max_size = 1 << 28;
alignas(8388608) int test[max_size];
// Prime numbers that are close to power of two.

class SearchBenchmark : public benchmark::Fixture {
 public:
  void SetUp(const ::benchmark::State& state) override {
    generator_.seed();
    distribution_ =
        std::uniform_int_distribution<int>(0, state.range(0) * 2 + 1);
    for (int i = 0; i < state.range(0); ++i) {
      test[i] = 2 * i + 1;
    }
  }
  std::default_random_engine generator_;
  std::uniform_int_distribution<int> distribution_;
};

static void CustomArguments(benchmark::internal::Benchmark* b) {
  constexpr int64_t sizes[18] = {
      1987,    4019,     8101,     16273,    32633,     65413,
      130973,  262051,   524201,   1048391,  2097023,   4194181,
      8388449, 16777049, 33554249, 67108729, 134217493, 268435183};
  for (int i = 0; i < 18; ++i) {
    b->Arg(sizes[i]);
  }
}

BENCHMARK_DEFINE_F(SearchBenchmark, Random)(benchmark::State& state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(distribution_(generator_));
  }
}
BENCHMARK_REGISTER_F(SearchBenchmark, Random)->Apply(CustomArguments);

BENCHMARK_DEFINE_F(SearchBenchmark, BinarySearch)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    int r = distribution_(generator_);
    benchmark::DoNotOptimize(BinarySearch(test, test + state.range(0), r));
  }
}
BENCHMARK_REGISTER_F(SearchBenchmark, BinarySearch)->Apply(CustomArguments);

BENCHMARK_DEFINE_F(SearchBenchmark, BinarySearch1)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    int r = distribution_(generator_);
    benchmark::DoNotOptimize(BinarySearch1(test, test + state.range(0), r));
  }
}
BENCHMARK_REGISTER_F(SearchBenchmark, BinarySearch1)->Apply(CustomArguments);

BENCHMARK_DEFINE_F(SearchBenchmark, BinarySearch2)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    int r = distribution_(generator_);
    benchmark::DoNotOptimize(BinarySearch2(test, test + state.range(0), r));
  }
}
BENCHMARK_REGISTER_F(SearchBenchmark, BinarySearch2)->Apply(CustomArguments);

BENCHMARK_DEFINE_F(SearchBenchmark, BinarySearch3)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    int r = distribution_(generator_);
    benchmark::DoNotOptimize(BinarySearch3(test, test + state.range(0), r));
  }
}
BENCHMARK_REGISTER_F(SearchBenchmark, BinarySearch3)->Apply(CustomArguments);

BENCHMARK_DEFINE_F(SearchBenchmark, Shar1)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    int r = distribution_(generator_);
    benchmark::DoNotOptimize(Shar1(test, test + state.range(0), r));
  }
}
BENCHMARK_REGISTER_F(SearchBenchmark, Shar1)->Apply(CustomArguments);

BENCHMARK_DEFINE_F(SearchBenchmark, Shar2)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    int r = distribution_(generator_);
    benchmark::DoNotOptimize(Shar2(test, test + state.range(0), r));
  }
}
BENCHMARK_REGISTER_F(SearchBenchmark, Shar2)->Apply(CustomArguments);

BENCHMARK_DEFINE_F(SearchBenchmark, SkewedBinarySearch)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    int r = distribution_(generator_);
    benchmark::DoNotOptimize(
        SkewedBinarySearch(test, test + state.range(0), r));
  }
}
BENCHMARK_REGISTER_F(SearchBenchmark, SkewedBinarySearch)
    ->Apply(CustomArguments);

BENCHMARK_DEFINE_F(SearchBenchmark, SharUnroll)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    int r = distribution_(generator_);
    benchmark::DoNotOptimize(SharUnroll(test, test + state.range(0), r));
  }
}
BENCHMARK_REGISTER_F(SearchBenchmark, SharUnroll)->Apply(CustomArguments);

BENCHMARK_DEFINE_F(SearchBenchmark, STLSearch)(benchmark::State& state) {
  while (state.KeepRunning()) {
    int r = distribution_(generator_);
    benchmark::DoNotOptimize(std::lower_bound(test, test + state.range(0), r));
  }
}
BENCHMARK_REGISTER_F(SearchBenchmark, STLSearch)->Apply(CustomArguments);

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
BENCHMARK_REGISTER_F(SearchBenchmark, BSearch)->Apply(CustomArguments);

}  // namespace

BENCHMARK_MAIN();
