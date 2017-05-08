#ifndef WEIGHT_BALANCED_TREE_H
#define WEIGHT_BALANCED_TREE_H

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

  void Insert(const T& x) {
    // When the tree is empty, create the node at root;
    if (root_ == nullptr) {
      root_ = new Node(x);
      return;
    }

    Node** parent_pointer = &root_;
    for (Node* current = root_; current != nullptr;) {
      // Rotate the tree when the size is imbalanced.
      if (x < current->value) {
        if (!is_balanced_after_insert(current->left, current->right)) {
          Node* child = current->left;
          need_single_rotation_after_insert(child->right, child->left,
                                            x > child->value)
              ? RightRotation(*parent_pointer)
              : LRRotation(*parent_pointer);
        }
      } else {
        if (!is_balanced_after_insert(current->right, current->left)) {
          Node* child = current->right;
          need_single_rotation_after_insert(child->left, child->right,
                                            x < child->value)
              ? LeftRotation(*parent_pointer)
              : RLRotation(*parent_pointer);
        }
      }
      // Since the tree might be rotated, the subtree needed to be inserted
      // might change.
      ++(*parent_pointer)->size;
      if (x < (*parent_pointer)->value) {
        current = (*parent_pointer)->left;
        parent_pointer = &(*parent_pointer)->left;
      } else {
        current = (*parent_pointer)->right;
        parent_pointer = &(*parent_pointer)->right;
      }
    }
    *parent_pointer = new Node(x);
  }

  void Delete(const T& x) {
    Node **parent_pointer = &root_, *current = root_;
    while (current != nullptr) {
      if (current->value == x) break;
      // Rotate the tree when the size is imbalanced.
      if (x < current->value) {
        if (!is_balanced_after_remove(current->left, current->right)) {
          Node* child = current->right;
          need_single_rotation_after_remove(child->left, child->right)
              ? LeftRotation(*parent_pointer)
              : RLRotation(*parent_pointer);
        }
      } else {
        if (!is_balanced_after_remove(current->right, current->left)) {
          Node* child = current->left;
          need_single_rotation_after_remove(child->right, child->left)
              ? RightRotation(*parent_pointer)
              : LRRotation(*parent_pointer);
        }
      }
      // Since the tree might be rotated, the subtree needed to be removed
      // might change.
      --(*parent_pointer)->size;
      if (x < (*parent_pointer)->value) {
        current = (*parent_pointer)->left;
        parent_pointer = &(*parent_pointer)->left;
      } else {
        current = (*parent_pointer)->right;
        parent_pointer = &(*parent_pointer)->right;
      }
    }
		if (current == nullptr) return;
    // When the node needed to be removed has two children, pull the minimum
    // value from the right tree and delete the minimum value in the right
    // tree.
    if (current->left != nullptr && current->right != nullptr) {
      --current->size;
      // If the right subtree size is larger, then promote the minimum of the
      // right subtree.
      if (size(current->right) > size(current->left)) {
        Node* min = current->right;
        for (parent_pointer = &current->right; min->left != nullptr;) {
          if (!is_balanced_after_remove(min->left, min->right)) {
            Node* child = min->right;
            need_single_rotation_after_remove(child->left, child->right)
                ? LeftRotation(*parent_pointer)
                : RLRotation(*parent_pointer);
          }
          --(*parent_pointer)->size;
          min = (*parent_pointer)->left;
          parent_pointer = &(*parent_pointer)->left;
        }
        current->value = min->value;
        current = min;
      } else {
        // If the left subtree size is larger, then promote the maximum of the
        // left subtree.
        Node* max = current->left;
        for (parent_pointer = &current->left; max->right != nullptr;) {
          if (!is_balanced_after_remove(max->right, max->left)) {
            Node* child = max->left;
            need_single_rotation_after_remove(child->right, child->left)
                ? RightRotation(*parent_pointer)
                : LRRotation(*parent_pointer);
          }
          --(*parent_pointer)->size;
          max = (*parent_pointer)->right;
          parent_pointer = &(*parent_pointer)->right;
        }
        current->value = max->value;
        current = max;
      }
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
  bool IsBalanced(Node* node) const {
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

  // Left rotation:
  //    root           x    |
  //    /  \          / \   |
  //   a    x   To root  c  |
  //       / \     /  \     |
  //      b    c  a    b    |
  static void LeftRotation(Node*& root) {
    Node* x = root->right;
    root->right = x->left;
    x->left = root;
    root = x;
    calculate_size(x->left);
    calculate_size(x);
  }

  // Right rotation:
  //    root          x       |
  //    /  \         / \      |
  //   x    c  To   a  root   |
  //  / \              /  \   |
  // a   b            b    c  |
  static void RightRotation(Node*& root) {
    Node* x = root->left;
    root->left = x->right;
    x->right = root;
    root = x;
    calculate_size(x->right);
    calculate_size(x);
  }

  // LR rotation:
  //    root             y         |
  //    /  \           /   \       |
  //   x    d         x    root    |
  //  / \      To    / \   /  \    |
  // a   y          a   b c    d   |
  //    / \                        |
  //   b   c                       |
  static void LRRotation(Node*& root) {
    Node *x = root->left, *y = x->right;
    x->right = y->left;
    root->left = y->right;
    y->left = x;
    y->right = root;
    root = y;
    calculate_size2(y);
  }

  // RL rotation:
  //    root              y        |
  //    /  \            /   \      |
  //   a    x         root   x     |
  //       / \   To   / \   / \    |
  //      y   d      a   b c   d   |
  //     / \                       |
  //    b   c                      |
  static void RLRotation(Node*& root) {
    Node *x = root->right, *y = x->left;
    x->left = y->right;
    root->right = y->left;
    y->left = root;
    y->right = x;
    root = y;
    calculate_size2(y);
  }

  Node* root_ = nullptr;
  static constexpr int delta = 3;
  static constexpr int gamma = 2;
};

#endif
