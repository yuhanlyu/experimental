#include "binary_search_tree_common.h"

#include <vector>

#include "../binary-search-tree/binary_search_tree.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace {

using testing::ElementsAreArray;

constexpr int max_test_size = 7;

TEST(BinarySearchTreeCommon, InorderTraverse) {
  for (int size = 1; size <= max_test_size; ++size) {
    std::vector<int> expected_result;
    for (int i = 0; i < size; ++i) expected_result.push_back(i + 1);
    std::vector<int> inserted_elements(expected_result);
    do {
      BinarySearchTree<int> tree;
      for (int value : inserted_elements) ASSERT_TRUE(tree.Insert(value));
      std::vector<int> actual_result;
      tree.InorderTraverse(actual_result);
      EXPECT_THAT(actual_result, ElementsAreArray(expected_result));
    } while (std::next_permutation(inserted_elements.begin(),
                                   inserted_elements.end()));
  }
}

TEST(BinarySearchTreeCommon, InorderTraverseArray) {
  for (int size = 1; size <= max_test_size; ++size) {
    std::vector<int> expected_result;
    for (int i = 0; i < size; ++i) expected_result.push_back(i + 1);
    std::vector<int> inserted_elements(expected_result);
    do {
      BinarySearchTree<int> tree;
      for (int value : inserted_elements) ASSERT_TRUE(tree.Insert(value));
      int actual_result[size];
      InorderTraverse(tree.root(), actual_result);
      EXPECT_THAT(expected_result, ElementsAreArray(actual_result, size));
    } while (std::next_permutation(inserted_elements.begin(),
                                   inserted_elements.end()));
  }
}

TEST(BinarySearchTreeCommon, InorderTraverseMorris) {
  for (int size = 1; size <= max_test_size; ++size) {
    std::vector<int> expected_result;
    for (int i = 0; i < size; ++i) expected_result.push_back(i + 1);
    std::vector<int> inserted_elements(expected_result);
    do {
      BinarySearchTree<int> tree;
      for (int value : inserted_elements) ASSERT_TRUE(tree.Insert(value));
      int actual_result[size];
      InorderTraverseMorris(tree.root(), actual_result);
      EXPECT_THAT(expected_result, ElementsAreArray(actual_result, size));
    } while (std::next_permutation(inserted_elements.begin(),
                                   inserted_elements.end()));
  }
}

TEST(BinarySearchTreeCommon, PreorderTraverse) {
  for (int size = 1; size <= max_test_size; ++size) {
    std::vector<int> inserted_elements;
    for (int i = 0; i < size; ++i) inserted_elements.push_back(i + 1);
    do {
      BinarySearchTree<int> tree;
      for (int value : inserted_elements) ASSERT_TRUE(tree.Insert(value));
      std::vector<int> actual_result;
      PreorderTraverse(tree.root(), actual_result);
      std::vector<int> expected_result;
      PreorderTraverseRec(tree.root(), expected_result);
      EXPECT_THAT(actual_result, ElementsAreArray(expected_result));
    } while (std::next_permutation(inserted_elements.begin(),
                                   inserted_elements.end()));
  }
}

TEST(BinarySearchTreeCommon, PreorderTraverseArray) {
  for (int size = 1; size <= max_test_size; ++size) {
    std::vector<int> inserted_elements;
    for (int i = 0; i < size; ++i) inserted_elements.push_back(i + 1);
    do {
      BinarySearchTree<int> tree;
      for (int value : inserted_elements) ASSERT_TRUE(tree.Insert(value));
      int actual_result[size];
      PreorderTraverse(tree.root(), actual_result);
      std::vector<int> expected_result;
      PreorderTraverseRec(tree.root(), expected_result);
      EXPECT_THAT(expected_result, ElementsAreArray(actual_result, size));
    } while (std::next_permutation(inserted_elements.begin(),
                                   inserted_elements.end()));
  }
}

TEST(BinarySearchTreeCommon, PreorderTraverseMorris) {
  for (int size = 1; size <= max_test_size; ++size) {
    std::vector<int> inserted_elements;
    for (int i = 0; i < size; ++i) inserted_elements.push_back(i + 1);
    do {
      BinarySearchTree<int> tree;
      for (int value : inserted_elements) ASSERT_TRUE(tree.Insert(value));
      int actual_result[size];
      PreorderTraverseMorris(tree.root(), actual_result);
      std::vector<int> expected_result;
      PreorderTraverseRec(tree.root(), expected_result);
      EXPECT_THAT(expected_result, ElementsAreArray(actual_result, size));
    } while (std::next_permutation(inserted_elements.begin(),
                                   inserted_elements.end()));
  }
}

TEST(BinarySearchTreeCommon, PostorderTraverse) {
  for (int size = 1; size <= max_test_size; ++size) {
    std::vector<int> inserted_elements;
    for (int i = 0; i < size; ++i) inserted_elements.push_back(i + 1);
    do {
      BinarySearchTree<int> tree;
      for (int value : inserted_elements) ASSERT_TRUE(tree.Insert(value));
      std::vector<int> actual_result;
      PostorderTraverse(tree.root(), actual_result);
      std::vector<int> expected_result;
      PostorderTraverseRec(tree.root(), expected_result);
      EXPECT_THAT(actual_result, ElementsAreArray(expected_result));
    } while (std::next_permutation(inserted_elements.begin(),
                                   inserted_elements.end()));
  }
}

TEST(BinarySearchTreeCommon, PostorderTraverseArray) {
  for (int size = 1; size <= max_test_size; ++size) {
    std::vector<int> inserted_elements;
    for (int i = 0; i < size; ++i) inserted_elements.push_back(i + 1);
    do {
      BinarySearchTree<int> tree;
      for (int value : inserted_elements) ASSERT_TRUE(tree.Insert(value));
      int actual_result[size];
      PostorderTraverse(tree.root(), actual_result);
      std::vector<int> expected_result;
      PostorderTraverseRec(tree.root(), expected_result);
      EXPECT_THAT(expected_result, ElementsAreArray(actual_result, size));
    } while (std::next_permutation(inserted_elements.begin(),
                                   inserted_elements.end()));
  }
}

TEST(BinarySearchTreeCommon, PostorderTraverseMorris) {
  for (int size = 1; size <= max_test_size; ++size) {
    std::vector<int> inserted_elements;
    for (int i = 0; i < size; ++i) inserted_elements.push_back(i + 1);
    do {
      BinarySearchTree<int> tree;
      for (int value : inserted_elements) ASSERT_TRUE(tree.Insert(value));
      int actual_result[size];
      PostorderTraverseMorris(tree.root(), actual_result);
      std::vector<int> expected_result;
      PostorderTraverseRec(tree.root(), expected_result);
      EXPECT_THAT(expected_result, ElementsAreArray(actual_result, size));
    } while (std::next_permutation(inserted_elements.begin(),
                                   inserted_elements.end()));
  }
}

TEST(BinarySearchTreeCommon, LevelOrderTraverse) {
  for (int size = 1; size <= max_test_size; ++size) {
    std::vector<int> inserted_elements;
    for (int i = 0; i < size; ++i) inserted_elements.push_back(i + 1);
    do {
      BinarySearchTree<int> tree;
      for (int value : inserted_elements) ASSERT_TRUE(tree.Insert(value));
      std::vector<int> actual_result;
      LevelOrderTraverse(tree.root(), actual_result);
      std::vector<int> expected_result;
      LevelOrderTraverseQueue(tree.root(), expected_result);
      EXPECT_THAT(actual_result, ElementsAreArray(expected_result));
    } while (std::next_permutation(inserted_elements.begin(),
                                   inserted_elements.end()));
  }
}

}  // namespace
