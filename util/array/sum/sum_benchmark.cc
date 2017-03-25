#include <functional>
#include <limits>
#include <random>
#include <valarray>

#include "benchmark/benchmark_api.h"

namespace {

constexpr int size = 1 << 24;
double test[size];

double ForLoop(double a[], int n) {
  double ans = 0.0;
  for (int i = 0; i < n; ++i) {
		ans += a[i];
	}
  return ans;
}

double UnrollLoop(double a[], int n) {
  double even = 0.0, odd = 0.0;
  for (int i = 0; i + 1 < n; i += 2) {
    even += a[i];
    odd += a[i + 1];
  }
  return even + odd + ((n % 2 == 0) ? a[n - 1] : 0.0);
}

class SumBenchmark : public benchmark::Fixture {
 public:
  void SetUp(const ::benchmark::State& state) override {
    generator.seed();
    for (int i = 0; i < state.range(0); ++i) {
      test[i] = distribution(generator);
    }
    val_array = std::valarray<double>(test, size);
  }
  std::valarray<double> val_array;
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution{
      0, std::numeric_limits<double>::max()};
};

BENCHMARK_DEFINE_F(SumBenchmark, ForLoop)(benchmark::State& state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(ForLoop(test, size));
  }
}
BENCHMARK_REGISTER_F(SumBenchmark, ForLoop)->Arg(size);

BENCHMARK_DEFINE_F(SumBenchmark, UnrollLoop)(benchmark::State& state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(UnrollLoop(test, size));
  }
}
BENCHMARK_REGISTER_F(SumBenchmark, UnrollLoop)->Arg(size);

BENCHMARK_DEFINE_F(SumBenchmark, Accumulate)(benchmark::State& state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(std::accumulate(test, test + size, 0.0));
  }
}
BENCHMARK_REGISTER_F(SumBenchmark, Accumulate)->Arg(size);

BENCHMARK_DEFINE_F(SumBenchmark, Valarray)(benchmark::State& state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(val_array.sum());
  }
}
BENCHMARK_REGISTER_F(SumBenchmark, Valarray)->Arg(size);

}  // namespace

BENCHMARK_MAIN()
