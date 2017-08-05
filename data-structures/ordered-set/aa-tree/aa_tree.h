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
    if (!((x < node->value) ? Insert(node->left, x) : Insert(node->right, x)))
      return false;
    Skew(node);
    Split(node);
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
      node->left == sentinel ? DeleteMinAndSet(node, node->right)
                             : DeleteMaxAndSet(node, node->left);
    } else if (!((x < node->value) ? Delete(node->left, x)
                                   : Delete(node->right, x)))
      return false;
    RebalanceAfterDelete(node);
    return true;
  }

  // Find the minimum in the subtree rooted at node, set be_deleted->value to be
  // the minimum and delete the minimum node.
  static void DeleteMinAndSet(Node* be_deleted, Node*& node) {
    if (node->left != sentinel) {
      DeleteMinAndSet(be_deleted, node->left);
      RebalanceAfterDelete(node);
    } else {
      be_deleted->value = node->value;
      Node* old_node = node;
      node = node->right;
      delete old_node;
    }
  }

  // Find the maximum in the subtree rooted at node, set be_deleted->value to be
  // the minimum and delete the minimum node.
  static void DeleteMaxAndSet(Node* be_deleted, Node*& node) {
    if (node->right != sentinel) {
      DeleteMaxAndSet(be_deleted, node->right);
      RebalanceAfterDelete(node);
    } else {
      be_deleted->value = node->value;
      Node* old_node = node;
      node = node->right;
      delete old_node;
    }
  }

  // If the tree is imbalance after deletion, rebalance the tree.
  static void RebalanceAfterDelete(Node*& node) {
    if (node->left->level >= node->level - 1 &&
        node->right->level >= node->level - 1)
      return;
    if (node->right->level > --node->level) node->right->level = node->level;
    Skew(node);
    Skew(node->right);
    Skew(node->right->right);
    Split(node);
    Split(node->right);
  }

  // Right rotation:
  //    root          x       |
  //    /  \         / \      |
  //   x    c  To   a  root   |
  //  / \              /  \   |
  // a   b            b    c  |
  static void Skew(Node*& root) {
    if (root->left->level != root->level) return;
    Node* x = root->left;
    root->left = x->right;
    x->right = root;
    root = x;
  }

  // Left rotation:
  //    root           x    |
  //    /  \          / \   |
  //   a    x   To root  c  |
  //       / \     /  \     |
  //      b    c  a    b    |
  static void Split(Node*& root) {
    if (root->right->right->level != root->level) return;
    Node* x = root->right;
    root->right = x->left;
    x->left = root;
    ++x->level;
    root = x;
  }

  static Node dummy;
  static constexpr Node* sentinel{&dummy};
  Node* root_ = sentinel;
};

// TODO(C++17): use inline variable.
template <typename T>
typename AATree<T>::Node AATree<T>::dummy{&dummy, &dummy, 0};
#endif
