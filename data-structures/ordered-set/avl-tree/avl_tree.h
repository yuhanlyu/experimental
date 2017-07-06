#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <vector>

#include "../binary-search-tree-common/binary_search_tree_common.h"

template <typename T>
struct AVLTree {
 public:
  struct Node {
    using value_type = T;
    explicit Node(const T& x) : value(x) {}
    Node(Node* l, Node* r) : left(l), right(r) {}
    Node() = default;
    Node* left = nullptr;
    Node* right = nullptr;
    T value;
    signed char balance_factor = 0;
  };

  bool RecursiveInsert(const T& x) {
    bool done = false;
    return Insert(root_, x, done);
  }

  bool Insert(const T& x) {
    if (root_ == nullptr) {
      root_ = new Node(x);
      return true;
    }
    Node **parent = &root_, **safe_guard = &root_;
    // Find the lowest node that has non zero balance_factor as safe_guard,
    // and the position to be inserted as parent.
    while ((*parent) != nullptr) {
      Node*& current = *parent;
      if (current->balance_factor != 0) safe_guard = parent;
      if (x == current->value) return false;
      parent = x < current->value ? &current->left : &current->right;
    }
    *parent = new Node(x);
    // Update balance_factor on the path from safe_guard to parent.
    for (Node* current = *safe_guard; current->value != x;) {
      if (x < current->value) {
        --current->balance_factor;
        current = current->left;
      } else {
        ++current->balance_factor;
        current = current->right;
      }
    }
    Node*& node = *safe_guard;
    // Rebalance the safe_guard.
    if (node->balance_factor == -2) {
      if (node->left->balance_factor == -1) {
        node->balance_factor = node->left->balance_factor = 0;
        RightRotate(node);
      } else
        LRRotate(node);
    } else if (node->balance_factor == 2) {
      if (node->right->balance_factor == 1) {
        node->balance_factor = node->right->balance_factor = 0;
        LeftRotate(node);
      } else
        RLRotate(node);
    }
    return true;
  }

  bool Delete(const T& x) {
    bool done = false;
    return Delete(root_, x, done);
  }

  bool IsBalanced() const { return ValidateHeight(root_) != -1; }

  ~AVLTree() { FreeTree(root_); }

  void InorderTraverse(std::vector<T>& result) const {
    return ::InorderTraverse(root_, result);
  }

  Node* root() const { return root_; }

  Node*& root() { return root_; }

 private:
  static int ValidateHeight(const Node* node) {
    if (node == nullptr) return 0;
    int left_height = ValidateHeight(node->left);
    if (left_height == -1) return -1;
    int right_height = ValidateHeight(node->right);
    if (right_height == -1) return -1;
    if (right_height - left_height != node->balance_factor) return -1;
    return std::max(left_height, right_height) + 1;
  }

  static bool Insert(Node*& node, const T& x, bool& done) {
    // When the tree is empty, create the node at root;
    if (node == nullptr) {
      node = new Node(x);
      return true;
    }
    if (x == node->value) return false;
    if (x < node->value) {
      if (!Insert(node->left, x, done)) return false;
      // The balance_factor changes from 0 to -1 -> the height of the subtree
      // increases, propagate up to rebalance the tree.
      if (done || --node->balance_factor == -1) return true;
      // At this point, node->balance_factor is either 0 or -2.
      done = true;
      // The balance_factor changes from 1 to 0, the height of the subtree does
      // not change, we are done.
      if (node->balance_factor == 0) return true;
      // When node->balance_factor is -2, rotation is required.
      // node->left->balance_factor is either 1 or -1.
      if (node->left->balance_factor == -1) {
        node->balance_factor = node->left->balance_factor = 0;
        RightRotate(node);
      } else
        LRRotate(node);
    } else {
      if (!Insert(node->right, x, done)) return false;
      // The balance_factor changes from 0 to 1 -> the height of the subtree
      // increases, propagate up to rebalance the tree.
      if (done || ++node->balance_factor == 1) return true;
      // At this point, node->balance_factor is either 0 or 2.
      done = true;
      // The balance_factor changes from -1 to 0, the height of the subtree does
      // not change, we are done.
      if (node->balance_factor == 0) return true;
      // When node->balance_factor is 2, rotation is required.
      // node->right->balance_factor is either 1 or -1.
      if (node->right->balance_factor == 1) {
        node->balance_factor = node->right->balance_factor = 0;
        LeftRotate(node);
      } else
        RLRotate(node);
    }
    return true;
  }

  static bool Delete(Node*& node, const T& x, bool& done) {
    if (node == nullptr) return false;
    const T* delete_value = &x;
    if (x == node->value) {
      if (node->left == nullptr || node->right == nullptr) {
        Node* to_be_deleted = node;
        node = node->left == nullptr ? node->right : node->left;
        delete to_be_deleted;
        return true;
      }
      Node* successor = node->right;
      while (successor->left != nullptr) successor = successor->left;
      node->value = successor->value;
      delete_value = &node->value;
    }
    if (*delete_value < node->value) {
      if (!Delete(node->left, *delete_value, done)) return false;
      // The balance_factor changes from -1 to 0 -> the height of the subtree
      // decreases, propagate up to rebalance the tree.
      if (done || ++node->balance_factor == 0) return true;
      // The balance_factor changes from 0 to 1, the height of the subtree does
      // not change, we are done.
      if (node->balance_factor == 1) return done = true;
      // node->right->balance_factor can be either 0, 1, -1.
      if (node->right->balance_factor != -1) {
        if (node->right->balance_factor == 1) {
          node->balance_factor = node->right->balance_factor = 0;
        } else {
          done = true;
          node->balance_factor = 1;
          node->right->balance_factor = -1;
        }
        LeftRotate(node);
      } else
        RLRotate(node);
    } else {
      if (!Delete(node->right, *delete_value, done)) return false;
      // The balance_factor changes from 1 to 0 -> the height of the subtree
      // decreases, propagate up to rebalance the tree.
      if (done || --node->balance_factor == 0) return true;
      // The balance_factor changes from 0 to -1, the height of the subtree does
      // not change, we are done.
      if (node->balance_factor == -1) return done = true;
      // node->left->balance_factor can be either 0, 1, -1.
      if (node->left->balance_factor != 1) {
        if (node->left->balance_factor == -1) {
          node->balance_factor = node->left->balance_factor = 0;
        } else {
          done = true;
          node->balance_factor = -1;
          node->left->balance_factor = 1;
        }
        RightRotate(node);
      } else
        LRRotate(node);
    }
    return true;
  }

  // Left rotation:
  //    root           x    |
  //    /  \          / \   |
  //   a    x   To root  c  |
  //       / \     /  \     |
  //      b    c  a    b    |
  static void LeftRotate(Node*& root) {
    Node* x = root->right;
    root->right = x->left;
    x->left = root;
    root = x;
  }

  // Right rotation:
  //    root          x       |
  //    /  \         / \      |
  //   x    c  To   a  root   |
  //  / \              /  \   |
  // a   b            b    c  |
  static void RightRotate(Node*& root) {
    Node* x = root->left;
    root->left = x->right;
    x->right = root;
    root = x;
  }

  // LR rotation:
  //    root             y         |
  //    /  \           /   \       |
  //   x    d         x    root    |
  //  / \      To    / \   /  \    |
  // a   y          a   b c    d   |
  //    / \                        |
  //   b   c                       |
  static void LRRotate(Node*& root) {
    Node *x = root->left, *y = x->right;
    if (y->balance_factor == 0) {
      x->balance_factor = root->balance_factor = 0;
    } else if (y->balance_factor == -1) {
      x->balance_factor = 0;
      root->balance_factor = 1;
    } else {
      x->balance_factor = -1;
      root->balance_factor = 0;
    }
    y->balance_factor = 0;
    x->right = y->left;
    root->left = y->right;
    y->left = x;
    y->right = root;
    root = y;
  }

  // RL rotation:
  //    root              y        |
  //    /  \            /   \      |
  //   a    x         root   x     |
  //       / \   To   / \   / \    |
  //      y   d      a   b c   d   |
  //     / \                       |
  //    b   c                      |
  static void RLRotate(Node*& root) {
    Node *x = root->right, *y = x->left;
    if (y->balance_factor == 0) {
      x->balance_factor = root->balance_factor = 0;
    } else if (y->balance_factor == 1) {
      x->balance_factor = 0;
      root->balance_factor = -1;
    } else {
      x->balance_factor = 1;
      root->balance_factor = 0;
    }
    y->balance_factor = 0;
    x->left = y->right;
    root->right = y->left;
    y->left = root;
    y->right = x;
    root = y;
  }

  Node* root_ = nullptr;
};
#endif
