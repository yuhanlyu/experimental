#include "weight_balanced_tree.h"

#include <algorithm>
#include <random>

#include "benchmark/benchmark_api.h"

namespace {

constexpr int min_size = 1 << 10;
constexpr int max_size = 1 << 20;
constexpr int multiplier = 4;
int test[max_size];

class WBTBenchmark : public benchmark::Fixture {
 public:
  void SetUp(const ::benchmark::State& state) override {
    for (int i = 0; i < state.range(0); ++i) test[i] = 2 * i + 1;
  }

  static void Shuffle(const ::benchmark::State& state) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(test, test + state.range(0), g);
  }

  static void BuildTree(const ::benchmark::State& state,
                        WeightBalancedTree<int>& tree) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(test, test + state.range(0), g);
    for (int i = 0; i < state.range(0); ++i) tree.Insert(test[i]);
    std::shuffle(test, test + state.range(0), g);
  }
};

BENCHMARK_DEFINE_F(WBTBenchmark, WBTInsert)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    Shuffle(state);
    state.ResumeTiming();
    WeightBalancedTree<int> tree;
    for (int i = 0; i < state.range(0); ++i) {
      tree.Insert(test[i]);
    }
  }
}
BENCHMARK_REGISTER_F(WBTBenchmark, WBTInsert)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(WBTBenchmark, WBTDelete)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    WeightBalancedTree<int> tree;
    BuildTree(state, tree);
    state.ResumeTiming();
    for (int i = 0; i < state.range(0); ++i) {
      tree.Delete(test[i]);
    }
  }
}
BENCHMARK_REGISTER_F(WBTBenchmark, WBTDelete)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

}  // namespace

BENCHMARK_MAIN()
