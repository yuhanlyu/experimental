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

  void Insert(const T& x) {
    Node **parent_pointer = &root_, *new_node = new Node(x);
    while (*parent_pointer != nullptr &&
           Random(++(*parent_pointer)->size) == 0) {
      parent_pointer = (x < (*parent_pointer)->value)
                           ? &(*parent_pointer)->left
                           : &(*parent_pointer)->right;
    }
    if (*parent_pointer != nullptr) {
      Split(*parent_pointer, x, new_node->left, new_node->right);
      UpdateSize(new_node);
    }
    *parent_pointer = new_node;
  }

  bool Delete(const T& x) {
    Node** parent_pointer = &root_;
    while (*parent_pointer != nullptr && (*parent_pointer)->value != x) {
      Node*& current = *parent_pointer;
      --current->size;
      parent_pointer = (x < current->value) ? &current->left : &current->right;
    }
    if (*parent_pointer == nullptr) return false;
    Node* to_be_delete = *parent_pointer;
    Join(*parent_pointer, (*parent_pointer)->left, (*parent_pointer)->right);
    delete to_be_delete;
    if (*parent_pointer != nullptr) UpdateSize(*parent_pointer);
    return true;
  }

  ~RBST() { FreeTree(root_); }

  void InorderTraverse(std::vector<T>& result) const {
    return ::InorderTraverse(root_, result);
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

  Node* root() const { return root_; }

  Node*& root() { return root_; }

 private:
  static int size(Node* node) { return node == nullptr ? 0 : node->size; }

  static void UpdateSize(Node* node) {
    node->size = size(node->left) + size(node->right) + 1;
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
  static void Join(Node*& node, Node* left, Node* right) {
    if (left == nullptr || right == nullptr) {
      node = left == nullptr ? right : left;
      return;
    }
    int n = size(left);
    if (Random(n + size(right) - 1) < n) {
      Join(left->right, left->right, right);
      node = left;
    } else {
      Join(right->left, left, right->left);
      node = right;
    }
    UpdateSize(node);
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
