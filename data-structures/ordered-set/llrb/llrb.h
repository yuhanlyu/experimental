#ifndef LLRB_H
#define LLRB_H

#include <vector>

#include "../binary-search-tree-common/binary_search_tree_common.h"

template <typename T>
struct LLRB {
 public:
  struct Node {
    using value_type = T;
    explicit Node(const T& x, bool is_red = true) : value(x), red(is_red) {}
    Node() = default;
    Node* left = sentinel;
    Node* right = sentinel;
    T value;
    bool red = false;
  };

  bool Insert(const T& x) {
    bool inserted = Insert(root_, x);
    root_->red = false;
    return inserted;
  }

  bool Delete(const T& x) {
    bool deleted = Delete(root_, x);
    root_->red = false;
    return deleted;
  }

  bool IsBalanced() const {
    if (sentinel->red) return false;
    if (sentinel->right != sentinel) return false;
    if (sentinel->left != sentinel) return false;
    if (root_->red) return false;
    return BlackHeight(root_) != -1;
  }

  ~LLRB() { FreeTree(root_, sentinel); }

  void InorderTraverse(std::vector<T>& result) const {
    return ::InorderTraverse(root_, result, sentinel);
  }

  Node* root() const { return root_; }

  Node*& root() { return root_; }

  void PrintTree() const { PrintTree(root_, "root"); }

  static void PrintTree(const Node* root, std::string prefix) {
    if (root == sentinel) return;
    PrintTree(root->left, prefix + "->left");
    std::cerr << prefix << " = " << root->value << ' '
              << (root->red ? 'R' : 'B') << '\n';
    PrintTree(root->right, prefix + "->right");
  }

 private:
  static int BlackHeight(const Node* node) {
    if (node == sentinel) return 1;
    if (node->right->red) return -1;
    if (node->red && node->left->red) return -1;
    int lh = BlackHeight(node->left), rh = BlackHeight(node->right);
    if (lh == -1 || rh == -1 || lh != rh) return -1;
    return lh + (node->red ? 0 : 1);
  }

  static bool Insert(Node*& node, const T& x) {
    if (node == sentinel) {
      node = new Node(x);
      return true;
    }
    if (x == node->value) return false;
    if (x < node->value) {
      if (!Insert(node->left, x)) return false;
    } else {
      if (!Insert(node->right, x)) return false;
    }
    // Enforce left-leaning.
    if (node->right->red) {
      // The current node might be red or black;
      node->right->red = node->red;
      node->red = true;
      LeftRotate(node);
    }
    // No two reds in a row.
    if (node->left->red && node->left->left->red) {
      // The current node must be black. Rotate and flip color.
      node->left->left->red = false;
      RightRotate(node);
      return true;
    }
    // When two children are red, flip color.
    if (node->left->red && node->right->red) {
      node->left->red = node->right->red = false;
      node->red = true;
    }
    return true;
  }

  static bool Delete(Node*& node, const T& x) {
    if (node == sentinel) return false;
    bool deleted = false;
    if (x < node->value) {
      // When node's left child and grand child are black, move the red left.
      if (node->left != sentinel && !node->left->red &&
          !node->left->left->red) {
        node->red = false;
        node->left->red = true;
        if (node->right->left->red)
          RLRotate(node);
        else
          node->right->red = true;
      }
      deleted = Delete(node->left, x);
    } else {
      // When the left is red, move the red to the right.
      if (node->left->red) {
        node->left->red = false;
        node->red = true;
        RightRotate(node);
      }
      // Delete a leaf.
      if (x == node->value && node->right == sentinel) {
        delete node;
        node = sentinel;
        return true;
      }
      // When node's right and left of right are black, move the red to right.
      // Current node must be red now.
      if (node->right != sentinel && !node->right->red &&
          !node->right->left->red) {
        node->red = false;
        node->left->red = node->right->red = true;
        if (node->left->left->red) {
          node->left->left->red = false;
          RightRotate(node);
        }
      }
      // When the target value is found, replaced the node by the successor.
      if (x == node->value) {
        Node* successor = node->right;
        while (successor->left != sentinel) successor = successor->left;
        node->value = successor->value;
        deleted = Delete(node->right, successor->value);
      } else
        deleted = Delete(node->right, x);
    }
    // Enforce left leaning.
    if (node->right->red) {
      node->right->red = false;
      node->red = true;
      LeftRotate(node);
    }
    // No two reds in a row.
    if (node->left->red && node->left->left->red) {
      node->left->left->red = false;
      RightRotate(node);
      return deleted;
    }
    // Flip color to enforce 2-3 tree.
    if (node->left->red && node->right->red) {
      node->left->red = node->right->red = false;
      node->red = true;
    }
    return deleted;
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
    x->left = y->right;
    root->right = y->left;
    y->left = root;
    y->right = x;
    root = y;
  }

  static Node dummy;
  static constexpr Node* sentinel = &dummy;

  Node* root_ = sentinel;
};

// TODO(C++17): use inline variable.
template <typename T>
typename LLRB<T>::Node LLRB<T>::dummy;
#endif