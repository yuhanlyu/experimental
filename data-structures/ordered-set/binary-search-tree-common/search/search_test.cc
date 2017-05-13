#include "search.h"

#include "../../binary-search-tree/binary_search_tree.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace {

constexpr int max_test_size = 7;

TEST(BinarySearchTreeSearch, NaiveSearch) {
  for (int size = 1; size <= max_test_size; ++size) {
    BinarySearchTree<int> tree;
    for (int i = 0; i < size; ++i) ASSERT_TRUE(tree.Insert(2 * i + 1));
    for (int i = 0; i <= 2 * size; ++i) {
      if (i % 2 == 0)
        EXPECT_EQ(nullptr, Search(tree.root(), i));
      else
        EXPECT_EQ(i, *Search(tree.root(), i));
    }
  }
}

TEST(BinarySearchTreeSearch, FastSearch) {
  for (int size = 1; size <= max_test_size; ++size) {
    BinarySearchTree<int> tree;
    for (int i = 0; i < size; ++i) ASSERT_TRUE(tree.Insert(2 * i + 1));
    for (int i = 0; i <= 2 * size; ++i) {
      if (i % 2 == 0)
        EXPECT_EQ(nullptr, FastSearch(tree.root(), i));
      else
        EXPECT_EQ(i, *FastSearch(tree.root(), i));
    }
  }
}

}  // namespace
