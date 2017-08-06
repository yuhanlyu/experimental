#include "weight_balanced_tree.h"

#include <algorithm>
#include <random>
#include <set>
#include <unordered_map>
#include <vector>

#include "../binary-search-tree-common/binary_search_tree_common.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace {

using testing::ElementsAreArray;

constexpr int max_test_size = 7;

TEST(WeightBalancedTree, Insert) {
  for (int size = 1; size <= max_test_size; ++size) {
    std::vector<int> expected_result;
    for (int i = 0; i < size; ++i) expected_result.push_back(i + 1);
    std::vector<int> inserted_elements(expected_result);
    do {
      WeightBalancedTree<int> tree;
      for (int value : inserted_elements) {
        tree.Insert(value);
        EXPECT_TRUE(tree.IsBalanced());
      }
      std::vector<int> actual_result;
      tree.InorderTraverse(actual_result);
      EXPECT_THAT(actual_result, ElementsAreArray(expected_result));
      for (int i = 0; i < size; ++i) EXPECT_EQ(i, tree.rank(i + 1));
    } while (std::next_permutation(inserted_elements.begin(),
                                   inserted_elements.end()));
  }
}

TEST(WeightBalancedTree, InsertRandom) {
  int sizes[] = {10, 100, 200, 500, 1000, 2000};
  for (int size : sizes) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<int> expected_result;
    for (int i = 0; i < size; ++i) expected_result.push_back(i + 1);
    std::vector<int> inserted_elements(expected_result);
    std::shuffle(inserted_elements.begin(), inserted_elements.end(), g);
    WeightBalancedTree<int> tree;
    for (int value : inserted_elements) {
      tree.Insert(value);
      EXPECT_TRUE(tree.IsBalanced());
    }
    std::vector<int> actual_result;
    tree.InorderTraverse(actual_result);
    EXPECT_THAT(actual_result, ElementsAreArray(expected_result));
    for (int i = 0; i < size; ++i) EXPECT_EQ(i, tree.rank(i + 1));
  }
}

TEST(WeightBalancedTree, Delete) {
  for (int size = 1; size <= max_test_size; ++size) {
    std::vector<int> inserted_elements;
    for (int i = 0; i < size; ++i) inserted_elements.push_back(i + 1);
    std::vector<int> temp(inserted_elements);
    do {
      WeightBalancedTree<int> tree;
      for (int value : temp) tree.Insert(value);
      tree.Delete(temp[0]);
      EXPECT_TRUE(tree.IsBalanced());
      std::vector<int> expected_result(temp);
      expected_result.erase(expected_result.begin());
      std::sort(expected_result.begin(), expected_result.end());
      std::vector<int> actual_result;
      tree.InorderTraverse(actual_result);
      EXPECT_THAT(actual_result, ElementsAreArray(expected_result));
      for (int i = 0; i < expected_result.size(); ++i)
        EXPECT_EQ(i, tree.rank(expected_result[i]));
    } while (std::next_permutation(temp.begin(), temp.end()));
  }
}

TEST(WeightBalancedTree, DeleteRandom) {
  int sizes[] = {10, 100, 200, 500, 1000, 2000, 5000};
  for (int size : sizes) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<int> inserted_elements;
    for (int i = 0; i < size; ++i) inserted_elements.push_back(i + 1);
    std::shuffle(inserted_elements.begin(), inserted_elements.end(), g);
    std::vector<int> temp(inserted_elements);
    WeightBalancedTree<int> tree;
    for (int value : inserted_elements) tree.Insert(value);
    for (int i = 0; i < size / 10; ++i) {
      tree.Delete(inserted_elements[i]);
      EXPECT_TRUE(tree.IsBalanced());
    }
    temp.erase(temp.begin(), temp.begin() + size / 10);
    std::vector<int> expected_result(temp);
    std::sort(expected_result.begin(), expected_result.end());
    std::vector<int> actual_result;
    tree.InorderTraverse(actual_result);
    EXPECT_THAT(actual_result, ElementsAreArray(expected_result));
    for (int i = 0; i < expected_result.size(); ++i)
      EXPECT_EQ(i, tree.rank(expected_result[i]));
  }
}

TEST(WeightBalancedTree, Mix) {
  int sizes[] = {10, 100, 200, 500};
  for (int size : sizes) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<int> elements;
    for (int i = 0; i < size; ++i) elements.insert(elements.end(), 2, i + 1);
    std::shuffle(elements.begin(), elements.end(), g);
    WeightBalancedTree<int> tree;
    std::set<int> expected_tree;
    std::unordered_map<int, int> count;
    for (int value : elements) {
      switch (++count[value]) {
        case 1:
          expected_tree.insert(value);
          tree.Insert(value);
          break;
        case 2:
          expected_tree.erase(value);
          tree.Delete(value);
          break;
      }
      EXPECT_TRUE(tree.IsBalanced());
      std::vector<int> expected_result(expected_tree.begin(),
                                       expected_tree.end());
      std::vector<int> actual_result;
      tree.InorderTraverse(actual_result);
      EXPECT_THAT(actual_result, ElementsAreArray(expected_result));
      for (int i = 0; i < expected_result.size(); ++i)
        EXPECT_EQ(i, tree.rank(expected_result[i]));
    }
  }
}

}  // namespace
