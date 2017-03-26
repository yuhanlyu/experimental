#include "josephus.h"

#include "benchmark/benchmark_api.h"

namespace {

static constexpr int n = 1 << 21;
static constexpr int m = 3;

static void BM_Woodhousea(benchmark::State& state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(Woodhousea(n, state.range(0)));
  }
}
BENCHMARK(BM_Woodhousea)->RangeMultiplier(m)->Range(2, n);

static void BM_ConcreteMath(benchmark::State& state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(ConcreteMath(n, state.range(0)));
  }
}
BENCHMARK(BM_ConcreteMath)->RangeMultiplier(m)->Range(2, n);

static void BM_TAOCP(benchmark::State& state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(TAOCP(n, state.range(0)));
  }
}
BENCHMARK(BM_TAOCP)->RangeMultiplier(m)->Range(2, n);

static void BM_TAOCPK(benchmark::State& state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(TAOCPK(n, state.range(0), n));
  }
}
BENCHMARK(BM_TAOCPK)->RangeMultiplier(m)->Range(2, n);

static void BM_Gelgi(benchmark::State& state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(Gelgi(n, state.range(0)));
  }
}
BENCHMARK(BM_Gelgi)->RangeMultiplier(m)->Range(2, n);

static void BM_ImprovedGelgi(benchmark::State& state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(ImprovedGelgi(n, state.range(0)));
  }
}
BENCHMARK(BM_ImprovedGelgi)->RangeMultiplier(m)->Range(2, n);
}  // namespace

BENCHMARK_MAIN()
