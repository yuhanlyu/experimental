#include "rebalance.h"

#include <vector>

#include "../../binary-search-tree/binary_search_tree.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace {

using testing::ElementsAreArray;

constexpr int max_test_size = 7;

TEST(BinarySearchTreeRebalance, NaiveRebalance) {
  for (int size = 1; size <= max_test_size; ++size) {
    std::vector<int> expected_result;
    for (int i = 0; i < size; ++i) expected_result.push_back(i + 1);
    std::vector<int> inserted_elements(expected_result);
    do {
      BinarySearchTree<int> tree;
      for (int value : inserted_elements) ASSERT_TRUE(tree.Insert(value));
      std::vector<int> actual_result;
      NaiveRebalance(tree.root());
      tree.InorderTraverse(actual_result);
      EXPECT_THAT(actual_result, ElementsAreArray(expected_result));
    } while (std::next_permutation(inserted_elements.begin(),
                                   inserted_elements.end()));
  }
}

TEST(BinarySearchTreeRebalance, RebalanceByFlatten) {
  for (int size = 1; size <= max_test_size; ++size) {
    std::vector<int> expected_result;
    for (int i = 0; i < size; ++i) expected_result.push_back(i + 1);
    std::vector<int> inserted_elements(expected_result);
    do {
      BinarySearchTree<int> tree;
      for (int value : inserted_elements) ASSERT_TRUE(tree.Insert(value));
      std::vector<int> actual_result;
      RebalanceByFlatten(tree.root());
      tree.InorderTraverse(actual_result);
      EXPECT_THAT(actual_result, ElementsAreArray(expected_result));
    } while (std::next_permutation(inserted_elements.begin(),
                                   inserted_elements.end()));
  }
}

TEST(BinarySearchTreeRebalance, RebalanceDSW) {
  for (int size = 1; size <= max_test_size; ++size) {
    std::vector<int> expected_result;
    for (int i = 0; i < size; ++i) expected_result.push_back(i + 1);
    std::vector<int> inserted_elements(expected_result);
    do {
      BinarySearchTree<int> tree;
      for (int value : inserted_elements) ASSERT_TRUE(tree.Insert(value));
      std::vector<int> actual_result;
      RebalanceDSW(tree.root());
      tree.InorderTraverse(actual_result);
      EXPECT_THAT(actual_result, ElementsAreArray(expected_result));
    } while (std::next_permutation(inserted_elements.begin(),
                                   inserted_elements.end()));
  }
}

TEST(BinarySearchTreeRebalance, RebalanceDay) {
  for (int size = 1; size <= max_test_size; ++size) {
    std::vector<int> expected_result;
    for (int i = 0; i < size; ++i) expected_result.push_back(i + 1);
    std::vector<int> inserted_elements(expected_result);
    do {
      BinarySearchTree<int> tree;
      for (int value : inserted_elements) ASSERT_TRUE(tree.Insert(value));
      std::vector<int> actual_result;
      RebalanceDay(tree.root());
      tree.InorderTraverse(actual_result);
      EXPECT_THAT(actual_result, ElementsAreArray(expected_result));
    } while (std::next_permutation(inserted_elements.begin(),
                                   inserted_elements.end()));
  }
}

}  // namespace
