#include "binary_search.h"

#include <algorithm>
#include <functional>

#include "gtest/gtest.h"

namespace {

class SearchTest : public ::testing::Test {
 protected:
  void Test(std::function<const int*(const int*, const int*, int)> search) {
    for (unsigned long i = 0; i < sizeof(sizes) / sizeof(sizes[0]); ++i) {
      int* test = new int[sizes[i]];
      for (unsigned long j = 0; j < sizes[i]; ++j) {
        test[j] = 2 * j + 1;
      }
      Test(search, test, sizes[i], 0, 2 * sizes[i] + 1);
      for (unsigned long j = 0; j < sizes[i]; ++j) {
        test[j] = j / 2;
      }
      Test(search, test, sizes[i], 0, sizes[i] / 2 + 1);
      delete[] test;
    }
  }
  void Test(std::function<const int*(const int*, const int*, int)> search,
            int* array, int size, int begin, int end) {
    for (int i = begin; i < end; ++i) {
      EXPECT_EQ(search(array, array + size, i),
                std::lower_bound(array, array + size, i));
    }
  }
  static constexpr unsigned long sizes[] = {0,  1,   2,   3,   5,    7,   11,
                                            13, 17,  19,  4,   8,    16,  32,
                                            64, 128, 256, 512, 1024, 2048};
};

TEST_F(SearchTest, ValidateBinarySearch) {
  Test([](const int* first, const int* last, int x) {
    return BinarySearch(first, last, x);
  });
}

TEST_F(SearchTest, ValidateBinarySearch1) {
  Test([](const int* first, const int* last, int x) {
    return BinarySearch1(first, last, x);
  });
}

TEST_F(SearchTest, ValidateBinarySearch2) {
  Test([](const int* first, const int* last, int x) {
    return BinarySearch2(first, last, x);
  });
}

TEST_F(SearchTest, ValidateBinarySearch3) {
  Test([](const int* first, const int* last, int x) {
    return BinarySearch3(first, last, x);
  });
}

TEST_F(SearchTest, ValidateShar1) {
  Test([](const int* first, const int* last, int x) {
    return Shar1(first, last, x);
  });
}

TEST_F(SearchTest, ValidateShar2) {
  Test([](const int* first, const int* last, int x) {
    return Shar2(first, last, x);
  });
}

TEST_F(SearchTest, ValidateSkewedBinarySearch) {
  Test([](const int* first, const int* last, int x) {
    return SkewedBinarySearch(first, last, x);
  });
}

TEST_F(SearchTest, ValidateSharUnroll) {
  Test([](const int* first, const int* last, int x) {
    return SharUnroll(first, last, x);
  });
}

}  // namespace
