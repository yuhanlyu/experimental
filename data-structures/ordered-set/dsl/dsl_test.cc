#include "dsl.h"

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

TEST(DSL, Insert) {
  for (int size = 1; size <= max_test_size; ++size) {
    std::vector<int> expected_result;
    for (int i = 0; i < size; ++i) expected_result.push_back(i + 1);
    std::vector<int> inserted_elements(expected_result);
    do {
      DSL<int> tree;
      for (int value : inserted_elements) {
        EXPECT_TRUE(tree.Insert(value));
        EXPECT_TRUE(tree.CheckGap());
      }
      std::vector<int> actual_result;
      tree.InorderTraverse(actual_result);
      EXPECT_THAT(actual_result, ElementsAreArray(expected_result));
      for (int value : inserted_elements) {
        EXPECT_FALSE(tree.Insert(value));
        EXPECT_TRUE(tree.CheckGap());
        actual_result.clear();
        tree.InorderTraverse(actual_result);
        EXPECT_THAT(actual_result, ElementsAreArray(expected_result));
      }
    } while (std::next_permutation(inserted_elements.begin(),
                                   inserted_elements.end()));
  }
}

TEST(DSL, InsertRandom) {
  int sizes[] = {10, 100, 200, 500, 1000, 2000};
  for (int size : sizes) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<int> expected_result;
    for (int i = 0; i < size; ++i) expected_result.push_back(i + 1);
    std::vector<int> inserted_elements(expected_result);
    std::shuffle(inserted_elements.begin(), inserted_elements.end(), g);
    DSL<int> tree;
    for (int value : inserted_elements) {
      EXPECT_TRUE(tree.Insert(value));
      EXPECT_TRUE(tree.CheckGap());
    }
    std::vector<int> actual_result;
    tree.InorderTraverse(actual_result);
    EXPECT_THAT(actual_result, ElementsAreArray(expected_result));
    for (int value : inserted_elements) {
      EXPECT_FALSE(tree.Insert(value));
      EXPECT_TRUE(tree.CheckGap());
      actual_result.clear();
      tree.InorderTraverse(actual_result);
      EXPECT_THAT(actual_result, ElementsAreArray(expected_result));
    }
  }
}

TEST(DSL, Delete) {
  for (int size = 1; size <= max_test_size; ++size) {
    std::vector<int> inserted_elements;
    for (int i = 0; i < size; ++i) inserted_elements.push_back(i + 1);
    std::vector<int> temp(inserted_elements);
    do {
      DSL<int> tree;
      for (int value : temp) ASSERT_TRUE(tree.Insert(value));
      EXPECT_TRUE(tree.Delete(temp[0]));
      EXPECT_TRUE(tree.CheckGap());
      std::vector<int> expected_result(temp);
      expected_result.erase(expected_result.begin());
      std::sort(expected_result.begin(), expected_result.end());
      std::vector<int> actual_result;
      tree.InorderTraverse(actual_result);
      EXPECT_THAT(actual_result, ElementsAreArray(expected_result));
      EXPECT_FALSE(tree.Delete(temp[0]));
      EXPECT_TRUE(tree.CheckGap());
      actual_result.clear();
      tree.InorderTraverse(actual_result);
      EXPECT_THAT(actual_result, ElementsAreArray(expected_result));
    } while (std::next_permutation(temp.begin(), temp.end()));
  }
}

TEST(DSL, DeleteRandom) {
  int sizes[] = {10, 100, 200, 500, 1000, 2000, 5000};
  for (int size : sizes) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<int> inserted_elements;
    for (int i = 0; i < size; ++i) inserted_elements.push_back(i + 1);
    std::shuffle(inserted_elements.begin(), inserted_elements.end(), g);
    std::vector<int> temp(inserted_elements);
    DSL<int> tree;
    for (int value : inserted_elements) ASSERT_TRUE(tree.Insert(value));
    for (int i = 0; i < size / 10; ++i) {
      EXPECT_TRUE(tree.Delete(inserted_elements[i]));
      EXPECT_TRUE(tree.CheckGap());
    }
    temp.erase(temp.begin(), temp.begin() + size / 10);
    std::vector<int> expected_result(temp);
    std::sort(expected_result.begin(), expected_result.end());
    std::vector<int> actual_result;
    tree.InorderTraverse(actual_result);
    EXPECT_THAT(actual_result, ElementsAreArray(expected_result));
    for (int i = 0; i < size / 10; ++i) {
      EXPECT_FALSE(tree.Delete(inserted_elements[i]));
      EXPECT_TRUE(tree.CheckGap());
      actual_result.clear();
      tree.InorderTraverse(actual_result);
      EXPECT_THAT(actual_result, ElementsAreArray(expected_result));
    }
  }
}

TEST(DSL, Mix) {
  int sizes[] = {10, 100, 200, 500};
  for (int size : sizes) {
    std::random_device rd;
    std::mt19937 g(rd());
    g.seed(0);
    std::vector<int> elements;
    for (int i = 0; i < size; ++i) elements.insert(elements.end(), 4, i + 1);
    std::shuffle(elements.begin(), elements.end(), g);
    DSL<int> tree;
    std::set<int> expected_tree;
    std::unordered_map<int, int> count;
    for (int value : elements) {
      switch (++count[value]) {
        case 1:
          expected_tree.insert(value);
          EXPECT_TRUE(tree.Insert(value));
          break;
        case 2:
          EXPECT_FALSE(tree.Insert(value));
          break;
        case 3:
          expected_tree.erase(value);
          EXPECT_TRUE(tree.Delete(value));
          break;
        case 4:
          EXPECT_FALSE(tree.Delete(value));
          break;
      }
      EXPECT_TRUE(tree.CheckGap());
      std::vector<int> expected_result(expected_tree.begin(),
                                       expected_tree.end());
      std::vector<int> actual_result;
      tree.InorderTraverse(actual_result);
      EXPECT_THAT(actual_result, ElementsAreArray(expected_result));
    }
  }
}

}  // namespace
