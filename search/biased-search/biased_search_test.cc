#include "biased_search.h"

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

TEST_F(SearchTest, ValidateBinarySearch) {
  for (int i = 0; i <= 2 * size; ++i) {
    EXPECT_EQ(BinarySearch(test, test + size, i), test + i / 2);
  }
}

TEST_F(SearchTest, ValidateBiasedBinarySearch) {
  for (int i = 0; i <= 2 * size; ++i) {
    EXPECT_EQ(BiasedBinarySearch(test, test + size, i), test + i / 2);
  }
}

}  // namespace
