#include "search.h"

#include <algorithm>
#include <limits>
#include <random>

#include "../../binary-search-tree/binary_search_tree.h"
#include "../rebalance/rebalance.h"
#include "benchmark/benchmark_api.h"

namespace {

constexpr int min_size = 1 << 10;
constexpr int max_size = 1 << 20;
constexpr int multiplier = 4;
int test_input[max_size];
int test_query[max_size];

class BSTSearchBenchmark : public benchmark::Fixture {
 public:
  void SetUp(const ::benchmark::State& state) override {
    for (int i = 0; i < state.range(0); ++i) test_input[i] = 2 * i + 1;
  }

  static void BuildTree(const ::benchmark::State& state,
                        BinarySearchTree<int>& tree) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(test_input, test_input + state.range(0), g);
    for (int i = 0; i < state.range(0); ++i) tree.Insert(test_input[i]);
    NaiveRebalance(tree.root());
    std::uniform_int_distribution<> dis(0, 2 * state.range(0) + 1);
    for (int i = 0; i < state.range(0); ++i) test_query[i] = dis(g);
  }
};

BENCHMARK_DEFINE_F(BSTSearchBenchmark, NaiveSearch)
(benchmark::State& state) {
  BinarySearchTree<int> tree;
  BuildTree(state, tree);
  while (state.KeepRunning()) {
    for (int i = 0; i < state.range(0); ++i)
      ::benchmark::DoNotOptimize(Search(tree.root(), test_query[i]));
  }
}
BENCHMARK_REGISTER_F(BSTSearchBenchmark, NaiveSearch)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTSearchBenchmark, FastSearch)
(benchmark::State& state) {
  BinarySearchTree<int> tree;
  BuildTree(state, tree);
  while (state.KeepRunning()) {
    for (int i = 0; i < state.range(0); ++i)
      ::benchmark::DoNotOptimize(FastSearch(tree.root(), test_query[i]));
  }
}
BENCHMARK_REGISTER_F(BSTSearchBenchmark, FastSearch)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

}  // namespace

BENCHMARK_MAIN()
