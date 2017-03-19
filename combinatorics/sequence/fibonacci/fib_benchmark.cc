#include "fib.h"

#include "benchmark/benchmark_api.h"

namespace {

volatile int32_t n = 92;

static void BM_Iterative(benchmark::State& state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(Iterative(n));
  }
}
BENCHMARK(BM_Iterative);

static void BM_Doubling(benchmark::State& state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(Doubling(n));
  }
}
BENCHMARK(BM_Doubling);

static void BM_Tumble(benchmark::State& state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(Tumble(n));
  }
}
BENCHMARK(BM_Tumble);

static void BM_QMatrix(benchmark::State& state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(QMatrix(n));
  }
}
BENCHMARK(BM_QMatrix);

}  // namespace

BENCHMARK_MAIN()
