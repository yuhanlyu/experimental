#include "rotation.h"

#include "benchmark/benchmark_api.h"

namespace {

class Rotation : public benchmark::Fixture {
 public:
  void SetUp(const ::benchmark::State& state) override {
    for (int i = 0; i < range; ++i) {
      temp[i] = i;
    }
  }

  static constexpr int range = 1 << 20;
  static constexpr int multiplier = 6561;
  int temp[range];
};

BENCHMARK_DEFINE_F(Rotation, JugglingBentley)
(benchmark::State& state) {
  while (state.KeepRunning()) {
    JugglingBentley(temp, range, state.range(0));
  }
}
BENCHMARK_REGISTER_F(Rotation, JugglingBentley)
    ->RangeMultiplier(Rotation::multiplier)
    ->Range(1, Rotation::range - 1);

BENCHMARK_DEFINE_F(Rotation, JugglingShene)(benchmark::State& state) {
  while (state.KeepRunning()) {
    JugglingShene(temp, range, state.range(0));
  }
}
BENCHMARK_REGISTER_F(Rotation, JugglingShene)
    ->RangeMultiplier(Rotation::multiplier)
    ->Range(1, Rotation::range - 1);

BENCHMARK_DEFINE_F(Rotation, RotateReverse)(benchmark::State& state) {
  while (state.KeepRunning()) {
    RotateReverse(temp, range, state.range(0));
  }
}
BENCHMARK_REGISTER_F(Rotation, RotateReverse)
    ->RangeMultiplier(Rotation::multiplier)
    ->Range(1, Rotation::range - 1);

BENCHMARK_DEFINE_F(Rotation, BlockSwapShene)(benchmark::State& state) {
  while (state.KeepRunning()) {
    BlockSwapShene(temp, range, state.range(0));
  }
}
BENCHMARK_REGISTER_F(Rotation, BlockSwapShene)
    ->RangeMultiplier(Rotation::multiplier)
    ->Range(1, Rotation::range - 1);

BENCHMARK_DEFINE_F(Rotation, BlockSwapGries)(benchmark::State& state) {
  while (state.KeepRunning()) {
    BlockSwapGries(temp, range, state.range(0));
  }
}
BENCHMARK_REGISTER_F(Rotation, BlockSwapGries)
    ->RangeMultiplier(Rotation::multiplier)
    ->Range(1, Rotation::range - 1);

}  // namespace

BENCHMARK_MAIN()
