#include "traversal.h"

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

class BSTTraversalBenchmark : public benchmark::Fixture {
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
  }
};

BENCHMARK_DEFINE_F(BSTTraversalBenchmark, InorderTraverseRec)
(benchmark::State& state) {
  BinarySearchTree<int> tree;
  BuildTree(state, tree);
  std::vector<int> result;
  result.reserve(state.range(0));
  while (state.KeepRunning()) {
    InorderTraverseRec(tree.root(), result);
		result.clear();
  }
}
BENCHMARK_REGISTER_F(BSTTraversalBenchmark, InorderTraverseRec)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTTraversalBenchmark, InorderTraverse)
(benchmark::State& state) {
  BinarySearchTree<int> tree;
  BuildTree(state, tree);
  std::vector<int> result;
  result.reserve(state.range(0));
  while (state.KeepRunning()) {
    InorderTraverse(tree.root(), result);
		result.clear();
  }
}
BENCHMARK_REGISTER_F(BSTTraversalBenchmark, InorderTraverse)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTTraversalBenchmark, InorderTraverseArray)
(benchmark::State& state) {
  BinarySearchTree<int> tree;
  BuildTree(state, tree);
  int result[state.range(0)];
  while (state.KeepRunning()) {
    InorderTraverse(tree.root(), result);
  }
}
BENCHMARK_REGISTER_F(BSTTraversalBenchmark, InorderTraverseArray)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTTraversalBenchmark, InorderTraverseMorris)
(benchmark::State& state) {
  BinarySearchTree<int> tree;
  BuildTree(state, tree);
  int result[state.range(0)];
  while (state.KeepRunning()) {
    InorderTraverseMorris(tree.root(), result);
  }
}
BENCHMARK_REGISTER_F(BSTTraversalBenchmark, InorderTraverseMorris)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTTraversalBenchmark, PreorderTraverseRec)
(benchmark::State& state) {
  BinarySearchTree<int> tree;
  BuildTree(state, tree);
  std::vector<int> result;
  result.reserve(state.range(0));
  while (state.KeepRunning()) {
    PreorderTraverseRec(tree.root(), result);
		result.clear();
  }
}
BENCHMARK_REGISTER_F(BSTTraversalBenchmark, PreorderTraverseRec)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTTraversalBenchmark, PreorderTraverse)
(benchmark::State& state) {
  BinarySearchTree<int> tree;
  BuildTree(state, tree);
  std::vector<int> result;
  result.reserve(state.range(0));
  while (state.KeepRunning()) {
    PreorderTraverse(tree.root(), result);
		result.clear();
  }
}
BENCHMARK_REGISTER_F(BSTTraversalBenchmark, PreorderTraverse)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTTraversalBenchmark, PreorderTraverseArray)
(benchmark::State& state) {
  BinarySearchTree<int> tree;
  BuildTree(state, tree);
  int result[state.range(0)];
  while (state.KeepRunning()) {
    PreorderTraverse(tree.root(), result);
  }
}
BENCHMARK_REGISTER_F(BSTTraversalBenchmark, PreorderTraverseArray)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTTraversalBenchmark, PreorderTraverseMorris)
(benchmark::State& state) {
  BinarySearchTree<int> tree;
  BuildTree(state, tree);
  int result[state.range(0)];
  while (state.KeepRunning()) {
    PreorderTraverseMorris(tree.root(), result);
  }
}
BENCHMARK_REGISTER_F(BSTTraversalBenchmark, PreorderTraverseMorris)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTTraversalBenchmark, PostorderTraverseRec)
(benchmark::State& state) {
  BinarySearchTree<int> tree;
  BuildTree(state, tree);
  std::vector<int> result;
  result.reserve(state.range(0));
  while (state.KeepRunning()) {
    PostorderTraverseRec(tree.root(), result);
		result.clear();
  }
}
BENCHMARK_REGISTER_F(BSTTraversalBenchmark, PostorderTraverseRec)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTTraversalBenchmark, PostorderTraverse)
(benchmark::State& state) {
  BinarySearchTree<int> tree;
  BuildTree(state, tree);
  std::vector<int> result;
  result.reserve(state.range(0));
  while (state.KeepRunning()) {
    PostorderTraverse(tree.root(), result);
		result.clear();
  }
}
BENCHMARK_REGISTER_F(BSTTraversalBenchmark, PostorderTraverse)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTTraversalBenchmark, PostorderTraverseArray)
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
BENCHMARK_REGISTER_F(BSTTraversalBenchmark, PostorderTraverseArray)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTTraversalBenchmark, PostorderTraverseMorris)
(benchmark::State& state) {
  BinarySearchTree<int> tree;
  BuildTree(state, tree);
  int result[state.range(0)];
  while (state.KeepRunning()) {
    PostorderTraverseMorris(tree.root(), result);
  }
}
BENCHMARK_REGISTER_F(BSTTraversalBenchmark, PostorderTraverseMorris)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTTraversalBenchmark, LevelOrderTraverseQueue)
(benchmark::State& state) {
  BinarySearchTree<int> tree;
  BuildTree(state, tree);
  std::vector<int> result;
  result.reserve(state.range(0));
  while (state.KeepRunning()) {
    LevelOrderTraverseQueue(tree.root(), result);
		result.clear();
  }
}
BENCHMARK_REGISTER_F(BSTTraversalBenchmark, LevelOrderTraverseQueue)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(BSTTraversalBenchmark, LevelOrderTraverse)
(benchmark::State& state) {
  BinarySearchTree<int> tree;
  BuildTree(state, tree);
  std::vector<int> result;
  result.reserve(state.range(0));
  while (state.KeepRunning()) {
    LevelOrderTraverse(tree.root(), result);
		result.clear();
  }
}
BENCHMARK_REGISTER_F(BSTTraversalBenchmark, LevelOrderTraverse)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

}  // namespace

BENCHMARK_MAIN()
