#include "stackless_qsort.h"

#include <algorithm>
#include <cstdlib>
#include <random>

#include "benchmark/benchmark_api.h"

namespace {

class QSortBenchmark : public benchmark::Fixture {
 public:
  void SetUp(const ::benchmark::State& state) override {
    generator.seed();
    test[0] = test[1] = test[shift + size] = 0;
    for (int i = shift; i < shift + size; ++i) {
      test[i] = distribution(generator);
    }
  }

  static constexpr int shift = 2;
  static constexpr int size = 1 << 18;
  static constexpr int max = 2 * size;
  std::uniform_int_distribution<int> distribution{0, max};
  std::default_random_engine generator;
  int test[size + shift + 1];
};

BENCHMARK_F(QSortBenchmark, StacklessQSort)(benchmark::State& state) {
  while (state.KeepRunning()) {
    int temp[shift + size + 1];
    std::copy(test + shift, test + shift + size, temp + shift);
    StacklessQSort(temp, shift + size);
  }
}

BENCHMARK_F(QSortBenchmark, STLQSort)(benchmark::State& state) {
  while (state.KeepRunning()) {
    int temp[shift + size + 1];
    std::copy(test + shift, test + shift + size, temp + shift);
    std::sort(temp + shift, temp + shift + size);
  }
}

BENCHMARK_F(QSortBenchmark, STLStableSort)(benchmark::State& state) {
  while (state.KeepRunning()) {
    int temp[shift + size + 1];
    std::copy(test + shift, test + shift + size, temp + shift);
    std::stable_sort(temp + shift, temp + shift + size);
  }
}

int compare(const void* p, const void* q) {
  int x = *reinterpret_cast<const int*>(p);
  int y = *reinterpret_cast<const int*>(q);
  return (x == y) ? 0 : ((x < y) ? -1 : 1);
}

BENCHMARK_F(QSortBenchmark, QSort)(benchmark::State& state) {
  while (state.KeepRunning()) {
    int temp[shift + size + 1];
    std::copy(test + shift, test + shift + size, temp + shift);
    qsort(temp + shift, size, sizeof(int), compare);
  }
}

}  // namespace

BENCHMARK_MAIN()
