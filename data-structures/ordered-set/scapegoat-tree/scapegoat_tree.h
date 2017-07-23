#ifndef SCAPEGOAT_TREE_H
#define SCAPEGOAT_TREE_H

#include <cmath>
#include <vector>

#include "../binary-search-tree-common/binary_search_tree_common.h"

template <typename T>
struct ScapegoatTree {
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
    if (!Insert(root_, x, size)) return false;
    if (++size > max_size) max_size = size;
    return true;
  }

  bool Delete(const T& x) {
    if (!Delete(root_, x, size, max_size)) return false;
    if (--size < alpha * max_size) max_size = size;
    return true;
  }

  ~ScapegoatTree() { FreeTree(root_); }

  void InorderTraverse(std::vector<T>& result) const {
    return ::InorderTraverse(root_, result);
  }

  Node* root() const { return root_; }

  Node*& root() { return root_; }

 private:
  static int height_alpha(int size) {
    return std::floor(std::log(size) * log_sqrt2);
  }

  static bool Insert(Node*& node, const T& x, int size) {
    // When the tree is empty, create the node at root;
    if (node == nullptr) {
      node = new Node(x);
      return true;
    }
    std::vector<Node*> ancestors;
    for (Node* current = node; current != nullptr;) {
      if (current->value == x) return false;
      ancestors.push_back(current);
      current = (x < current->value) ? current->left : current->right;
    }
    Node* parent = ancestors[ancestors.size() - 1];
    ((x < parent->value) ? parent->left : parent->right) = new Node(x);

    // The distance betweeen new node and root is ancestors.size().
    if (++size <= 2 || ancestors.size() <= height_alpha(size)) return true;
    Node* current = x < parent->value ? parent->left : parent->right;
    for (int depth = 1, subtree_size = 1; depth <= ancestors.size(); ++depth) {
      parent = ancestors[ancestors.size() - depth];
      if (depth - 1 > height_alpha(subtree_size)) {
        (current == parent->left ? parent->left : parent->right) =
            NaiveRebalance(current);
        // NaiveRebalance(current == parent->left ? parent->left :
        // parent->right);
        return true;
      }
      subtree_size +=
          1 + TreeSize(current == parent->left ? parent->right : parent->left);
      current = parent;
    }
    node = NaiveRebalance(node);
    return true;
  }

  static bool Delete(Node*& node, const T& x, int size, int max_size) {
    Node *parent = nullptr, *current = node;
    // Find the node to be deleted;
    while (current != nullptr && current->value != x) {
      parent = current;
      current = (x < current->value) ? current->left : current->right;
    }
    // The node cannot be found.
    if (current == nullptr) return false;
    // When the node needed to be removed has two children, pull the minimum
    // value from the right tree and delete the minimum value in the right
    // tree.
    if (current->left != nullptr && current->right != nullptr) {
      Node* min = current->right;
      for (parent = current; min->left != nullptr; min = min->left) {
        parent = min;
      }
      current->value = min->value;
      current = min;
    }
    // When the node needed to be removed has one child, move the non-null
    // subtree up. If both subtrees are null, then set the node to be null.
    Node* sub_tree =
        (current->left != nullptr ? current->left : current->right);
    // If root node will be deleted.
    if (parent == nullptr)
      node = sub_tree;
    else
      (parent->left == current ? parent->left : parent->right) = sub_tree;
    delete current;
    if (--size < alpha * max_size) node = NaiveRebalance(node);
    return true;
  }

  Node* root_ = nullptr;
  int size = 0;
  int max_size = 0;
  static constexpr double log_sqrt2 = 2.88539008178;
  static constexpr double alpha = 0.707106781186548;  // 1 / sqrt(2.0).
};

#endif
