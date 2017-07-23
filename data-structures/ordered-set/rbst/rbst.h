#ifndef RANDOMIZED_BINARY_SEARCH_TREE_H
#define RANDOMIZED_BINARY_SEARCH_TREE_H

#include <random>
#include <vector>

#include "../binary-search-tree-common/binary_search_tree_common.h"

template <typename T>
struct RBST {
 public:
  struct Node {
    using value_type = T;
    explicit Node(const T& x) : value(x) {}
    Node(Node* l, Node* r) : left(l), right(r) {}
    Node() = default;
    Node* left = nullptr;
    Node* right = nullptr;
    int size = 1;
    T value;
  };

  void Insert(const T& x) { Insert(root_, x); }

  void Delete(const T& x) { Delete(root_, x); }

  ~RBST() { FreeTree(root_); }

  void InorderTraverse(std::vector<T>& result) const {
    return ::InorderTraverse(root_, result);
  }

  int rank(const T& x) const { return rank(root_, x); }

  Node* root() const { return root_; }

  Node*& root() { return root_; }

 private:
  // Compute the number of elements in the tree that is smaller than x.
  static int rank(const Node* node, const T& x) {
    int rank = 0;
    for (const Node* current = node; current != nullptr;) {
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

  static int size(Node* node) { return node == nullptr ? 0 : node->size; }

  static void UpdateSize(Node* node) {
    node->size = size(node->left) + size(node->right) + 1;
  }

  static void Insert(Node*& node, const T& x) {
    Node *parent = nullptr, *current = node, *new_node = new Node(x);
    while (current != nullptr && Random(++current->size) == 0) {
      parent = current;
      current = x < current->value ? current->left : current->right;
    }
    if (current != nullptr) {
      Split(current, x, new_node->left, new_node->right);
      UpdateSize(new_node);
    }
    if (parent == nullptr)
      node = new_node;
    else
      (x < parent->value ? parent->left : parent->right) = new_node;
  }

  static void Delete(Node*& node, const T& x) {
    Node *parent = nullptr, *current = node;
    while (current != nullptr && current->value != x) {
      parent = current;
      --current->size;
      current = (x < current->value) ? current->left : current->right;
    }
    Node* subtree = Join(current->left, current->right);
    if (parent == nullptr) {
      node = subtree;
      if (node != nullptr) UpdateSize(node);
    } else {
      (parent->left == current ? parent->left : parent->right) = subtree;
      UpdateSize(parent);
    }
    delete current;
  }

  // Split the subtree rooted at node, so that all nodes that are smaller than
  // x is rooted at left, and other nodes are rooted at right.
  static void Split(Node* node, const T& x, Node*& left, Node*& right) {
    if (node == nullptr) {
      left = right = nullptr;
      return;
    }
    if (x < node->value) {
      Split(node->left, x, left, node->left);
      right = node;
    } else {
      Split(node->right, x, node->right, right);
      left = node;
    }
    UpdateSize(node);
  }

  // Merge the trees that are rooted at left and right as root.
  static Node* Join(Node* left, Node* right) {
    if (left == nullptr || right == nullptr)
      return left == nullptr ? right : left;
    int n = size(left);
    if (Random(n + size(right) - 1) < n) {
      left->right = Join(left->right, right);
      UpdateSize(left);
      return left;
    }
    right->left = Join(left, right->left);
    UpdateSize(right);
    return right;
  }

  // Return a random number between 0 and n.
  static int Random(int n) {
    static std::random_device random_device;
    static std::default_random_engine generator{random_device()};
    static std::uniform_int_distribution<> distribution;
    return distribution(generator) % (n + 1);
  }

  Node* root_ = nullptr;
};
#endif
