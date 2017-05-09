#ifndef WEIGHT_BALANCED_TREE_H
#define WEIGHT_BALANCED_TREE_H

#include <type_traits>
#include <vector>

#include "../binary-search-tree-common/binary_search_tree_common.h"

template <typename T>
struct WeightBalancedTree {
 public:
  struct Node {
    using value_type = T;
    explicit Node(const T& x) : value(x) {}
    explicit Node(Node* l, Node* r) : left(l), right(r) {}
    Node() = default;
    Node* left = nullptr;
    Node* right = nullptr;
    int size = 1;
    T value;
  };

  // Left<true>(node) returns node->left, Left<false>(node) returns node->right.
  template <bool mode, typename std::enable_if<mode>::type* = nullptr>
  static Node*& Left(Node* node) {
    return node->left;
  }
  template <bool mode, typename std::enable_if<!mode>::type* = nullptr>
  static Node*& Left(Node* node) {
    return node->right;
  }

  // Right<true>(node) returns node->left, Right<false>(node) returns
  // node->left.
  template <bool mode, typename std::enable_if<mode>::type* = nullptr>
  static Node*& Right(Node* node) {
    return node->right;
  }
  template <bool mode, typename std::enable_if<!mode>::type* = nullptr>
  static Node*& Right(Node* node) {
    return node->left;
  }

  void Insert(const T& x) {
    // When the tree is empty, create the node at root;
    if (root_ == nullptr) {
      root_ = new Node(x);
      return;
    }

    Node** parent_pointer = &root_;
    for (Node* current = root_; current != nullptr;) {
      // Rotate the tree when the size is imbalanced.
      x < current->value ? InsertHelper<false>(x, current, *parent_pointer)
                         : InsertHelper<true>(x, current, *parent_pointer);
      // Since the tree might be rotated, the subtree needed to be inserted
      // might change.
      ++(*parent_pointer)->size;
      x < (*parent_pointer)->value
          ? UpdateCurrent<true>(current, parent_pointer)
          : UpdateCurrent<false>(current, parent_pointer);
    }
    *parent_pointer = new Node(x);
  }

  void Delete(const T& x) {
    Node **parent_pointer = &root_, *current = root_;
    while (current != nullptr) {
      if (current->value == x) break;
      // Rotate the tree when the size is imbalanced.
      x < current->value ? DeleteHelper<true>(current, *parent_pointer)
                         : DeleteHelper<false>(current, *parent_pointer);
      // Since the tree might be rotated, the subtree needed to be removed
      // might change.
      --(*parent_pointer)->size;
      x < (*parent_pointer)->value
          ? UpdateCurrent<true>(current, parent_pointer)
          : UpdateCurrent<false>(current, parent_pointer);
    }
    if (current == nullptr) return;
    // When the node needed to be removed has two children, pull the minimum
    // value from the right tree and delete the minimum value in the right
    // tree.
    if (current->left != nullptr && current->right != nullptr) {
      --current->size;
      // If the right subtree size is larger, then promote the minimum of the
      // right subtree. Otherwise, promote the maximum of the left subtree.
      size(current->right) > size(current->left)
          ? DeleteMin<true>(current, parent_pointer)
          : DeleteMin<false>(current, parent_pointer);
    }
    // When the node needed to be removed has one child, move the non-null
    // subtree up. If both subtrees are null, then set the node to be null.
    *parent_pointer =
        (current->left != nullptr ? current->left : current->right);
    delete current;
  }

  // Compute the number of elements in the tree that is smaller than x.
  int rank(const T& x) const {
    int rank = 0;
    for (Node* current = root_; current != nullptr;) {
      if (x == current->value) return rank + size(current->left);
      if (x < current->value) {
        current = current->left;
      } else {
        rank += 1 + size(current->left);
        current = current->right;
      }
    }
    return rank;
  }

  bool IsBalanced() const { return IsBalanced(root_); }

  ~WeightBalancedTree() { FreeTree(root_); }

  void InorderTraverse(std::vector<T>& result) const {
    return ::InorderTraverse(root_, result);
  }

  Node* root() const { return root_; }

  Node*& root() { return root_; }

 private:
  static bool IsBalanced(Node* node) {
    if (node == nullptr) return true;
    return delta * weight(node->left) >= weight(node->right) &&
           delta * weight(node->right) >= weight(node->left) &&
           IsBalanced(node->left) && IsBalanced(node->right);
  }

  static int weight(Node* node) { return size(node) + 1; }

  static int size(Node* node) { return node == nullptr ? 0 : node->size; }

  // Calaulte the size for a given node.
  static void calculate_size(Node* node) {
    node->size = size(node->left) + size(node->right) + 1;
  }

  // Bottom-up calculate the sizes for two levels for a given node.
  static void calculate_size2(Node* node) {
    calculate_size(node->left);
    calculate_size(node->right);
    calculate_size(node);
  }

  // Test whether the tree is balanced after the node is inserted.
  static bool is_balanced_after_insert(Node* insert, Node* other) {
    return delta * weight(other) >= weight(insert) + 1;
  }

  // Test whether the tree needs single rotation after the node is inserted.
  static bool need_single_rotation_after_insert(Node* inner, Node* outer,
                                                bool insert_inner) {
    return weight(inner) + insert_inner <
           gamma * (weight(outer) + !insert_inner);
  }

  // Test whether the tree is balanced after the node is removed.
  static bool is_balanced_after_remove(Node* remove, Node* other) {
    return delta * (weight(remove) - 1) >= weight(other);
  }

  // Test whether the tree needs single rotation after the node is removed.
  static bool need_single_rotation_after_remove(Node* inner, Node* outer) {
    return weight(inner) < gamma * weight(outer);
  }

  // Rotate the subtree when necessary during the insert.
  template <bool mode>
  static void InsertHelper(const T& x, Node* current, Node*& parent_pointer) {
    if (!is_balanced_after_insert(Right<mode>(current), Left<mode>(current))) {
      Node* child = Right<mode>(current);
      bool test = !(mode ^ (x < child->value));
      need_single_rotation_after_insert(Left<mode>(child), Right<mode>(child),
                                        test)
          ? LeftRotation<mode>(parent_pointer)
          : RLRotation<mode>(parent_pointer);
    }
  }

  // Rotate the subtree when necessary during the delete.
  template <bool mode>
  static void DeleteHelper(Node* current, Node*& parent_pointer) {
    if (!is_balanced_after_remove(Left<mode>(current), Right<mode>(current))) {
      Node* child = Right<mode>(current);
      need_single_rotation_after_remove(Left<mode>(child), Right<mode>(child))
          ? LeftRotation<mode>(parent_pointer)
          : RLRotation<mode>(parent_pointer);
    }
  }

  // When mode is true, find the minimum value of the right subtree of current
  // and assign the minimum value to the current. Then, set the current to be
	// the minimum node. During the traversal, rotate the tree if the tree will
	// become imbalanced after the minimum node is deleted. In the end of the
	// function, the parent_pointer will be the pointer in the parent of minimum
	// node pointing to the minimum node.
  // The case of mode=false is symmetric for finding the maximum value of the
  // left subtree of current.
  template <bool mode>
  static void DeleteMin(Node*& current, Node**& parent_pointer) {
    Node* min = Right<mode>(current);
    for (parent_pointer = &Right<mode>(current); Left<mode>(min) != nullptr;) {
      if (!is_balanced_after_remove(Left<mode>(min), Right<mode>(min))) {
        Node* child = Right<mode>(min);
        need_single_rotation_after_remove(Left<mode>(child), Right<mode>(child))
            ? LeftRotation<mode>(*parent_pointer)
            : RLRotation<mode>(*parent_pointer);
      }
      --(*parent_pointer)->size;
      min = Left<mode>(*parent_pointer);
      parent_pointer = &Left<mode>(*parent_pointer);
    }
    current->value = min->value;
    current = min;
  }

  // Update the current and parent_pointer.
  // When less_than_x is true, current will be (*parent_pointer)->left and
  // parent_pointer will be &(*parent_pointer)->left.
  // When less_than_x is false, current will be (*parent_pointer)->right and
  // parent_pointer will be &(*parent_pointer)->right.
  template <bool less_than_x>
  static void UpdateCurrent(Node*& current, Node**& parent_pointer) {
    current = Left<less_than_x>(*parent_pointer);
    parent_pointer = &Left<less_than_x>(*parent_pointer);
  }

  // LeftRotation<true> is left rotation.
  //    root           x    |
  //    /  \          / \   |
  //   a    x   To root  c  |
  //       / \     /  \     |
  //      b    c  a    b    |
  // LeftRotation<false> is right rotation.
  //    root          x       |
  //    /  \         / \      |
  //   x    c  To   a  root   |
  //  / \              /  \   |
  // a   b            b    c  |
  template <bool mode>
  static void LeftRotation(Node*& root) {
    Node* x = Right<mode>(root);
    Right<mode>(root) = Left<mode>(x);
    Left<mode>(x) = root;
    root = x;
    calculate_size(Left<mode>(x));
    calculate_size(x);
  }

  // RLRotation<true> is RL rotation, which is a right rotation followed by a
  // left rotation.
  //    root              y        |
  //    /  \            /   \      |
  //   a    x         root   x     |
  //       / \   To   / \   / \    |
  //      y   d      a   b c   d   |
  //     / \                       |
  //    b   c                      |
  // RLRotation<false> is LR rotation, which is a left rotation followed by a
  // right rotation.
  //    root             y         |
  //    /  \           /   \       |
  //   x    d         x    root    |
  //  / \      To    / \   /  \    |
  // a   y          a   b c    d   |
  //    / \                        |
  //   b   c                       |
  template <bool mode>
  static void RLRotation(Node*& root) {
    Node *x = Right<mode>(root), *y = Left<mode>(x);
    Left<mode>(x) = Right<mode>(y);
    Right<mode>(root) = Left<mode>(y);
    Left<mode>(y) = root;
    Right<mode>(y) = x;
    root = y;
    calculate_size2(y);
  }

  Node* root_ = nullptr;
  static constexpr int delta = 3;
  static constexpr int gamma = 2;
};

#endif
