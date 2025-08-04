#include <algorithm>
#include <random>
#include <set>

#include "benchmark/benchmark.h"
#include "red_black_tree.h"
#include "red_black_tree_standard.h"
#include "red_black_tree_standard_link.h"

namespace {

constexpr int min_size = 1 << 10;
constexpr int max_size = 1 << 20;
constexpr int multiplier = 4;
int test[max_size];

class RBTreeBenchmark : public benchmark::Fixture {
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

  static void BuildTree(const ::benchmark::State& state, std::set<int>& tree) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(test, test + state.range(0), g);
    for (int i = 0; i < state.range(0); ++i) tree.insert(test[i]);
    std::shuffle(test, test + state.range(0), g);
  }
};

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeStandardInsert)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    Shuffle(state);
    state.ResumeTiming();
    RBTreeStandard<int> tree;
    for (int i = 0; i < state.range(0); ++i) {
      tree.Insert(test[i]);
    }
  }
}
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeStandardInsert)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeStandardLinkInsert)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    Shuffle(state);
    state.ResumeTiming();
    RBTreeStandardLink<int> tree;
    for (int i = 0; i < state.range(0); ++i) {
      tree.Insert(test[i]);
    }
  }
}
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeStandardLinkInsert)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeInsert)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    Shuffle(state);
    state.ResumeTiming();
    RBTree<int> tree;
    for (int i = 0; i < state.range(0); ++i) {
      tree.Insert(test[i]);
    }
  }
}
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeInsert)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeBottomUpInsert)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    Shuffle(state);
    state.ResumeTiming();
    RBTree<int> tree;
    for (int i = 0; i < state.range(0); ++i) {
      tree.BottomUpInsert(test[i]);
    }
  }
}
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeBottomUpInsert)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeTopDownInsert)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    Shuffle(state);
    state.ResumeTiming();
    RBTree<int> tree;
    for (int i = 0; i < state.range(0); ++i) {
      tree.TopDownInsert(test[i]);
    }
  }
}
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeTopDownInsert)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, STLInsert)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    Shuffle(state);
    state.ResumeTiming();
    std::set<int> tree;
    for (int i = 0; i < state.range(0); ++i) {
      tree.insert(test[i]);
    }
  }
}
BENCHMARK_REGISTER_F(RBTreeBenchmark, STLInsert)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeStandardDelete)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    RBTreeStandard<int> tree;
    BuildTree(state, tree);
    state.ResumeTiming();
    for (int i = 0; i < state.range(0); ++i) {
      tree.Delete(test[i]);
    }
  }
}
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeStandardDelete)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeStandardLinkDelete)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    RBTreeStandardLink<int> tree;
    BuildTree(state, tree);
    state.ResumeTiming();
    for (int i = 0; i < state.range(0); ++i) {
      tree.Delete(test[i]);
    }
  }
}
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeStandardLinkDelete)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeDelete)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    RBTree<int> tree;
    BuildTree(state, tree);
    state.ResumeTiming();
    for (int i = 0; i < state.range(0); ++i) {
      tree.Delete(test[i]);
    }
  }
}
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeDelete)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeBottomUpDelete)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    RBTree<int> tree;
    BuildTree(state, tree);
    state.ResumeTiming();
    for (int i = 0; i < state.range(0); ++i) {
      tree.BottomUpDelete(test[i]);
    }
  }
}
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeBottomUpDelete)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeTopDownDelete)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    RBTree<int> tree;
    BuildTree(state, tree);
    state.ResumeTiming();
    for (int i = 0; i < state.range(0); ++i) {
      tree.TopDownDelete(test[i]);
    }
  }
}
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeTopDownDelete)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, STLDelete)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    std::set<int> tree;
    BuildTree(state, tree);
    state.ResumeTiming();
    for (int i = 0; i < state.range(0); ++i) {
      tree.erase(test[i]);
    }
  }
}
BENCHMARK_REGISTER_F(RBTreeBenchmark, STLDelete)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

}  // namespace

BENCHMARK_MAIN();
