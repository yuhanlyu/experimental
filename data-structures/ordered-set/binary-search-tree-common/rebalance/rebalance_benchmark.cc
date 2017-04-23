#include "rebalance.h"

#include <algorithm>
#include <cstdlib>
#include <limits>
#include <random>

#include "../../binary-search-tree/binary_search_tree.h"
#include "benchmark/benchmark_api.h"

namespace {

constexpr int min_size = 1 << 10;
constexpr int max_size = 1 << 20;
constexpr int multiplier = 4;
int test[max_size];

class BSTRebalanceBenchmark : public benchmark::Fixture {
 public:
  void SetUp(const ::benchmark::State& state) override {
    for (int i = 0; i < state.range(0); ++i) test[i] = 2 * i + 1;
  }

  static void BuildTree(const ::benchmark::State& state,
                        BinarySearchTree<int>& tree) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(test, test + state.range(0), g);
    for (int i = 0; i < state.range(0); ++i) tree.Insert(test[i]);
    std::shuffle(test, test + state.range(0), g);
  }
};

BENCHMARK_DEFINE_F(BSTRebalanceBenchmark, NaiveRebalance)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    BinarySearchTree<int> tree;
    BuildTree(state, tree);
    std::vector<int> result;
    result.reserve(state.range(0));
    state.ResumeTiming();
    NaiveRebalance(tree.root());
  }
}
BENCHMARK_REGISTER_F(BSTRebalanceBenchmark, NaiveRebalance)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTRebalanceBenchmark, RebalanceByFlatten)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    BinarySearchTree<int> tree;
    BuildTree(state, tree);
    std::vector<int> result;
    result.reserve(state.range(0));
    state.ResumeTiming();
    RebalanceByFlatten(tree.root());
  }
}
BENCHMARK_REGISTER_F(BSTRebalanceBenchmark, RebalanceByFlatten)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTRebalanceBenchmark, RebalanceDay)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    BinarySearchTree<int> tree;
    BuildTree(state, tree);
    std::vector<int> result;
    result.reserve(state.range(0));
    state.ResumeTiming();
    RebalanceDay(tree.root());
  }
}
BENCHMARK_REGISTER_F(BSTRebalanceBenchmark, RebalanceDay)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTRebalanceBenchmark, RebalanceDSW)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    BinarySearchTree<int> tree;
    BuildTree(state, tree);
    std::vector<int> result;
    result.reserve(state.range(0));
    state.ResumeTiming();
    RebalanceDSW(tree.root());
  }
}
BENCHMARK_REGISTER_F(BSTRebalanceBenchmark, RebalanceDSW)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);



}  // namespace

BENCHMARK_MAIN()
