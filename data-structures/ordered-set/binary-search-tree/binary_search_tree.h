#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <vector>

#include "../binary-search-tree-common/binary_search_tree_common.h"

// Find the pointer from the parent to the node with the minimum value.
template <typename T>
T*& FindMinPtr(T** node) {
  while ((*node)->left != nullptr) node = &(*node)->left;
  return *node;
}

template <typename T>
struct BinarySearchTree {
 public:
  struct Node {
    using value_type = T;
    explicit Node(const T& x) : value(x) {}
    Node() = default;
    Node* left = nullptr;
    Node* right = nullptr;
    T value;
  };

  bool Insert(const T& x) {
    // When the tree is empty, create the node at root;
    if (root_ == nullptr) {
      root_ = new Node(x);
      return true;
    }
    Node* parent;
    for (Node* current = root_; current != nullptr;) {
      parent = current;
      if (current->value == x) return false;
      current = (x < current->value) ? current->left : current->right;
    }
    ((x < parent->value) ? parent->left : parent->right) = new Node(x);
    return true;
  }

  bool InsertRec(const T& x) { return InsertRec(root_, x); }

  bool Remove(const T& x) { return Remove(&root_, x); }

  bool RemoveRec(const T& x) { return RemoveRec(root_, x); }

  ~BinarySearchTree() { FreeTree(root_); }

  void InorderTraverse(std::vector<T>& result) const {
    return ::InorderTraverse(root_, result);
  }

  Node* root() const { return root_; }

 private:
  static bool InsertRec(Node*& node, const T& x) {
    // When the tree is empty, create the node at root;
    if (node == nullptr) {
      node = new Node(x);
      return true;
    }
    if (x == node->value) return false;
    return (x < node->value) ? InsertRec(node->left, x)
                             : InsertRec(node->right, x);
  }

  static bool Remove(Node** node, const T& x) {
    while (*node != nullptr) {
      Node& current = **node;
      if (x < current.value)
        node = &current.left;
      else if (x > current.value)
        node = &current.right;
      else
        break;
    }
    if (*node == nullptr) return false;
    Node& current = **node;
    // When the node needed to be removed has two children, pull the minimum
    // value from the right tree and delete the minimum value in the right
    // tree.
    if (current.left != nullptr && current.right != nullptr) {
      Node*& min_ptr = FindMinPtr(&current.right);
      current.value = min_ptr->value;
      Node* old_node = min_ptr;
      min_ptr = min_ptr->right;
      delete old_node;
    } else {
      // When the node needed to be removed has one child, move the non-null
      // subtree up. If both subtrees are null, then set the node to be null.
      *node = (current.left != nullptr) ? current.left : current.right;
      delete &current;
    }
    return true;
  }

  static bool RemoveRec(Node*& node, const T& x) {
    if (node == nullptr) return false;
    if (x < node->value) return RemoveRec(node->left, x);
    if (x > node->value) return RemoveRec(node->right, x);
    // When the node needed to be removed has two children, pull the minimum
    // value from the right tree and delete the minimum value in the right
    // tree.
    if (node->left != nullptr && node->right != nullptr) {
      Node*& min_ptr = FindMinPtr(&node->right);
      node->value = min_ptr->value;
      Node* old_node = min_ptr;
      min_ptr = min_ptr->right;
      delete old_node;
    } else {
      // When the node needed to be removed has one child, move the non-null
      // subtree up. If both subtrees are null, then set the node to be null.
      Node* old_node = node;
      node = (node->left != nullptr) ? node->left : node->right;
      delete old_node;
    }
    return true;
  }

  Node* root_ = nullptr;
};

#endif
