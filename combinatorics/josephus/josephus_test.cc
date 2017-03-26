#include "josephus.h"

#include "gtest/gtest.h"

namespace {

static constexpr int32_t n = 2000000;

TEST(JosephusTest, ValidateConcreteMath) {
  for (int32_t m = 2; m < n; m += 100000) {
    EXPECT_EQ(ConcreteMath(n, m), TAOCPK(n, m, n));
  }
}

TEST(JosephusTest, ValidateWoodhousea) {
  for (int32_t m = 2; m < n; m += 100000) {
    EXPECT_EQ(Woodhousea(n, m), TAOCPK(n, m, n));
  }
}

TEST(JosephusTest, ValidateGelgi) {
  for (int32_t m = 2; m < n; m += 100000) {
    EXPECT_EQ(Gelgi(n, m), TAOCPK(n, m, n));
  }
}

TEST(JosephusTest, ValidateGelgiImprove) {
  for (int32_t m = 2; m < n; m += 100000) {
    EXPECT_EQ(ImprovedGelgi(n, m), TAOCPK(n, m, n));
  }
}

TEST(JosephusTest, ValidateGelgiTAOCP) {
  for (int32_t m = 2; m < n; m += 100000) {
    EXPECT_EQ(TAOCP(n, m), TAOCPK(n, m, n));
  }
}
}  // namespace
