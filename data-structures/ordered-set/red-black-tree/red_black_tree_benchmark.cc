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
constexpr int max_size = 1 << 20;
constexpr int multiplier = 4;
constexpr int batch_size = 10;
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

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeStandardMix)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    RBTreeStandard<int> tree;
    BuildTree(state, tree);
    int insert[batch_size];
    int removal[batch_size];
    RandomElement(state, insert, removal);
    state.ResumeTiming();
    for (int i = 0; i < batch_size; ++i) {
      tree.Delete(removal[i]);
    }
    for (int i = 0; i < batch_size; ++i) {
      tree.Insert(insert[i]);
    }
  }
}
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeStandardMix)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeStandardLinkMix)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    RBTreeStandardLink<int> tree;
    BuildTree(state, tree);
    int insert[batch_size];
    int removal[batch_size];
    RandomElement(state, insert, removal);
    state.ResumeTiming();
    for (int i = 0; i < batch_size; ++i) {
      tree.Delete(removal[i]);
    }
    for (int i = 0; i < batch_size; ++i) {
      tree.Insert(insert[i]);
    }
  }
}
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeStandardLinkMix)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeMix)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    RBTree<int> tree;
    BuildTree(state, tree);
    int insert[batch_size];
    int removal[batch_size];
    RandomElement(state, insert, removal);
    state.ResumeTiming();
    for (int i = 0; i < batch_size; ++i) {
      tree.Delete(removal[i]);
    }
    for (int i = 0; i < batch_size; ++i) {
      tree.Insert(insert[i]);
    }
  }
}
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeMix)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeBottomUpMix)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    RBTree<int> tree;
    BuildTree(state, tree);
    int insert[batch_size];
    int removal[batch_size];
    RandomElement(state, insert, removal);
    state.ResumeTiming();
    for (int i = 0; i < batch_size; ++i) {
      tree.BottomUpDelete(removal[i]);
    }
    for (int i = 0; i < batch_size; ++i) {
      tree.BottomUpInsert(insert[i]);
    }
  }
}
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeBottomUpMix)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeTopDownMix)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    RBTree<int> tree;
    BuildTree(state, tree);
    int insert[batch_size];
    int removal[batch_size];
    RandomElement(state, insert, removal);
    state.ResumeTiming();
    for (int i = 0; i < batch_size; ++i) {
      tree.TopDownDelete(removal[i]);
    }
    for (int i = 0; i < batch_size; ++i) {
      tree.TopDownInsert(insert[i]);
    }
  }
}
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeTopDownMix)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

BENCHMARK_DEFINE_F(RBTreeBenchmark, RBTreeSTLMix)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    std::set<int> tree;
    BuildTree(state, tree);
    int insert[batch_size];
    int removal[batch_size];
    RandomElement(state, insert, removal);
    state.ResumeTiming();
    for (int i = 0; i < batch_size; ++i) {
      tree.insert(removal[i]);
    }
    for (int i = 0; i < batch_size; ++i) {
      tree.erase(insert[i]);
    }
  }
}
BENCHMARK_REGISTER_F(RBTreeBenchmark, RBTreeSTLMix)
    ->RangeMultiplier(multiplier)
    ->Range(min_size, max_size);

}  // namespace

BENCHMARK_MAIN();
