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
    Node* left = sentinel;
    Node* right = sentinel;
    T value;
  };

  bool Insert(const T& x) {
    if (root_ == sentinel) {
      root_ = new Node(x);
      return true;
    }
    Splay(root_, x);
    if (root_->value == x) return false;
    Node* new_node = new Node(x);
    if (x < root_->value) {
      new_node->right = root_;
      new_node->left = root_->left;
      root_->left = sentinel;
    } else {
      new_node->left = root_;
      new_node->right = root_->right;
      root_->right = sentinel;
    }
    root_ = new_node;
    return true;
  }

  bool Delete(const T& x) {
    if (root_ == sentinel) return false;
    Splay(root_, x);
    if (root_->value != x) return false;
    Node* new_tree;
    if (root_->left == sentinel) {
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

  bool InsertRec(const T& x) {
    if (root_ == sentinel) {
      root_ = new Node(x);
      return true;
    }
    SplayRec(root_, x);
    if (root_->value == x) return false;
    Node* new_node = new Node(x);
    if (x < root_->value) {
      new_node->right = root_;
      new_node->left = root_->left;
      root_->left = sentinel;
    } else {
      new_node->left = root_;
      new_node->right = root_->right;
      root_->right = sentinel;
    }
    root_ = new_node;
    return true;
  }

  bool DeleteRec(const T& x) {
    if (root_ == sentinel) return false;
    SplayRec(root_, x);
    Node* new_tree;
    if (root_->left == sentinel) {
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

  ~SplayTree() { FreeTree(root_, sentinel); }

  void InorderTraverse(std::vector<T>& result) const {
    return ::InorderTraverse(root_, result, sentinel);
  }

  Node* root() const { return root_; }

  Node*& root() { return root_; }

  static Node* sentinel;

 private:
  // Top-down splay.
  static void Splay(Node*& node, const T& x) {
    Node dummy, *left_tree = &dummy, *right_tree = &dummy;
    for (sentinel->value = x; x != node->value;) {
      if (x < node->value) {
        if (x < node->left->value) RightRotate(node);
        if (node->left == sentinel) break;
        // Link right.
        right_tree->left = node;
        right_tree = node;
        node = node->left;
      } else {
        if (x > node->right->value) LeftRotate(node);
        if (node->right == sentinel) break;
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
    if (node == sentinel || node->value == x) return;
    if (x < node->value) {
      if (node->left == sentinel) return;
      // Zig-Zig case.
      if (x < node->left->value) {
        SplayRec(node->left->left, x);
        RightRotate(node);
      } else if (x > node->left->value) {
        // Zig-Zag case.
        SplayRec(node->left->right, x);
        if (node->left->right != sentinel) LeftRotate(node->left);
      }
      if (node->left != sentinel) RightRotate(node);
    } else {
      if (node->right == sentinel) return;
      // Zag-Zig case.
      if (x < node->right->value) {
        SplayRec(node->right->left, x);
        if (node->right->left != sentinel) RightRotate(node->right);
      } else if (x > node->right->value) {
        // Zag-zag case.
        SplayRec(node->right->right, x);
        LeftRotate(node);
      }
      if (node->right != sentinel) LeftRotate(node);
    }
  }

  // Create the sentinel node.
  static Node* InitializeSentinel() {
    Node* sentinel = new Node();
    sentinel->left = sentinel->right = sentinel;
    return sentinel;
  }

  Node* root_ = sentinel;
};

template <typename T>
typename SplayTree<T>::Node* SplayTree<T>::sentinel =
    SplayTree<T>::InitializeSentinel();

#endif
