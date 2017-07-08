#ifndef WAVL_H
#define WAVL_H

#include <sstream>
#include <vector>

#include "../binary-search-tree-common/binary_search_tree_common.h"

template <typename T>
struct WAVL {
 public:
  struct Node {
    using value_type = T;
    explicit Node(const T& x) : value(x) {}
    Node(Node* l, Node* r) : left(l), right(r) {}
    Node() = default;
    std::string ToString() const {
      std::ostringstream stream;
      stream << value << " (" << left_rd_one << ", " << right_rd_one << ")";
      return stream.str();
    }
    Node* left = nullptr;
    Node* right = nullptr;
    T value;
    // rd_one means the parity of the rank difference between node and child.
    // rd_one = false means the difference is 2, or 0 (temporarily in
    // insertion).
    // rd_one = true means the difference is 1, or 3 (temporarily in deletion).
    bool left_rd_one = true;
    bool right_rd_one = true;
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
    Node **parent = &root_, **safe_node = &root_;
    // Find the lowest node that has non zero balance_factor as safe_node,
    // and the position to be inserted as parent.
    while ((*parent) != nullptr) {
      Node*& current = *parent;
      if (x == current->value) return false;
      // When the has a 2 child, the node is a safe_node.
      // USING bitwise or is faster than logical or.
      if (!current->left_rd_one | !current->right_rd_one) safe_node = parent;
      parent = x < current->value ? &current->left : &current->right;
    }
    *parent = new Node(x);
    Node*& node = *safe_node;
    // Promote all nodes below the safe_node.
    for (Node* current = x < node->value ? node->left : node->right;
         current != *parent;) {
      if (x < current->value) {
        current->right_rd_one = false;
        current = current->left;
      } else {
        current->left_rd_one = false;
        current = current->right;
      }
    }
    if (x < node->value) {
      node->left_rd_one = !node->left_rd_one;
      // At this point, rank difference between current and left is either 0 or
      // 1.
      if (node->left_rd_one) return true;
      // At this point, rank difference between current and left is 0.
      // At this point, rank difference between current and right is either 1 or
      // 2.
      if (node->right_rd_one) {
        node->right_rd_one = false;
        return node->left_rd_one = true;
      }
      // At this point, rank difference between current and right is 2.
      if (!node->left->left_rd_one) {
        node->left_rd_one = node->left->right->right_rd_one;
        node->left->right_rd_one = node->left->right->left_rd_one;
        node->right_rd_one = node->left->left_rd_one =
            node->left->right->left_rd_one = node->left->right->right_rd_one =
                true;
        LRRotate(node);
      } else {
        node->right_rd_one = node->left_rd_one = node->left->right_rd_one =
            true;
        RightRotate(node);
      }
    } else {
      node->right_rd_one = !node->right_rd_one;
      // At this point, rank difference between current and right is either 0 or
      // 1.
      if (node->right_rd_one) return true;
      // At this point, rank difference between current and right is 0.
      // At this point, rank difference between current and left is either 1 or
      // 2.
      if (node->left_rd_one) {
        node->left_rd_one = false;
        return node->right_rd_one = true;
      }
      // At this point, rank difference between current and left is or 2.
      if (!node->right->right_rd_one) {
        node->right_rd_one = node->right->left->left_rd_one;
        node->right->left_rd_one = node->right->left->right_rd_one;
        node->left_rd_one = node->right->right_rd_one =
            node->right->left->left_rd_one = node->right->left->right_rd_one =
                true;
        RLRotate(node);
      } else {
        node->right->left_rd_one = node->left_rd_one = node->right_rd_one =
            true;
        LeftRotate(node);
      }
    }
    return true;
  }

  bool Delete(const T& x) { return true; }

  bool RecursiveDelete(const T& x) {
    bool done = false;
    return Delete(root_, x, done);
  }

  bool IsBalanced() const { return ValidateRank(root_) != -1; }

  ~WAVL() { FreeTree(root_); }

  void InorderTraverse(std::vector<T>& result) const {
    return ::InorderTraverse(root_, result);
  }

  void PrintTree() const { return PrintTree(root_, "root"); }

  Node* root() const { return root_; }

  Node*& root() { return root_; }

 private:
  static void PrintTree(const Node* root, std::string prefix) {
    if (root == nullptr) return;
    PrintTree(root->left, prefix + "->left");
    std::cerr << prefix << " = " << root->ToString() << '\n';
    PrintTree(root->right, prefix + "->right");
  }

  static int ValidateRank(const Node* node) {
    if (node == nullptr) return 0;
    int left_rank = ValidateRank(node->left);
    int right_rank = ValidateRank(node->right);
    if (left_rank == -1 || right_rank == -1) return -1;
    if (left_rank == 0 && right_rank == 0 && !node->left_rd_one &&
        !node->right_rd_one)
      return -1;
    left_rank += node->left_rd_one ? 1 : 2;
    right_rank += node->right_rd_one ? 1 : 2;
    if (left_rank != right_rank) return -1;
    return left_rank;
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
      if (done) return true;
      node->left_rd_one = !node->left_rd_one;
      // At this point, rank difference between current and left is either 0 or
      // 1.
      if (node->left_rd_one) return done = true;
      // At this point, rank difference between current and left is 0.
      // At this point, rank difference between current and right is either 1 or
      // 2.
      if (node->right_rd_one) {
        node->right_rd_one = false;
        return node->left_rd_one = true;
      }
      done = true;
      // At this point, rank difference between current and right is 2.
      if (!node->left->left_rd_one) {
        node->left_rd_one = node->left->right->right_rd_one;
        node->left->right_rd_one = node->left->right->left_rd_one;
        node->right_rd_one = node->left->left_rd_one =
            node->left->right->left_rd_one = node->left->right->right_rd_one =
                true;
        LRRotate(node);
      } else {
        node->right_rd_one = node->left_rd_one = node->left->right_rd_one =
            true;
        RightRotate(node);
      }
    } else {
      if (!Insert(node->right, x, done)) return false;
      if (done) return true;
      node->right_rd_one = !node->right_rd_one;
      // At this point, rank difference between current and right is either 0 or
      // 1.
      if (node->right_rd_one) return done = true;
      // At this point, rank difference between current and right is 0.
      // At this point, rank difference between current and left is either 1 or
      // 2.
      if (node->left_rd_one) {
        node->left_rd_one = false;
        return node->right_rd_one = true;
      }
      done = true;
      // At this point, rank difference between current and left is 2.
      if (!node->right->right_rd_one) {
        node->right_rd_one = node->right->left->left_rd_one;
        node->right->left_rd_one = node->right->left->right_rd_one;
        node->left_rd_one = node->right->right_rd_one =
            node->right->left->left_rd_one = node->right->left->right_rd_one =
                true;
        RLRotate(node);
      } else {
        node->right->left_rd_one = node->left_rd_one = node->right_rd_one =
            true;
        LeftRotate(node);
      }
    }
    return true;
  }

  static bool Delete(Node*& node, const T& x, bool& done) {
    if (node == nullptr) return false;
    const T* delete_value = &x;
    if (*delete_value == node->value) {
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
      if (done) return true;
      node->left_rd_one = !node->left_rd_one;
      // At this pont, rank difference between current and left is either 2 or
      // 3.
      if (!node->left_rd_one) {
        // When node is not leaf, no rebalancing is required.
        if (node->left != nullptr || node->right != nullptr) return done = true;
        // Leaf node must be 1, 1.
        return node->left_rd_one = node->right_rd_one = true;
      }
      // At this point, rank difference between current and left is 3.
      // At this point, rank difference between current and right is 1 or 2.
      if (!node->right_rd_one) {
        node->left_rd_one = false;
        return node->right_rd_one = true;
      }
      // At this point, rank difference between current and right is 1.
      // If right can be demoted, then demote current and right.
      if (!node->right->left_rd_one && !node->right->right_rd_one) {
        node->left_rd_one = false;
        return node->right->left_rd_one = node->right->right_rd_one = true;
      }
      done = true;
      // At this point, rank difference between right and right->right is either
      // 1 or 2.
      if (!node->right->right_rd_one) {
        // At this point, rank difference between right and right->left is 1.
        node->right_rd_one = node->right->left->left_rd_one;
        node->right->left_rd_one = node->right->left->right_rd_one;
        RLRotate(node);
        node->left_rd_one = node->right_rd_one = false;
        return node->right->right_rd_one = true;
      }
      // At this point, rank difference between right and right->right is 1.
      node->right_rd_one = node->right->left_rd_one;
      LeftRotate(node);
      node->left_rd_one = true;
      node->right_rd_one = node->left->left_rd_one = false;
      // When left is a leaf, demote left.
      if (node->left->left == nullptr && node->left->right == nullptr) {
        node->left->left_rd_one = node->left->right_rd_one = true;
        node->left_rd_one = false;
      }
    } else {
      if (!Delete(node->right, *delete_value, done)) return false;
      if (done) return true;
      node->right_rd_one = !node->right_rd_one;
      // At this pont, rank difference between current and right is either 2 or
      // 3.
      if (!node->right_rd_one) {
        // When node is not leaf, no rebalancing is required.
        if (node->left != nullptr || node->right != nullptr) return done = true;
        // Leaf node must be 1, 1.
        return node->left_rd_one = node->right_rd_one = true;
      }
      // At this point, rank difference between current and right is 3.
      // At this point, rank difference between current and left is 1 or 2.
      if (!node->left_rd_one) {
        node->right_rd_one = false;
        return node->left_rd_one = true;
      }
      // At this point, rank difference between current and left is 1.
      // If left can be demoted, then demote current and left.
      if (!node->left->left_rd_one && !node->left->right_rd_one) {
        node->right_rd_one = false;
        return node->left->left_rd_one = node->left->right_rd_one = true;
      }
      done = true;
      // At this point, rank difference between left and left->left is either 1
      // or 2.
      if (!node->left->left_rd_one) {
        // At this point, rank difference between left and left->right is 1.
        node->left_rd_one = node->left->right->right_rd_one;
        node->left->right_rd_one = node->left->right->left_rd_one;
        LRRotate(node);
        node->left_rd_one = node->right_rd_one = false;
        return node->left->left_rd_one = true;
      }
      // At this point, rank difference between left and left->left is 1.
      node->left_rd_one = node->left->right_rd_one;
      RightRotate(node);
      node->right_rd_one = true;
      node->left_rd_one = node->right->right_rd_one = false;
      // When right is a leaf, demote right.
      if (node->right->left == nullptr && node->right->right == nullptr) {
        node->right->left_rd_one = node->right->right_rd_one = true;
        node->right_rd_one = false;
      }
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

  Node* root_ = nullptr;
};

#endif
