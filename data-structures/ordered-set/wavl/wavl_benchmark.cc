#include <algorithm>
#include <random>
#include <unordered_set>

#include "benchmark/benchmark.h"
#include "wavl.h"
#include "wavl_standard.h"

namespace {

constexpr int min_size = 1 << 10;
constexpr int max_size = 1 << 22;
constexpr int multiplier = 4;
constexpr int batch_size = 10;
int test[max_size];

class WAVLBenchmark : public benchmark::Fixture {
 public:
  void SetUp(const ::benchmark::State& state) override {
    // The scope of test is all odd numbers from 1 to 2 * range - 1.
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
  static void RandomElement(const ::benchmark::State& state, int element[],
                            int batch_size, bool odd = false) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::unordered_set<int> samples;
    for (int i = state.range(0) - batch_size; i < state.range(0); ++i) {
      std::uniform_int_distribution<int> dist(0, i);
      int r = dist(g);
      samples.insert(samples.find(r) == samples.end() ? r : i);
    }

    int i = 0;
    // When odd is 0, the sample is even numbers.
    // When odd is 1, the sample is odd numbers.
    for (int s : samples) {
      element[i++] = 2 * s + odd;
    }

    std::shuffle(element, element + batch_size, g);
  }
};

BENCHMARK_DEFINE_F(WAVLBenchmark, WAVLStandardInsert)
(benchmark::State& state) {
  WAVLStandard<int> tree;
  BuildTree(state, tree);
  int element[batch_size];
  for (auto _ : state) {
    state.PauseTiming();
    RandomElement(state, element, batch_size);
    for (int i = 0; i < batch_size; ++i) {
      state.ResumeTiming();
      tree.Insert(test[i]);
      state.PauseTiming();
    }
    for (int i = 0; i < batch_size; ++i) {
      tree.Delete(element[i]);
    }
  }
}
BENCHMARK_REGISTER_F(WAVLBenchmark, WAVLStandardInsert)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(WAVLBenchmark, WAVLInsert)
(benchmark::State& state) {
  WAVL<int> tree;
  BuildTree(state, tree);
  int element[batch_size];
  for (auto _ : state) {
    state.PauseTiming();
    RandomElement(state, element, batch_size);
    for (int i = 0; i < batch_size; ++i) {
      state.ResumeTiming();
      tree.Insert(test[i]);
      state.PauseTiming();
    }
    for (int i = 0; i < batch_size; ++i) {
      tree.Delete(element[i]);
    }
  }
}
BENCHMARK_REGISTER_F(WAVLBenchmark, WAVLInsert)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(WAVLBenchmark, WAVLRecursiveInsert)
(benchmark::State& state) {
  WAVL<int> tree;
  BuildTree(state, tree);
  int element[batch_size];
  for (auto _ : state) {
    state.PauseTiming();
    RandomElement(state, element, batch_size);
    for (int i = 0; i < batch_size; ++i) {
      state.ResumeTiming();
      tree.RecursiveInsert(test[i]);
      state.PauseTiming();
    }
    for (int i = 0; i < batch_size; ++i) {
      tree.RecursiveDelete(element[i]);
    }
  }
}
BENCHMARK_REGISTER_F(WAVLBenchmark, WAVLRecursiveInsert)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(WAVLBenchmark, WAVLStandardDelete)
(benchmark::State& state) {
  WAVLStandard<int> tree;
  BuildTree(state, tree);
  int element[batch_size];
  for (auto _ : state) {
    state.PauseTiming();
    RandomElement(state, element, batch_size, true);
    for (int i = 0; i < batch_size; ++i) {
      state.ResumeTiming();
      tree.Delete(element[i]);
      state.PauseTiming();
    }
    for (int i = 0; i < batch_size; ++i) {
      tree.Insert(test[i]);
    }
  }
}
BENCHMARK_REGISTER_F(WAVLBenchmark, WAVLStandardDelete)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(WAVLBenchmark, WAVLDelete)
(benchmark::State& state) {
  WAVL<int> tree;
  BuildTree(state, tree);
  int element[batch_size];
  for (auto _ : state) {
    state.PauseTiming();
    RandomElement(state, element, batch_size, true);
    for (int i = 0; i < batch_size; ++i) {
      state.ResumeTiming();
      tree.Delete(element[i]);
      state.PauseTiming();
    }
    for (int i = 0; i < batch_size; ++i) {
      tree.Insert(test[i]);
    }
  }
}
BENCHMARK_REGISTER_F(WAVLBenchmark, WAVLStandardDelete)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(WAVLBenchmark, WAVLRecursiveDelete)
(benchmark::State& state) {
  WAVL<int> tree;
  BuildTree(state, tree);
  int element[batch_size];
  for (auto _ : state) {
    state.PauseTiming();
    RandomElement(state, element, batch_size, true);
    for (int i = 0; i < batch_size; ++i) {
      state.ResumeTiming();
      tree.RecursiveDelete(element[i]);
      state.PauseTiming();
    }
    for (int i = 0; i < batch_size; ++i) {
      tree.RecursiveInsert(test[i]);
    }
  }
}
BENCHMARK_REGISTER_F(WAVLBenchmark, WAVLRecursiveDelete)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

}  // namespace

BENCHMARK_MAIN();
