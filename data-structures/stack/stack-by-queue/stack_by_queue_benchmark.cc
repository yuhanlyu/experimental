#include "stack_by_queue.h"

#include <limits>
#include <random>
#include <stack>

#include "benchmark/benchmark_api.h"

namespace {

static void BM_StackByQueuePush(benchmark::State& state) {
  Stack<int> stack;
  while (state.KeepRunning()) {
    stack.push(0);
  }
}
BENCHMARK(BM_StackByQueuePush);

static void BM_STLStackPush(benchmark::State& state) {
  std::stack<int> stack;
  while (state.KeepRunning()) {
    stack.push(0);
  }
}
BENCHMARK(BM_STLStackPush);

static void BM_StackByQueueMix(benchmark::State& state) {
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution{
      0, std::numeric_limits<int>::max()};
  Stack<int> stack;
  while (state.KeepRunning()) {
    int r = distribution(generator);
    if (r % 3 == 0 || r % 3 == 1) {
      stack.push(r);
    } else if (!stack.empty()) {
      stack.pop();
    }
  }
}
BENCHMARK(BM_StackByQueueMix);

static void BM_STLStackMix(benchmark::State& state) {
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution{
      0, std::numeric_limits<int>::max()};
  std::stack<int> stack;
  while (state.KeepRunning()) {
    int r = distribution(generator);
    if (r % 3 == 0 || r % 3 == 1) {
      stack.push(r);
    } else if (!stack.empty()) {
      stack.pop();
    }
  }
}
BENCHMARK(BM_STLStackMix);

}  // namespace

BENCHMARK_MAIN()
