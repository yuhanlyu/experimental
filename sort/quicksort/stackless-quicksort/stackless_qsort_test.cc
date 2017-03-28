#include "stackless_qsort.h"

#include <algorithm>
#include <limits>
#include <random>

#include "gtest/gtest.h"

namespace {

constexpr int shift = 2;

// For all sizes from 1 to 10, test all permutations of integers [1, .., size].
TEST(QSortTest, SmallSize) {
  const int max_size = 10;
  int test[max_size + shift + 1];
  int temp[max_size + shift + 1];
  int answer[max_size + shift + 1];
  for (int size = 1; size <= 10; ++size) {
    test[0] = test[1] = test[size + shift] = 0;
    for (int i = shift; i < shift + size; ++i) {
      test[i] = i;
    }
    do {
      std::copy(test + shift, test + shift + size, temp + shift);
      StacklessQSort(temp, size + shift);

      std::copy(test + shift, test + shift + size, answer + shift);
      std::sort(answer + shift, answer + shift + size);

      for (int i = shift; i < shift + size; ++i) {
        ASSERT_EQ(temp[i], answer[i]);
      }
    } while (std::next_permutation(test + shift, test + shift + size));
  }
}

TEST(QSortTest, StacklessQSort) {
  const int size = 1 << 16;
  int test[size + shift + 1];
  int temp[size + shift + 1];
  int answer[size + shift + 1];

  std::default_random_engine generator_;
  std::uniform_int_distribution<int> distribution_{0, size};

  test[0] = test[1] = test[size] = 0;
  for (int i = shift; i < shift + size; ++i) {
    test[i] = distribution_(generator_);
  }
  std::copy(test + shift, test + shift + size, temp + shift);
  StacklessQSort(temp, size + shift);

  std::copy(test + shift, test + shift + size, answer + shift);
  std::sort(answer + shift, answer + shift + size);

  for (int i = shift; i < shift + size; ++i) {
    EXPECT_EQ(temp[i], answer[i]);
  }
}

}  // namespace
