#ifndef TREAP_H
#define TREAP_H

#include <random>
#include <vector>

#include "../binary-search-tree-common/binary_search_tree_common.h"

template <typename T>
struct Treap {
 public:
  struct Node {
    using value_type = T;
    explicit Node(const T& x) : value(x) {}
    Node(Node* l, Node* r) : left(l), right(r) {}
    Node() = default;
    Node* left = nullptr;
    Node* right = nullptr;
    double priority = random();
    T value;

    // Generate random priority.
    static double random() {
      static std::random_device random_device;
      static std::default_random_engine generator{random_device()};
      static std::uniform_real_distribution<> distribution;
      return distribution(generator);
    }
  };

  bool Insert(const T& x) { return Insert(root_, x); }

  bool Delete(const T& x) {
    Node** parent_pointer = &root_;
    while (*parent_pointer != nullptr && !(x == (*parent_pointer)->value)) {
      parent_pointer = (x < (*parent_pointer)->value)
                           ? &(*parent_pointer)->left
                           : &(*parent_pointer)->right;
    }
    if (*parent_pointer == nullptr) return false;
    // Rotate the node until the node does not have two children.
    while ((*parent_pointer)->left && (*parent_pointer)->right) {
      Node*& current = *parent_pointer;
      if (current->left->priority < current->right->priority) {
        RightRotate(current);
        parent_pointer = &current->right;
      } else {
        LeftRotate(current);
        parent_pointer = &current->left;
      }
    }
    Node* to_be_delete = *parent_pointer;
    *parent_pointer = (to_be_delete->left != nullptr) ? to_be_delete->left
                                                      : to_be_delete->right;
    delete to_be_delete;
    return true;
  }

  // Insert a value without using rotation.
  void InsertWithoutRotation(const T& x) {
    Node* new_node = new Node(x);
    Node** parent_pointer = &root_;
    while (*parent_pointer != nullptr &&
           new_node->priority > (*parent_pointer)->priority) {
      Node*& current = *parent_pointer;
      parent_pointer = (x < current->value) ? &current->left : &current->right;
    }
    if (*parent_pointer != nullptr)
      Split(*parent_pointer, x, new_node->left, new_node->right);
    *parent_pointer = new_node;
  }

  // Delete a value without using rotation.
  bool DeleteWithoutRotation(const T& x) {
    Node** parent_pointer = &root_;
    while (*parent_pointer != nullptr && (*parent_pointer)->value != x) {
      Node*& current = *parent_pointer;
      parent_pointer = (x < current->value) ? &current->left : &current->right;
    }
    if (*parent_pointer == nullptr) return false;
    Node* to_be_delete = *parent_pointer;
    Join(*parent_pointer, (*parent_pointer)->left, (*parent_pointer)->right);
    delete to_be_delete;
    return true;
  }

  ~Treap() { FreeTree(root_); }

  void InorderTraverse(std::vector<T>& result) const {
    return ::InorderTraverse(root_, result);
  }

  bool IsHeap() { return IsHeap(root_); }

  Node* root() const { return root_; }

  Node*& root() { return root_; }

 private:
  static bool Insert(Node*& node, const T& x) {
    if (node == nullptr) {
      node = new Node(x);
      return true;
    }
    if (x == node->value) return false;
    if (x < node->value) {
      if (Insert(node->left, x) == false) return false;
      if (node->left->priority < node->priority) RightRotate(node);
    } else {
      if (Insert(node->right, x) == false) return false;
      if (node->right->priority < node->priority) LeftRotate(node);
    }
    return true;
  }

  static bool IsHeap(const Node* node) {
    if (node == nullptr) return true;
    if (node->left != nullptr && node->priority > node->left->priority)
      return false;
    if (node->right != nullptr && node->priority > node->right->priority)
      return false;
    return IsHeap(node->left) && IsHeap(node->right);
  }

  // Split the subtree rooted at node, so that all nodes that are smaller than
  // x is rooted at left, and other nodes are rooted at right.
  static void Split(Node* node, const T& x, Node*& left, Node*& right) {
    Node **left_pointer = &left, **right_pointer = &right;
    while (node != nullptr && x != node->value) {
      if (x < node->value) {
        *right_pointer = node;
        right_pointer = &node->left;
        node = node->left;
      } else {
        *left_pointer = node;
        left_pointer = &node->right;
        node = node->right;
      }
    }
    *left_pointer = *right_pointer = nullptr;
  }

  // Merge the trees that are rooted at left and right as node.
  static void Join(Node*& node, Node* left, Node* right) {
    Node** parent_pointer = &node;
    while (left != nullptr && right != nullptr) {
      if (left->priority < right->priority) {
        *parent_pointer = left;
        parent_pointer = &left->right;
        left = left->right;
      } else {
        *parent_pointer = right;
        parent_pointer = &right->left;
        right = right->left;
      }
    }
    *parent_pointer = left != nullptr ? left : right;
  }

  Node* root_ = nullptr;
};
#endif
