#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <vector>

#include "../binary-search-tree-common/binary_search_tree_common.h"

template <typename T>
struct SplayTree {
 public:
  struct Node {
    using value_type = T;
    explicit Node(const T& x) : value(x) {}
    Node(Node* l, Node* r) : left(l), right(r) {}
    Node() = default;
    Node* left = nullptr;
    Node* right = nullptr;
    T value;
  };

  bool Insert(const T& x) {
    if (root_ == nullptr) {
      root_ = new Node(x);
      return true;
    }
    Splay(root_, x);
    if (root_->value == x) return false;
    Node* new_node = new Node(x);
    // Attach the old tree to new_node and set root_ to the new_node.
    if (x < root_->value) {
      new_node->right = root_;
      new_node->left = root_->left;
      root_->left = nullptr;
    } else {
      new_node->left = root_;
      new_node->right = root_->right;
      root_->right = nullptr;
    }
    root_ = new_node;
    return true;
  }

  bool Delete(const T& x) {
    if (root_ == nullptr) return false;
    Splay(root_, x);
    if (root_->value != x) return false;
    Node* new_tree;
    // Combine the two subtrees and delete the node.
    if (root_->left == nullptr) {
      new_tree = root_->right;
    } else {
      Splay(root_->left, x);
      new_tree = root_->left;
      new_tree->right = root_->right;
    }
    delete root_;
    root_ = new_tree;
    return true;
  }

  bool InsertRec(const T& x) {
    if (root_ == nullptr) {
      root_ = new Node(x);
      return true;
    }
    SplayRec(root_, x);
    if (root_->value == x) return false;
    Node* new_node = new Node(x);
    // Attach the old tree to new_node and set root_ to the new_node.
    if (x < root_->value) {
      new_node->right = root_;
      new_node->left = root_->left;
      root_->left = nullptr;
    } else {
      new_node->left = root_;
      new_node->right = root_->right;
      root_->right = nullptr;
    }
    root_ = new_node;
    return true;
  }

  bool DeleteRec(const T& x) {
    if (root_ == nullptr) return false;
    SplayRec(root_, x);
    Node* new_tree;
    // Combine the two subtrees and delete the node.
    if (root_->left == nullptr) {
      new_tree = root_->right;
    } else {
      SplayRec(root_->left, x);
      new_tree = root_->left;
      new_tree->right = root_->right;
    }
    delete root_;
    root_ = new_tree;
    return true;
  }

  ~SplayTree() { FreeTree(root_); }

  void InorderTraverse(std::vector<T>& result) const {
    return ::InorderTraverse(root_, result);
  }

  Node* root() const { return root_; }

  Node*& root() { return root_; }

 private:
  // Top-down splay.
  static void Splay(Node*& node, const T& x) {
    Node dummy, *left_tree = &dummy, *right_tree = &dummy;
    while (x != node->value) {
      if (x < node->value) {
        if (node->left != nullptr && x < node->left->value) RightRotate(node);
        if (node->left == nullptr) break;
        // Link right.
        right_tree->left = node;
        right_tree = node;
        node = node->left;
      } else {
        if (node->right != nullptr && x > node->right->value) LeftRotate(node);
        if (node->right == nullptr) break;
        // Link left.
        left_tree->right = node;
        left_tree = node;
        node = node->right;
      }
    }
    left_tree->right = node->left;
    right_tree->left = node->right;
    node->left = dummy.right;
    node->right = dummy.left;
  }

  static void SplayRec(Node*& node, const T& x) {
    if (node == nullptr || node->value == x) return;
    if (x < node->value) {
      if (node->left == nullptr) return;
      // Zig-Zig case.
      if (x < node->left->value) {
        SplayRec(node->left->left, x);
        RightRotate(node);
      } else if (x > node->left->value) {
        // Zig-Zag case.
        SplayRec(node->left->right, x);
        if (node->left->right != nullptr) LeftRotate(node->left);
      }
      if (node->left != nullptr) RightRotate(node);
    } else {
      if (node->right == nullptr) return;
      // Zag-Zig case.
      if (x < node->right->value) {
        SplayRec(node->right->left, x);
        if (node->right->left != nullptr) RightRotate(node->right);
      } else if (x > node->right->value) {
        // Zag-zag case.
        SplayRec(node->right->right, x);
        LeftRotate(node);
      }
      if (node->right != nullptr) LeftRotate(node);
    }
  }

  Node* root_ = nullptr;
};

#endif
