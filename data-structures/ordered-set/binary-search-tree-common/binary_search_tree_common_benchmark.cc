#include "binary_search_tree_common.h"

#include <algorithm>
#include <cstdlib>
#include <limits>
#include <random>

#include "../binary-search-tree/binary_search_tree.h"
#include "benchmark/benchmark_api.h"

namespace {

constexpr int min_size = 1 << 10;
constexpr int max_size = 1 << 20;
constexpr int multiplier = 4;
int test[max_size];

class BSTCommonBenchmark : public benchmark::Fixture {
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

BENCHMARK_DEFINE_F(BSTCommonBenchmark, InorderTraverseRec)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    BinarySearchTree<int> tree;
    BuildTree(state, tree);
    std::vector<int> result;
    result.reserve(state.range(0));
    state.ResumeTiming();
    InorderTraverseRec(tree.root(), result);
  }
}
BENCHMARK_REGISTER_F(BSTCommonBenchmark, InorderTraverseRec)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTCommonBenchmark, InorderTraverse)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    BinarySearchTree<int> tree;
    BuildTree(state, tree);
    std::vector<int> result;
    result.reserve(state.range(0));
    state.ResumeTiming();
    InorderTraverse(tree.root(), result);
  }
}
BENCHMARK_REGISTER_F(BSTCommonBenchmark, InorderTraverse)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTCommonBenchmark, InorderTraverseArray)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    BinarySearchTree<int> tree;
    BuildTree(state, tree);
    int result[state.range(0)];
    state.ResumeTiming();
    InorderTraverse(tree.root(), result);
  }
}
BENCHMARK_REGISTER_F(BSTCommonBenchmark, InorderTraverseArray)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTCommonBenchmark, InorderTraverseMorris)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    BinarySearchTree<int> tree;
    BuildTree(state, tree);
    int result[state.range(0)];
    state.ResumeTiming();
    InorderTraverseMorris(tree.root(), result);
  }
}
BENCHMARK_REGISTER_F(BSTCommonBenchmark, InorderTraverseMorris)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTCommonBenchmark, PreorderTraverseRec)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    BinarySearchTree<int> tree;
    BuildTree(state, tree);
    std::vector<int> result;
    result.reserve(state.range(0));
    state.ResumeTiming();
    PreorderTraverseRec(tree.root(), result);
  }
}
BENCHMARK_REGISTER_F(BSTCommonBenchmark, PreorderTraverseRec)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTCommonBenchmark, PreorderTraverse)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    BinarySearchTree<int> tree;
    BuildTree(state, tree);
    std::vector<int> result;
    result.reserve(state.range(0));
    state.ResumeTiming();
    PreorderTraverse(tree.root(), result);
  }
}
BENCHMARK_REGISTER_F(BSTCommonBenchmark, PreorderTraverse)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTCommonBenchmark, PreorderTraverseArray)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    BinarySearchTree<int> tree;
    BuildTree(state, tree);
    int result[state.range(0)];
    state.ResumeTiming();
    PreorderTraverse(tree.root(), result);
  }
}
BENCHMARK_REGISTER_F(BSTCommonBenchmark, PreorderTraverseArray)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTCommonBenchmark, PreorderTraverseMorris)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    BinarySearchTree<int> tree;
    BuildTree(state, tree);
    int result[state.range(0)];
    state.ResumeTiming();
    PreorderTraverseMorris(tree.root(), result);
  }
}
BENCHMARK_REGISTER_F(BSTCommonBenchmark, PreorderTraverseMorris)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTCommonBenchmark, PostorderTraverseRec)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    BinarySearchTree<int> tree;
    BuildTree(state, tree);
    std::vector<int> result;
    result.reserve(state.range(0));
    state.ResumeTiming();
    PostorderTraverseRec(tree.root(), result);
  }
}
BENCHMARK_REGISTER_F(BSTCommonBenchmark, PostorderTraverseRec)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTCommonBenchmark, PostorderTraverse)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    BinarySearchTree<int> tree;
    BuildTree(state, tree);
    std::vector<int> result;
    result.reserve(state.range(0));
    state.ResumeTiming();
    PostorderTraverse(tree.root(), result);
  }
}
BENCHMARK_REGISTER_F(BSTCommonBenchmark, PostorderTraverse)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTCommonBenchmark, PostorderTraverseArray)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    BinarySearchTree<int> tree;
    BuildTree(state, tree);
    int result[state.range(0)];
    state.ResumeTiming();
    PostorderTraverse(tree.root(), result);
  }
}
BENCHMARK_REGISTER_F(BSTCommonBenchmark, PostorderTraverseArray)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTCommonBenchmark, PostorderTraverseMorris)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    BinarySearchTree<int> tree;
    BuildTree(state, tree);
    int result[state.range(0)];
    state.ResumeTiming();
    PostorderTraverseMorris(tree.root(), result);
  }
}
BENCHMARK_REGISTER_F(BSTCommonBenchmark, PostorderTraverseMorris)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTCommonBenchmark, LevelOrderTraverseQueue)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    BinarySearchTree<int> tree;
    BuildTree(state, tree);
    std::vector<int> result;
    result.reserve(state.range(0));
    state.ResumeTiming();
    LevelOrderTraverseQueue(tree.root(), result);
  }
}
BENCHMARK_REGISTER_F(BSTCommonBenchmark, LevelOrderTraverseQueue)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTCommonBenchmark, LevelOrderTraverse)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    BinarySearchTree<int> tree;
    BuildTree(state, tree);
    std::vector<int> result;
    result.reserve(state.range(0));
    state.ResumeTiming();
    LevelOrderTraverse(tree.root(), result);
  }
}
BENCHMARK_REGISTER_F(BSTCommonBenchmark, LevelOrderTraverse)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

}  // namespace

BENCHMARK_MAIN()
