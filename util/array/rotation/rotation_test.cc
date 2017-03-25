#include "rotation.h"

#include <algorithm>

#include "gtest/gtest.h"

namespace {

class RotationTest : public ::testing::Test {
 protected:
  static void SetUpTestCase() {
    for (int i = 1; i < cases; ++i) {
      shift[i] = shift[i - 1] * m;
    }
  }

  void SetUp() override {
    for (int i = 0; i < size; ++i) {
      test[i] = i;
    }
  }

  static constexpr int size = 2000000;
  static constexpr int m = 7;
  static constexpr int cases = 8;
  static int shift[cases];
  int test[size];
};

int RotationTest::shift[cases] = {1};

TEST_F(RotationTest, ValidateJugglingBently) {
  for (int i = 0; i < cases; ++i) {
    int temp[size];
    std::copy(test, test + size, temp);
    JugglingBentley(temp, size, shift[i]);
    for (int j = 0; j < size; ++j) {
      ASSERT_EQ(temp[j], (j + shift[i]) % size);
    }
  }
}

TEST_F(RotationTest, ValidateJugglingShene) {
  for (int i = 0; i < cases; ++i) {
    int temp[size];
    std::copy(test, test + size, temp);
    JugglingShene(temp, size, shift[i]);
    for (int j = 0; j < size; ++j) ASSERT_EQ(temp[j], (j + shift[i]) % size);
  }
}

TEST_F(RotationTest, ValidateRotateReverse) {
  for (int i = 0; i < cases; ++i) {
    int temp[size];
    std::copy(test, test + size, temp);
    RotateReverse(temp, size, shift[i]);
    for (int j = 0; j < size; ++j) {
      ASSERT_EQ(temp[j], (j + shift[i]) % size);
    }
  }
}

TEST_F(RotationTest, ValidateBlockSwapShene) {
  for (int i = 0; i < cases; ++i) {
    int temp[size];
    std::copy(test, test + size, temp);
    BlockSwapShene(temp, size, shift[i]);
    for (int j = 0; j < size; ++j) {
      ASSERT_EQ(temp[j], (j + shift[i]) % size);
    }
  }
}

TEST_F(RotationTest, ValidateBlockSwapGries) {
  for (int i = 0; i < cases; ++i) {
    int temp[size];
    std::copy(test, test + size, temp);
    BlockSwapGries(temp, size, shift[i]);
    for (int j = 0; j < size; ++j) {
      ASSERT_EQ(temp[j], (j + shift[i]) % size);
    }
  }
}

}  //  namespace
