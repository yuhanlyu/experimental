#include <algorithm>
#include <random>
#include <set>
#include <unordered_set>

#include "benchmark/benchmark.h"
#include "red_black_tree.h"
#include "red_black_tree_standard.h"
#include "red_black_tree_standard_link.h"

namespace {

constexpr int min_size = 1 << 10;
constexpr int max_size = 1 << 22;
constexpr int multiplier = 4;
constexpr int batch_size = 10;
int test[max_size];

class RBTreeBenchmark : public benchmark::Fixture {
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

  static void BuildTree(const ::benchmark::State& state, std::set<int>& tree) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(test, test + state.range(0), g);
    for (int i = 0; i < state.range(0); ++i) tree.insert(test[i]);
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

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeStandardInsert)
(benchmark::State& state) {
  RBTreeStandard<int> tree;
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
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeStandardInsert)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeStandardLinkInsert)
(benchmark::State& state) {
  RBTreeStandardLink<int> tree;
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
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeStandardLinkInsert)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeInsert)
(benchmark::State& state) {
  RBTree<int> tree;
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
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeInsert)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeBottomUpInsert)
(benchmark::State& state) {
  RBTree<int> tree;
  BuildTree(state, tree);
  int element[batch_size];
  for (auto _ : state) {
    state.PauseTiming();
    RandomElement(state, element, batch_size);
    for (int i = 0; i < batch_size; ++i) {
      state.ResumeTiming();
      tree.BottomUpInsert(test[i]);
      state.PauseTiming();
    }
    for (int i = 0; i < batch_size; ++i) {
      tree.BottomUpDelete(element[i]);
    }
  }
}
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeBottomUpInsert)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeTopDownInsert)
(benchmark::State& state) {
  RBTree<int> tree;
  BuildTree(state, tree);
  int element[batch_size];
  for (auto _ : state) {
    state.PauseTiming();
    RandomElement(state, element, batch_size);
    for (int i = 0; i < batch_size; ++i) {
      state.ResumeTiming();
      tree.TopDownInsert(test[i]);
      state.PauseTiming();
    }
    for (int i = 0; i < batch_size; ++i) {
      tree.TopDownDelete(element[i]);
    }
  }
}
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeTopDownInsert)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeSTLInsert)
(benchmark::State& state) {
  std::set<int> tree;
  BuildTree(state, tree);

  int element[batch_size];
  for (auto _ : state) {
    state.PauseTiming();
    RandomElement(state, element, batch_size);
    for (int i = 0; i < batch_size; ++i) {
      state.ResumeTiming();
      tree.erase(test[i]);
      state.PauseTiming();
    }
    for (int i = 0; i < batch_size; ++i) {
      tree.insert(element[i]);
    }
  }
}
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeSTLInsert)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeStandardDelete)
(benchmark::State& state) {
  RBTreeStandard<int> tree;
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
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeStandardDelete)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeStandardLinkDelete)
(benchmark::State& state) {
  RBTreeStandardLink<int> tree;
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
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeStandardLinkDelete)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeDelete)
(benchmark::State& state) {
  RBTree<int> tree;
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
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeDelete)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeBottomUpDelete)
(benchmark::State& state) {
  RBTree<int> tree;
  BuildTree(state, tree);
  int element[batch_size];
  for (auto _ : state) {
    state.PauseTiming();
    RandomElement(state, element, batch_size, true);
    for (int i = 0; i < batch_size; ++i) {
      state.ResumeTiming();
      tree.BottomUpDelete(element[i]);
      state.PauseTiming();
    }
    for (int i = 0; i < batch_size; ++i) {
      tree.BottomUpInsert(test[i]);
    }
  }
}
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeBottomUpDelete)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeTopDownDelete)
(benchmark::State& state) {
  RBTree<int> tree;
  BuildTree(state, tree);
  int element[batch_size];
  for (auto _ : state) {
    state.PauseTiming();
    RandomElement(state, element, batch_size, true);
    for (int i = 0; i < batch_size; ++i) {
      state.ResumeTiming();
      tree.TopDownDelete(element[i]);
      state.PauseTiming();
    }
    for (int i = 0; i < batch_size; ++i) {
      tree.TopDownInsert(test[i]);
    }
  }
}
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeTopDownDelete)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeSTLDelete)
(benchmark::State& state) {
  std::set<int> tree;
  BuildTree(state, tree);
  int element[batch_size];
  for (auto _ : state) {
    state.PauseTiming();
    RandomElement(state, element, batch_size, true);
    for (int i = 0; i < batch_size; ++i) {
      state.ResumeTiming();
      tree.erase(element[i]);
      state.PauseTiming();
    }
    for (int i = 0; i < batch_size; ++i) {
      tree.insert(test[i]);
    }
  }
}
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeSTLDelete)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

}  // namespace

BENCHMARK_MAIN();
