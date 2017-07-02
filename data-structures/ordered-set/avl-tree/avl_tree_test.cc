#include "avl_tree.h"

#include <algorithm>
#include <vector>

#include "../binary-search-tree-common/binary_search_tree_common.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace {

using testing::ElementsAreArray;

constexpr int max_test_size = 7;

TEST(AVLTree, RecursiveInsert) {
  for (int size = 1; size <= max_test_size; ++size) {
    std::vector<int> expected_result;
    for (int i = 0; i < size; ++i) expected_result.push_back(i + 1);
    std::vector<int> inserted_elements(expected_result);
    do {
      AVLTree<int> tree;
      for (int value : inserted_elements) {
        EXPECT_TRUE(tree.RecursiveInsert(value));
        EXPECT_TRUE(tree.IsBalanced());
      }
      std::vector<int> actual_result;
      tree.InorderTraverse(actual_result);
      EXPECT_THAT(actual_result, ElementsAreArray(expected_result));
      for (int value : inserted_elements)
        EXPECT_FALSE(tree.RecursiveInsert(value));
    } while (std::next_permutation(inserted_elements.begin(),
                                   inserted_elements.end()));
  }
}

TEST(AVLTree, Insert) {
  for (int size = 1; size <= max_test_size; ++size) {
    std::vector<int> expected_result;
    for (int i = 0; i < size; ++i) expected_result.push_back(i + 1);
    std::vector<int> inserted_elements(expected_result);
    do {
      AVLTree<int> tree;
      for (int value : inserted_elements) {
        EXPECT_TRUE(tree.Insert(value));
        EXPECT_TRUE(tree.IsBalanced());
      }
      std::vector<int> actual_result;
      tree.InorderTraverse(actual_result);
      EXPECT_THAT(actual_result, ElementsAreArray(expected_result));
      for (int value : inserted_elements) EXPECT_FALSE(tree.Insert(value));
    } while (std::next_permutation(inserted_elements.begin(),
                                   inserted_elements.end()));
  }
}

TEST(AVLTree, Delete) {
  for (int size = 1; size <= max_test_size; ++size) {
    std::vector<int> inserted_elements;
    for (int i = 0; i < size; ++i) inserted_elements.push_back(i + 1);
    std::vector<int> temp(inserted_elements);
    do {
      AVLTree<int> tree;
      for (int value : temp) ASSERT_TRUE(tree.Insert(value));
      EXPECT_TRUE(tree.Delete(temp[0]));
      EXPECT_TRUE(tree.IsBalanced());
      std::vector<int> expected_result(temp);
      expected_result.erase(expected_result.begin());
      std::sort(expected_result.begin(), expected_result.end());
      std::vector<int> actual_result;
      tree.InorderTraverse(actual_result);
      EXPECT_THAT(actual_result, ElementsAreArray(expected_result));
      EXPECT_FALSE(tree.Delete(temp[0]));
    } while (std::next_permutation(temp.begin(), temp.end()));
  }
}

}  // namespace
