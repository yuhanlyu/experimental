#ifndef AA_TREE_H
#define AA_TREE_H

#include <vector>

#include "../binary-search-tree-common/binary_search_tree_common.h"

template <typename T>
struct AATree {
 public:
  struct Node {
    using value_type = T;
    explicit Node(const T& x) : value(x) {}
    Node(Node* l, Node* r, int lv) : left(l), right(r), level(lv) {}
    Node(Node* l, Node* r) : left(l), right(r) {}
    Node() = default;
    Node* left = sentinel;
    Node* right = sentinel;
    int level = 1;
    T value;
  };

  bool Insert(const T& x) { return Insert(root_, x); }

  bool Delete(const T& x) { return Delete(root_, x); }

  bool IsBalanced() const { return IsBalanced(root_); }

  ~AATree() { FreeTree(root_, sentinel); }

  void InorderTraverse(std::vector<T>& result) const {
    return ::InorderTraverse(root_, result, sentinel);
  }

  Node* root() const { return root_; }

  Node*& root() { return root_; }

 private:
  static bool IsBalanced(Node* node) {
    if (node == sentinel) return true;
    if (node->left->level == node->level) return false;
    if (node->right->right->level == node->level) return false;
    return IsBalanced(node->left) && IsBalanced(node->right);
  }

  static bool Insert(Node*& node, const T& x) {
    // When the tree is empty, create the node at root;
    if (node == sentinel) {
      node = new Node(x);
      return true;
    }
    if (x == node->value) return false;
    if (!Insert(x < node->value ? node->left : node->right, x)) return false;
    node = Skew(node);
    node = Split(node);
    return true;
  }

  static bool Delete(Node*& node, const T& x) {
    if (node == sentinel) return false;
    if (x == node->value) {
      if (node->left == sentinel && node->right == sentinel) {
        delete node;
        node = sentinel;
        return true;
      }
      // When there are two subtrees, find the successor.
      // When there is one subtree, must find predecessor/successor accordingly,
      // instead of promoting the only child.
      if (node->left == sentinel)
        node->right = DeleteMinAndSet(node, node->right);
      else
        node->left = DeleteMaxAndSet(node, node->left);
    } else if (!Delete(x < node->value ? node->left : node->right, x))
      return false;
    node = RebalanceAfterDelete(node);
    return true;
  }

  // Find the minimum in the subtree rooted at node, set be_deleted->value to be
  // the minimum and delete the minimum node.
  static Node* DeleteMinAndSet(Node* be_deleted, Node* node) {
    if (node->left != sentinel) {
      node->left = DeleteMinAndSet(be_deleted, node->left);
      node = RebalanceAfterDelete(node);
    } else {
      be_deleted->value = node->value;
      Node* old_node = node;
      node = node->right;
      delete old_node;
    }
    return node;
  }

  // Find the maximum in the subtree rooted at node, set be_deleted->value to be
  // the minimum and delete the minimum node.
  static Node* DeleteMaxAndSet(Node* be_deleted, Node* node) {
    if (node->right != sentinel) {
      node->right = DeleteMaxAndSet(be_deleted, node->right);
      node = RebalanceAfterDelete(node);
    } else {
      be_deleted->value = node->value;
      Node* old_node = node;
      node = node->right;
      delete old_node;
    }
    return node;
  }

  // If the tree is imbalance after deletion, rebalance the tree.
  static Node* RebalanceAfterDelete(Node* node) {
    if (node->left->level >= node->level - 1 &&
        node->right->level >= node->level - 1)
      return node;
    if (node->right->level > --node->level) node->right->level = node->level;
    node = Skew(node);
    node->right = Skew(node->right);
    node->right->right = Skew(node->right->right);
    node = Split(node);
    node->right = Split(node->right);
    return node;
  }

  // Right rotation:
  //    root          x       |
  //    /  \         / \      |
  //   x    c  To   a  root   |
  //  / \              /  \   |
  // a   b            b    c  |
  static Node* Skew(Node* root) {
    if (root->left->level != root->level) return root;
    Node* x = root->left;
    root->left = x->right;
    x->right = root;
    return x;
  }

  // Left rotation:
  //    root           x    |
  //    /  \          / \   |
  //   a    x   To root  c  |
  //       / \     /  \     |
  //      b    c  a    b    |
  static Node* Split(Node* root) {
    if (root->right->right->level != root->level) return root;
    Node* x = root->right;
    root->right = x->left;
    x->left = root;
    ++x->level;
    return x;
  }

  static Node dummy;
  static constexpr Node* sentinel{&dummy};
  Node* root_ = sentinel;
};

// TODO(C++17): use inline variable.
template <typename T>
typename AATree<T>::Node AATree<T>::dummy{&dummy, &dummy, 0};
#endif
