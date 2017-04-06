#include "binary_search.h"

#include "gtest/gtest.h"

namespace {

class SearchTest : public ::testing::Test {
 protected:
  void SetUp() override {
    for (int i = 0; i < size; ++i) {
      test[i] = 2 * i + 1;
    }
  }
  static constexpr int size = 1 << 20;
  int test[size];
};

TEST_F(SearchTest, ValidateBranchfreeBinarySearch) {
  for (int i = 0; i <= 2 * size; ++i) {
    EXPECT_EQ(BranchfreeBinarySearch(test, test + size, i), test + i / 2);
  }
}

TEST_F(SearchTest, ValidateSkewedBinarySearch) {
  for (int i = 0; i <= 2 * size; ++i) {
    EXPECT_EQ(SkewedBinarySearch(test, test + size, i), test + i / 2);
  }
}

}  // namespace
