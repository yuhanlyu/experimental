#include <algorithm>
#include <random>
#include <unordered_set>

#include "benchmark/benchmark.h"
#include "wavl.h"
#include "wavl_standard.h"

namespace {

constexpr int min_size = 1 << 10;
constexpr int max_size = 1 << 20;
constexpr int multiplier = 4;
constexpr int batch_size = 10;
int test[max_size];

class WAVLBenchmark : public benchmark::Fixture {
 public:
  void SetUp(const ::benchmark::State& state) override {
    for (int i = 0; i < state.range(0); ++i) test[i] = 2 * i + 1;
  }

  static void Shuffle(const ::benchmark::State& state) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(test, test + state.range(0), g);
  }

  template <typename T>
  static void BuildTree(const ::benchmark::State& state, T& tree) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(test, test + state.range(0), g);
    for (int i = 0; i < state.range(0); ++i) tree.Insert(test[i]);
    std::shuffle(test, test + state.range(0), g);
  }

  // Floyd's algorithm.
  static void RandomElement(const ::benchmark::State& state, int insert[],
                            int removal[]) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::unordered_set<int> samples;
    for (int i = state.range(0) - batch_size; i < state.range(0); ++i) {
      std::uniform_int_distribution<int> dist(0, i);
      int r = dist(g);
      samples.insert(samples.find(r) == samples.end() ? r : i);
    }

    int i = 0;
    for (int s : samples) {
      insert[i] = removal[i] = s;
      ++i;
    }

    std::shuffle(insert, insert + batch_size, g);
    std::shuffle(removal, removal + batch_size, g);
  }
};

BENCHMARK_DEFINE_F(WAVLBenchmark, WAVLStandardInsert)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    Shuffle(state);
    state.ResumeTiming();
    WAVLStandard<int> tree;
    for (int i = 0; i < state.range(0); ++i) {
      tree.Insert(test[i]);
    }
  }
}
BENCHMARK_REGISTER_F(WAVLBenchmark, WAVLStandardInsert)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(WAVLBenchmark, WAVLStandardDelete)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    WAVLStandard<int> tree;
    BuildTree(state, tree);
    state.ResumeTiming();
    for (int i = 0; i < state.range(0); ++i) {
      tree.Delete(test[i]);
    }
  }
}
BENCHMARK_REGISTER_F(WAVLBenchmark, WAVLStandardDelete)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(WAVLBenchmark, WAVLStandardMix)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    WAVLStandard<int> tree;
    BuildTree(state, tree);
    int insert[batch_size];
    int removal[batch_size];
    RandomElement(state, insert, removal);
    state.ResumeTiming();
    for (int i = 0; i < batch_size; ++i) {
      tree.Insert(removal[i]);
    }
    for (int i = 0; i < batch_size; ++i) {
      tree.Delete(insert[i]);
    }
  }
}
BENCHMARK_REGISTER_F(WAVLBenchmark, WAVLStandardMix)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(WAVLBenchmark, WAVLInsert)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    Shuffle(state);
    state.ResumeTiming();
    WAVL<int> tree;
    for (int i = 0; i < state.range(0); ++i) {
      tree.Insert(test[i]);
    }
  }
}
BENCHMARK_REGISTER_F(WAVLBenchmark, WAVLInsert)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(WAVLBenchmark, WAVLRecursiveInsert)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    Shuffle(state);
    state.ResumeTiming();
    WAVL<int> tree;
    for (int i = 0; i < state.range(0); ++i) {
      tree.RecursiveInsert(test[i]);
    }
  }
}
BENCHMARK_REGISTER_F(WAVLBenchmark, WAVLRecursiveInsert)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(WAVLBenchmark, WAVLRecursiveDelete)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    WAVL<int> tree;
    BuildTree(state, tree);
    state.ResumeTiming();
    for (int i = 0; i < state.range(0); ++i) {
      tree.RecursiveDelete(test[i]);
    }
  }
}
BENCHMARK_REGISTER_F(WAVLBenchmark, WAVLRecursiveDelete)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

}  // namespace

BENCHMARK_MAIN();
