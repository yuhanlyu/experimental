#include "scapegoat_tree.h"

#include <algorithm>
#include <cstdlib>
#include <limits>
#include <random>

#include "benchmark/benchmark_api.h"

namespace {

constexpr int min_size = 1 << 10;
constexpr int max_size = 1 << 20;
constexpr int multiplier = 4;
int test[max_size];

class ScapegoatBenchmark : public benchmark::Fixture {
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
                        ScapegoatTree<int>& tree) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(test, test + state.range(0), g);
    for (int i = 0; i < state.range(0); ++i) tree.Insert(test[i]);
    std::shuffle(test, test + state.range(0), g);
  }
};

BENCHMARK_DEFINE_F(ScapegoatBenchmark, ScapegoatTreeInsert)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    Shuffle(state);
    state.ResumeTiming();
    ScapegoatTree<int> tree;
    for (int i = 0; i < state.range(0); ++i) {
      benchmark::DoNotOptimize(tree.Insert(test[i]));
    }
  }
}
BENCHMARK_REGISTER_F(ScapegoatBenchmark, ScapegoatTreeInsert)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(ScapegoatBenchmark, ScapegoatTreeDelete)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    ScapegoatTree<int> tree;
    BuildTree(state, tree);
    state.ResumeTiming();
    for (int i = 0; i < state.range(0); ++i) {
      benchmark::DoNotOptimize(tree.Delete(test[i]));
    }
  }
}
BENCHMARK_REGISTER_F(ScapegoatBenchmark, ScapegoatTreeDelete)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

}  // namespace

BENCHMARK_MAIN()
