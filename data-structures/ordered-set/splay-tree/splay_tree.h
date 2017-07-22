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

  bool Insert(const T& x) { return Insert(root_, x); }

  bool Delete(const T& x) { return Delete(root_, x); }

  bool InsertRec(const T& x) { return InsertRec(root_, x); }

  bool DeleteRec(const T& x) { return DeleteRec(root_, x); }

  ~SplayTree() { FreeTree(root_); }

  void InorderTraverse(std::vector<T>& result) const {
    return ::InorderTraverse(root_, result);
  }

  Node* root() const { return root_; }

  Node*& root() { return root_; }

 private:
  static bool Insert(Node*& node, const T& x) {
    if (node == nullptr) {
      node = new Node(x);
      return true;
    }
    node = Splay(node, x);
    if (node->value == x) return false;
    Node* new_node = new Node(x);
    // Attach the old tree to new_node and set node to the new_node.
    if (x < node->value) {
      new_node->right = node;
      new_node->left = node->left;
      node->left = nullptr;
    } else {
      new_node->left = node;
      new_node->right = node->right;
      node->right = nullptr;
    }
    node = new_node;
    return true;
  }

  static bool Delete(Node*& node, const T& x) {
    if (node == nullptr) return false;
    node = Splay(node, x);
    if (node->value != x) return false;
    Node* new_tree;
    // Combine the two subtrees and delete the node.
    if (node->left == nullptr) {
      new_tree = node->right;
    } else {
      node->left = Splay(node->left, x);
      new_tree = node->left;
      new_tree->right = node->right;
    }
    delete node;
    node = new_tree;
    return true;
  }

  static bool InsertRec(Node*& node, const T& x) {
    if (node == nullptr) {
      node = new Node(x);
      return true;
    }
    node = SplayRec(node, x);
    if (node->value == x) return false;
    Node* new_node = new Node(x);
    // Attach the old tree to new_node and set node to the new_node.
    if (x < node->value) {
      new_node->right = node;
      new_node->left = node->left;
      node->left = nullptr;
    } else {
      new_node->left = node;
      new_node->right = node->right;
      node->right = nullptr;
    }
    node = new_node;
    return true;
  }

  static bool DeleteRec(Node*& node, const T& x) {
    node = SplayRec(node, x);
    if (node == nullptr || node->value != x) return false;
    Node* new_tree;
    // Combine the two subtrees and delete the node.
    if (node->left == nullptr) {
      new_tree = node->right;
    } else {
      node->left = SplayRec(node->left, x);
      new_tree = node->left;
      new_tree->right = node->right;
    }
    delete node;
    node = new_tree;
    return true;
  }

  // Top-down splay.
  static Node* Splay(Node* node, const T& x) {
    Node dummy, *left_tree = &dummy, *right_tree = &dummy;
    while (x != node->value) {
      if (x < node->value) {
        if (node->left != nullptr && x < node->left->value)
          node = RightRotate(node);
        if (node->left == nullptr) break;
        // Link right.
        right_tree->left = node;
        right_tree = node;
        node = node->left;
      } else {
        if (node->right != nullptr && x > node->right->value)
          node = LeftRotate(node);
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
    return node;
  }

  static Node* SplayRec(Node* node, const T& x) {
    if (node == nullptr || node->value == x) return node;
    if (x < node->value) {
      if (node->left == nullptr) return node;
      // Zig-Zig case.
      if (x < node->left->value) {
        node->left->left = SplayRec(node->left->left, x);
        node = RightRotate(node);
      } else if (x > node->left->value) {
        // Zig-Zag case.
        node->left->right = SplayRec(node->left->right, x);
        if (node->left->right != nullptr) node->left = LeftRotate(node->left);
      }
      if (node->left != nullptr) node = RightRotate(node);
    } else {
      if (node->right == nullptr) return node;
      // Zag-Zig case.
      if (x < node->right->value) {
        node->right->left = SplayRec(node->right->left, x);
        if (node->right->left != nullptr)
          node->right = RightRotate(node->right);
      } else if (x > node->right->value) {
        // Zag-zag case.
        node->right->right = SplayRec(node->right->right, x);
        node = LeftRotate(node);
      }
      if (node->right != nullptr) node = LeftRotate(node);
    }
    return node;
  }

  // Left rotation:
  //    root           x    |
  //    /  \          / \   |
  //   a    x   To root  c  |
  //       / \     /  \     |
  //      b    c  a    b    |
  template <typename Node>
  static Node* LeftRotate(Node* root) {
    Node* x = root->right;
    root->right = x->left;
    x->left = root;
    return x;
  }

  // Right rotation:
  //    root          x       |
  //    /  \         / \      |
  //   x    c  To   a  root   |
  //  / \              /  \   |
  // a   b            b    c  |
  template <typename Node>
  static Node* RightRotate(Node* root) {
    Node* x = root->left;
    root->left = x->right;
    x->right = root;
    return x;
  }

  Node* root_ = nullptr;
};

#endif
