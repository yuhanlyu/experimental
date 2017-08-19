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
    union {
      Node* link[2] = {nullptr, nullptr};
      struct {
        Node* left;
        Node* right;
      };
    };
    T value;
    signed char balance_factor = 0;
  };

  bool RecursiveInsert(const T& x) {
    bool done = false;
    return RecursiveInsert(root_, x, done);
  }

  bool Insert(const T& x) { return Insert(root_, x); }

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

  static bool Insert(Node*& node, const T& x) {
    if (node == nullptr) {
      node = new Node(x);
      return true;
    }
    Node **parent = &node, **safe_node = &node;
    // Find the lowest node that has non zero balance_factor as safe_node,
    // and the position to be inserted as parent.
    while ((*parent) != nullptr) {
      Node*& current = *parent;
      if (x == current->value) return false;
      if (current->balance_factor != 0) safe_node = parent;
      parent = x < current->value ? &current->left : &current->right;
    }
    *parent = new Node(x);
    // Update balance_factor on the path from safe_node to parent.
    for (Node* current = *safe_node; current->value != x;) {
      if (x < current->value) {
        --current->balance_factor;
        current = current->left;
      } else {
        ++current->balance_factor;
        current = current->right;
      }
    }
    if (std::abs((*safe_node)->balance_factor) < 2) return true;
    Node*& update_node = *safe_node;
    bool is_right = x >= update_node->value;
    // At this point, node->balance_factor is either 2 or -2.
    // When balance_factor has different signs with the inserted subtree's
    // balance_factor, double rotation.
    if ((update_node->link[is_right]->balance_factor ^
         update_node->balance_factor) < 0) {
      update_node = DoubleRotate(update_node, is_right);
      return true;
    }
    // When balance_factor has the same sign with the inserted subtree's
    // balance_factor, single rotation.
    update_node->balance_factor = update_node->link[is_right]->balance_factor =
        0;
    update_node = Rotate(update_node, is_right);
    return true;
  }

  static bool RecursiveInsert(Node*& node, const T& x, bool& done) {
    if (node == nullptr) {
      node = new Node(x);
      return true;
    }
    if (x == node->value) return false;
    bool is_right = x >= node->value;
    if (!RecursiveInsert(node->link[is_right], x, done)) return false;
    if (done) return true;
    node->balance_factor += is_right * 2 - 1;
    // If the balance_factor changes from 0 to 1 or -1, propagate up to
    // rebalance the tree.
    if (node->balance_factor == is_right * 2 - 1) return true;
    // At this point, node->balance_factor is either 0, 2, or -2.
    done = true;
    // The balance_factor changes from 1 or -1 to 0, the height of the subtree
    // does not change, we are done.
    if (node->balance_factor == 0) return true;
    // At this point, node->balance_factor is either 2 or -2.
    // When balance_factor has different signs with the inserted subtree's
    // balance_factor, double rotation.
    if ((node->link[is_right]->balance_factor ^ node->balance_factor) < 0) {
      node = DoubleRotate(node, is_right);
      return true;
    }
    // When balance_factor has the same sign with the inserted subtree's
    // balance_factor, single rotation.
    node->balance_factor = node->link[is_right]->balance_factor = 0;
    node = Rotate(node, is_right);
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
        node = LeftRotate(node);
      } else
        node = RLRotate(node);
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
        node = RightRotate(node);
      } else
        node = LRRotate(node);
    }
    return true;
  }

  // Left rotation:
  //    root           x    |
  //    /  \          / \   |
  //   a    x   To root  c  |
  //       / \     /  \     |
  //      b    c  a    b    |
  static Node* LeftRotate(Node* root) {
    Node* x = root->right;
    root->right = x->left;
    x->left = root;
    return x;
  }

  // Right rotation:
  //    root          x       |
  //    /  \         / \      |
  //   x    c  To   a  root   |
  //  / \              /  \   |
  // a   b            b    c  |
  static Node* RightRotate(Node* root) {
    Node* x = root->left;
    root->left = x->right;
    x->right = root;
    return x;
  }

  // LR rotation:
  //    root             y         |
  //    /  \           /   \       |
  //   x    d         x    root    |
  //  / \      To    / \   /  \    |
  // a   y          a   b c    d   |
  //    / \                        |
  //   b   c                       |
  static Node* LRRotate(Node* root) {
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
    return y;
  }

  // RL rotation:
  //    root              y        |
  //    /  \            /   \      |
  //   a    x         root   x     |
  //       / \   To   / \   / \    |
  //      y   d      a   b c   d   |
  //     / \                       |
  //    b   c                      |
  static Node* RLRotate(Node* root) {
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
    return y;
  }

  // Left rotation, when left_rotate = true
  //    root           x    |
  //    /  \          / \   |
  //   a    x   To root  c  |
  //       / \     /  \     |
  //      b    c  a    b    |
  // otherwise, right rotation.
  static Node* Rotate(Node* root, bool left_rotate) {
    Node* x = root->link[left_rotate];
    root->link[left_rotate] = x->link[!left_rotate];
    x->link[!left_rotate] = root;
    return x;
  }

  // RL rotation, when rl_rotate = true.
  //    root              y        |
  //    /  \            /   \      |
  //   a    x         root   x     |
  //       / \   To   / \   / \    |
  //      y   d      a   b c   d   |
  //     / \                       |
  //    b   c                      |
  // Otherwise, LRrotation.
  static Node* DoubleRotate(Node* root, bool rl_rotate) {
    Node *x = root->link[rl_rotate], *y = x->link[!rl_rotate];
    if (y->balance_factor == 0) {
      x->balance_factor = root->balance_factor = 0;
    } else if (y->balance_factor == 2 * rl_rotate - 1) {
      x->balance_factor = 0;
      root->balance_factor = -y->balance_factor;
    } else {
      x->balance_factor = -y->balance_factor;
      root->balance_factor = 0;
    }
    y->balance_factor = 0;
    x->link[!rl_rotate] = y->link[rl_rotate];
    root->link[rl_rotate] = y->link[!rl_rotate];
    y->link[!rl_rotate] = root;
    y->link[rl_rotate] = x;
    return y;
  }

  Node* root_ = nullptr;
};
#endif
