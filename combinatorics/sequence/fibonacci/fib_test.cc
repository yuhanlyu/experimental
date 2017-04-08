#include "fib.h"

#include "gtest/gtest.h"

namespace {

class FibonacciTest : public ::testing::Test {
 protected:
  void SetUp() override {
    for (int i = 1; i <= max; ++i) {
      ans[i] = Iterative(i);
    }
  }
  static constexpr int32_t max = 92;
  int64_t ans[max + 1];
};

TEST_F(FibonacciTest, ValidateDoubling) {
  for (int i = 1; i <= max; ++i) {
    EXPECT_EQ(ans[i], Doubling(i));
  }
}

TEST_F(FibonacciTest, ValidateTumble) {
  for (int i = 1; i <= max; ++i) {
    EXPECT_EQ(ans[i], Tumble(i));
  }
}

TEST_F(FibonacciTest, ValidateQMatrix) {
  for (int i = 1; i <= max; ++i) {
    EXPECT_EQ(ans[i], QMatrix(i));
  }
}

}  // namespace
