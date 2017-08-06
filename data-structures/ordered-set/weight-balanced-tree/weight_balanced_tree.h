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
    Node(Node* l, Node* r) : left(l), right(r) {}
    Node(Node* l, Node* r, int s) : left(l), right(r), size(s) {}
    Node() = default;
    Node* left = sentinel;
    Node* right = sentinel;
    int size = 1;
    T value;
  };

  void Insert(const T& x) { Insert(root_, x); }

  void Delete(const T& x) { Delete(root_, x); }

  // Compute the number of elements in the tree that is smaller than x.
  int rank(const T& x) const {
    int rank = 0;
    for (Node* current = root_; current != sentinel;) {
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

  ~WeightBalancedTree() { FreeTree(root_, sentinel); }

  void InorderTraverse(std::vector<T>& result) const {
    return ::InorderTraverse(root_, result, sentinel);
  }

  Node* root() const { return root_; }

  Node*& root() { return root_; }

 private:
  static bool IsBalanced(Node* node) {
    if (node == sentinel) return true;
    return delta * weight(node->left) >= weight(node->right) &&
           delta * weight(node->right) >= weight(node->left) &&
           IsBalanced(node->left) && IsBalanced(node->right);
  }

  static int weight(Node* node) { return size(node) + 1; }

  static int size(Node* node) { return node->size; }

  // Calaulte the size for a given node.
  static void calculate_size(Node* node) {
    node->size = size(node->left) + size(node->right) + 1;
  }

  // Bottom-up calculate the sizes for two levels for a given node.
  static void calculate_size2(Node* node) {
    calculate_size(node->left);
    calculate_size(node->right);
    node->size = node->left->size + node->right->size + 1;
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

  static void Insert(Node*& node, const T& x) {
    // When the tree is empty, create the node at root;
    if (node == sentinel) {
      node = new Node(x);
      return;
    }

    Node** parent_pointer = &node;
    while (*parent_pointer != sentinel) {
      Node*& current = *parent_pointer;
      // Rotate the tree when the size is imbalanced.
      if (x < current->value) {
        if (!is_balanced_after_insert(current->left, current->right)) {
          Node* child = current->left;
          need_single_rotation_after_insert(child->right, child->left,
                                            x > child->value)
              ? RightRotate(current)
              : LRRotate(current);
        }
      } else {
        if (!is_balanced_after_insert(current->right, current->left)) {
          Node* child = current->right;
          need_single_rotation_after_insert(child->left, child->right,
                                            x < child->value)
              ? LeftRotate(current)
              : RLRotate(current);
        }
      }
      // Since the tree might be rotated, the subtree needed to be inserted
      // might change.
      ++current->size;
      parent_pointer = x < current->value ? &current->left : &current->right;
    }
    *parent_pointer = new Node(x);
  }

  static void Delete(Node*& node, const T& x) {
    Node** parent_pointer = &node;
    while (*parent_pointer != sentinel) {
      Node*& current = *parent_pointer;
      if (current->value == x) break;
      // Rotate the tree when the size is imbalanced.
      if (x < current->value) {
        if (!is_balanced_after_remove(current->left, current->right)) {
          Node* child = current->right;
          need_single_rotation_after_remove(child->left, child->right)
              ? LeftRotate(current)
              : RLRotate(current);
        }
      } else {
        if (!is_balanced_after_remove(current->right, current->left)) {
          Node* child = current->left;
          need_single_rotation_after_remove(child->right, child->left)
              ? RightRotate(current)
              : LRRotate(current);
        }
      }
      // Since the tree might be rotated, the subtree needed to be removed
      // might change.
      --current->size;
      parent_pointer = x < current->value ? &current->left : &current->right;
    }
    Node* to_be_delete = *parent_pointer;
    if (to_be_delete == sentinel) return;
    // When the node needed to be removed has two children, pull the minimum
    // value from the right tree and delete the minimum value in the right
    // tree.
    if (to_be_delete->left != sentinel && to_be_delete->right != sentinel) {
      --to_be_delete->size;
      // If the right subtree size is larger, then promote the minimum of the
      // right subtree.
      if (size(to_be_delete->right) > size(to_be_delete->left)) {
        parent_pointer = &to_be_delete->right;
        while ((*parent_pointer)->left != sentinel) {
          Node*& current = *parent_pointer;
          if (!is_balanced_after_remove(current->left, current->right)) {
            Node* child = current->right;
            need_single_rotation_after_remove(child->left, child->right)
                ? LeftRotate(current)
                : RLRotate(current);
          }
          --current->size;
          parent_pointer = &current->left;
        }
      } else {
        // If the left subtree size is larger, then promote the maximum of the
        // left subtree.
        parent_pointer = &to_be_delete->left;
        while ((*parent_pointer)->right != sentinel) {
          Node*& current = *parent_pointer;
          if (!is_balanced_after_remove(current->right, current->left)) {
            Node* child = current->left;
            need_single_rotation_after_remove(child->right, child->left)
                ? RightRotate(current)
                : LRRotate(current);
          }
          --current->size;
          parent_pointer = &current->right;
        }
      }
      to_be_delete->value = (*parent_pointer)->value;
      to_be_delete = *parent_pointer;
    }
    // When the node needed to be removed has one child, move the non-null
    // subtree up. If both subtrees are null, then set the node to be null.
    *parent_pointer = (to_be_delete->left != sentinel ? to_be_delete->left
                                                      : to_be_delete->right);
    delete to_be_delete;
  }

  // Left rotation:
  //    root           x    |
  //    /  \          / \   |
  //   a    x   To root  c  |
  //       / \     /  \     |
  //      b    c  a    b    |
  static void LeftRotate(Node*& root) {
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
  static void RightRotate(Node*& root) {
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
  static void LRRotate(Node*& root) {
    Node *x = root->left, *y = x->right;
    x->right = y->left;
    root->left = y->right;
    y->left = x;
    y->right = root;
    root = y;
    calculate_size2(root);
  }

  // RL rotation:
  //    root              y        |
  //    /  \            /   \      |
  //   a    x         root   x     |
  //       / \   To   / \   / \    |
  //      y   d      a   b c   d   |
  //     / \                       |
  //    b   c                      |
  static void RLRotate(Node*& root) {
    Node *x = root->right, *y = x->left;
    x->left = y->right;
    root->right = y->left;
    y->left = root;
    y->right = x;
    root = y;
    calculate_size2(root);
  }

  static Node dummy;
  static constexpr Node* sentinel{&dummy};
  static constexpr int delta = 3;
  static constexpr int gamma = 2;
  Node* root_ = sentinel;
};

// TODO(C++17): use inline variable.
template <typename T>
typename WeightBalancedTree<T>::Node WeightBalancedTree<T>::dummy{&dummy,
                                                                  &dummy, 0};
#endif
