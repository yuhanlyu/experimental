#ifndef WEIGHT_BALANCED_TREE_H
#define WEIGHT_BALANCED_TREE_H

#include <type_traits>
#include <vector>

#include "../binary-search-tree-common/binary_search_tree_common.h"

#define ROTATION(root, left, right) \
  do {                              \
    Node* x = (root)->right;        \
    (root)->right = x->left;        \
    x->left = (root);               \
    (root) = x;                     \
    calculate_size(x->left);        \
    calculate_size(root);           \
  } while (false)

#define DOUBLE_ROTATION(root, left, right) \
  do {                                     \
    Node *x = (root)->right, *y = x->left; \
    x->left = y->right;                    \
    (root)->right = y->left;               \
    y->left = (root);                      \
    y->right = x;                          \
    (root) = y;                            \
    calculate_size2(root);                 \
  } while (false)

#define INSERT_HELPER(x, current, left, right, mode)                         \
  do {                                                                       \
    if (!is_balanced_after_insert((current)->right, (current)->left)) {      \
      Node* child = (current)->right;                                        \
      if (need_single_rotation_after_insert(child->left, child->right,       \
                                            (mode) == ((x) < child->value))) \
        ROTATION(current, left, right);                                      \
      else                                                                   \
        DOUBLE_ROTATION(current, left, right);                               \
    }                                                                        \
  } while (false)

#define DELETE_HELPER(current, left, right)                                 \
  do {                                                                      \
    if (!is_balanced_after_remove((current)->left, (current)->right)) {     \
      Node* child = (current)->right;                                       \
      if (need_single_rotation_after_remove((child)->left, (child)->right)) \
        ROTATION(current, left, right);                                     \
      else                                                                  \
        DOUBLE_ROTATION(current, left, right);                              \
    }                                                                       \
  } while (false)

#define DELETE_MIN(to_be_delete, parent_pointer, left, right)                 \
  do {                                                                        \
    (parent_pointer) = &(to_be_delete)->right;                                \
    while ((*(parent_pointer))->left != nullptr) {                            \
      Node*& current = *(parent_pointer);                                     \
      if (!is_balanced_after_remove((current)->left, (current)->right)) {     \
        Node* child = (current)->right;                                       \
        if (need_single_rotation_after_remove((child)->left, (child)->right)) \
          ROTATION(current, left, right);                                     \
        else                                                                  \
          DOUBLE_ROTATION(current, left, right);                              \
      }                                                                       \
      --(current)->size;                                                      \
      (parent_pointer) = &(current)->left;                                    \
    }                                                                         \
  } while (false)

template <typename T>
struct WeightBalancedTree {
 public:
  struct Node {
    using value_type = T;
    explicit Node(const T& x) : value(x) {}
    explicit Node(Node* l, Node* r) : left(l), right(r) {}
    Node() = default;
    Node* left = nullptr;
    Node* right = nullptr;
    int size = 1;
    T value;
  };

  // Left<true>(node) returns node->left, Left<false>(node) returns node->right.
  template <bool mode, typename std::enable_if<mode>::type* = nullptr>
  static Node*& Left(Node* node) {
    return node->left;
  }
  template <bool mode, typename std::enable_if<!mode>::type* = nullptr>
  static Node*& Left(Node* node) {
    return node->right;
  }

  // Right<true>(node) returns node->left, Right<false>(node) returns
  // node->left.
  template <bool mode, typename std::enable_if<mode>::type* = nullptr>
  static Node*& Right(Node* node) {
    return node->right;
  }
  template <bool mode, typename std::enable_if<!mode>::type* = nullptr>
  static Node*& Right(Node* node) {
    return node->left;
  }

  void Insert(const T& x) {
    // When the tree is empty, create the node at root;
    if (root_ == nullptr) {
      root_ = new Node(x);
      return;
    }

    Node** parent_pointer = &root_;
    while (*parent_pointer != nullptr) {
      Node*& current = *parent_pointer;
      // Rotate the tree when the size is imbalanced.
      if (x < current->value) {
        if (!is_balanced_after_insert(current->left, current->right)) {
          Node* child = current->left;
          need_single_rotation_after_insert(child->right, child->left,
                                            x > child->value)
              ? RightRotation(current)
              : LRRotation(current);
        }
      } else {
        if (!is_balanced_after_insert(current->right, current->left)) {
          Node* child = current->right;
          need_single_rotation_after_insert(child->left, child->right,
                                            x < child->value)
              ? LeftRotation(current)
              : RLRotation(current);
        }
      }
      // Since the tree might be rotated, the subtree needed to be inserted
      // might change.
      ++current->size;
      parent_pointer = x < current->value ? &current->left : &current->right;
    }
    *parent_pointer = new Node(x);
  }

  void Delete(const T& x) {
    Node** parent_pointer = &root_;
    while (*parent_pointer != nullptr) {
      Node*& current = *parent_pointer;
      if (current->value == x) break;
      // Rotate the tree when the size is imbalanced.
      if (x < current->value) {
        if (!is_balanced_after_remove(current->left, current->right)) {
          Node* child = current->right;
          need_single_rotation_after_remove(child->left, child->right)
              ? LeftRotation(current)
              : RLRotation(current);
        }
      } else {
        if (!is_balanced_after_remove(current->right, current->left)) {
          Node* child = current->left;
          need_single_rotation_after_remove(child->right, child->left)
              ? RightRotation(current)
              : LRRotation(current);
        }
      }
      // Since the tree might be rotated, the subtree needed to be removed
      // might change.
      --current->size;
      parent_pointer = x < current->value ? &current->left : &current->right;
    }
    Node* to_be_delete = *parent_pointer;
    if (to_be_delete == nullptr) return;
    // When the node needed to be removed has two children, pull the minimum
    // value from the right tree and delete the minimum value in the right
    // tree.
    if (to_be_delete->left != nullptr && to_be_delete->right != nullptr) {
      --to_be_delete->size;
      // If the right subtree size is larger, then promote the minimum of the
      // right subtree.
      if (size(to_be_delete->right) > size(to_be_delete->left)) {
        parent_pointer = &to_be_delete->right;
        while ((*parent_pointer)->left != nullptr) {
          Node*& current = *parent_pointer;
          if (!is_balanced_after_remove(current->left, current->right)) {
            Node* child = current->right;
            need_single_rotation_after_remove(child->left, child->right)
                ? LeftRotation(current)
                : RLRotation(current);
          }
          --current->size;
          parent_pointer = &current->left;
        }
      } else {
        // If the left subtree size is larger, then promote the maximum of the
        // left subtree.
        parent_pointer = &to_be_delete->left;
        while ((*parent_pointer)->right != nullptr) {
          Node*& current = *parent_pointer;
          if (!is_balanced_after_remove(current->right, current->left)) {
            Node* child = current->left;
            need_single_rotation_after_remove(child->right, child->left)
                ? RightRotation(current)
                : LRRotation(current);
          }
          --current->size;
          parent_pointer = &current->right;
        }
      }
      to_be_delete->value = (*parent_pointer)->value;
      to_be_delete = *parent_pointer;
    }
    // When the node needed to be removed has one child, move the non-null
    // subtree up. If both subtrees are null, then set the node to be null.
    *parent_pointer = (to_be_delete->left != nullptr ? to_be_delete->left
                                                     : to_be_delete->right);
    delete to_be_delete;
  }

  void InsertTemplate(const T& x) {
    // When the tree is empty, create the node at root;
    if (root_ == nullptr) {
      root_ = new Node(x);
      return;
    }

    Node** parent_pointer = &root_;
    while (*parent_pointer != nullptr) {
      Node*& current = *parent_pointer;
      // Rotate the tree when the size is imbalanced.
      x < current->value ? InsertHelper<false>(x, current)
                         : InsertHelper<true>(x, current);
      // Since the tree might be rotated, the subtree needed to be inserted
      // might change.
      ++current->size;
      parent_pointer = x < current->value ? &current->left : &current->right;
    }
    *parent_pointer = new Node(x);
  }

  void DeleteTemplate(const T& x) {
    Node** parent_pointer = &root_;
    while (*parent_pointer != nullptr) {
      Node*& current = *parent_pointer;
      if (current->value == x) break;
      // Rotate the tree when the size is imbalanced.
      x < current->value ? DeleteHelper<true>(current)
                         : DeleteHelper<false>(current);
      // Since the tree might be rotated, the subtree needed to be removed
      // might change.
      --current->size;
      parent_pointer = x < current->value ? &current->left : &current->right;
    }
    Node* to_be_delete = *parent_pointer;
    if (to_be_delete == nullptr) return;
    // When the node needed to be removed has two children, pull the minimum
    // value from the right tree and delete the minimum value in the right
    // tree.
    if (to_be_delete->left != nullptr && to_be_delete->right != nullptr) {
      --to_be_delete->size;
      // If the right subtree size is larger, then promote the minimum of the
      // right subtree. Otherwise, promote the maximum of the left subtree.
      size(to_be_delete->right) > size(to_be_delete->left)
          ? DeleteMin<true>(to_be_delete, parent_pointer)
          : DeleteMin<false>(to_be_delete, parent_pointer);
      to_be_delete->value = (*parent_pointer)->value;
      to_be_delete = *parent_pointer;
    }
    // When the node needed to be removed has one child, move the non-null
    // subtree up. If both subtrees are null, then set the node to be null.
    *parent_pointer = (to_be_delete->left != nullptr ? to_be_delete->left
                                                     : to_be_delete->right);
    delete to_be_delete;
  }

  void InsertMacro(const T& x) {
    // When the tree is empty, create the node at root;
    if (root_ == nullptr) {
      root_ = new Node(x);
      return;
    }

    Node** parent_pointer = &root_;
    while (*parent_pointer != nullptr) {
      Node*& current = *parent_pointer;
      // Rotate the tree when the size is imbalanced.
      if (x < current->value)
        INSERT_HELPER(x, current, right, left, false);
      else
        INSERT_HELPER(x, current, left, right, true);
      // Since the tree might be rotated, the subtree needed to be inserted
      // might change.
      ++current->size;
      parent_pointer = x < current->value ? &current->left : &current->right;
    }
    *parent_pointer = new Node(x);
  }

  void DeleteMacro(const T& x) {
    Node** parent_pointer = &root_;
    while (*parent_pointer != nullptr) {
      Node*& current = *parent_pointer;
      if (current->value == x) break;
      // Rotate the tree when the size is imbalanced.
      if (x < current->value)
        DELETE_HELPER(current, left, right);
      else
        DELETE_HELPER(current, right, left);
      // Since the tree might be rotated, the subtree needed to be removed
      // might change.
      --current->size;
      parent_pointer = x < current->value ? &current->left : &current->right;
    }
    Node* to_be_delete = *parent_pointer;
    if (to_be_delete == nullptr) return;
    // When the node needed to be removed has two children, pull the minimum
    // value from the right tree and delete the minimum value in the right
    // tree.
    if (to_be_delete->left != nullptr && to_be_delete->right != nullptr) {
      --to_be_delete->size;
      // If the right subtree size is larger, then promote the minimum of the
      // right subtree. Otherwise, promote the maximum of the left subtree.
      if (size(to_be_delete->right) > size(to_be_delete->left))
        DELETE_MIN(to_be_delete, parent_pointer, left, right);
      else
        DELETE_MIN(to_be_delete, parent_pointer, right, left);
      to_be_delete->value = (*parent_pointer)->value;
      to_be_delete = *parent_pointer;
    }
    // When the node needed to be removed has one child, move the non-null
    // subtree up. If both subtrees are null, then set the node to be null.
    *parent_pointer = (to_be_delete->left != nullptr ? to_be_delete->left
                                                     : to_be_delete->right);
    delete to_be_delete;
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

  bool IsBalanced() const { return IsBalanced(root_); }

  ~WeightBalancedTree() { FreeTree(root_); }

  void InorderTraverse(std::vector<T>& result) const {
    return ::InorderTraverse(root_, result);
  }

  Node* root() const { return root_; }

  Node*& root() { return root_; }

 private:
  static bool IsBalanced(Node* node) {
    if (node == nullptr) return true;
    return delta * weight(node->left) >= weight(node->right) &&
           delta * weight(node->right) >= weight(node->left) &&
           IsBalanced(node->left) && IsBalanced(node->right);
  }

  static int weight(Node* node) { return size(node) + 1; }

  static int size(Node* node) { return node == nullptr ? 0 : node->size; }

  // Calaulte the size for a given node.
  static void calculate_size(Node* node) {
    node->size = size(node->left) + size(node->right) + 1;
  }

  // Bottom-up calculate the sizes for two levels for a given node.
  static void calculate_size2(Node* node) {
    calculate_size(node->left);
    calculate_size(node->right);
    node->size = node->left->size + node->right->size + 1;
  }

  // Test whether the tree is balanced after the node is inserted.
  static bool is_balanced_after_insert(Node* insert, Node* other) {
    return delta * weight(other) >= weight(insert) + 1;
  }

  // Test whether the tree needs single rotation after the node is inserted.
  static bool need_single_rotation_after_insert(Node* inner, Node* outer,
                                                bool insert_inner) {
    return weight(inner) + insert_inner <
           gamma * (weight(outer) + !insert_inner);
  }

  // Test whether the tree is balanced after the node is removed.
  static bool is_balanced_after_remove(Node* remove, Node* other) {
    return delta * (weight(remove) - 1) >= weight(other);
  }

  // Test whether the tree needs single rotation after the node is removed.
  static bool need_single_rotation_after_remove(Node* inner, Node* outer) {
    return weight(inner) < gamma * weight(outer);
  }

  // Rotate the subtree when necessary during the insert.
  template <bool mode>
  static void InsertHelper(const T& x, Node*& current) {
    if (!is_balanced_after_insert(Right<mode>(current), Left<mode>(current))) {
      Node* child = Right<mode>(current);
      // When mode is true and x < child->value, then x will be inserted to
      // inner. Similarly, when mode is false and x > child->value, then x will
      // be inserted to inner.
      need_single_rotation_after_insert(Left<mode>(child), Right<mode>(child),
                                        mode == (x < child->value))
          ? LeftRotation<mode>(current)
          : RLRotation<mode>(current);
    }
  }

  // Rotate the subtree when necessary during the delete.
  template <bool mode>
  static void DeleteHelper(Node*& current) {
    if (!is_balanced_after_remove(Left<mode>(current), Right<mode>(current))) {
      Node* child = Right<mode>(current);
      need_single_rotation_after_remove(Left<mode>(child), Right<mode>(child))
          ? LeftRotation<mode>(current)
          : RLRotation<mode>(current);
    }
  }

  // When mode is true, find the minimum value of the right subtree of current
  // and assign the minimum value to the current. Then, set the current to be
  // the minimum node. During the traversal, rotate the tree if the tree will
  // become imbalanced after the minimum node is deleted. In the end of the
  // function, the parent_pointer will be the pointer in the parent of minimum
  // node pointing to the minimum node.
  // The case of mode=false is symmetric for finding the maximum value of the
  // left subtree of current.
  template <bool mode>
  static void DeleteMin(Node*& to_be_delete, Node**& parent_pointer) {
    parent_pointer = &Right<mode>(to_be_delete);
    while (Left<mode>(*parent_pointer) != nullptr) {
      Node*& current = *parent_pointer;
      if (!is_balanced_after_remove(Left<mode>(current),
                                    Right<mode>(current))) {
        Node* child = Right<mode>(current);
        need_single_rotation_after_remove(Left<mode>(child), Right<mode>(child))
            ? LeftRotation<mode>(current)
            : RLRotation<mode>(current);
      }
      --current->size;
      parent_pointer = &Left<mode>(current);
    }
  }

  // LeftRotation<true> is left rotation.
  //    root           x    |
  //    /  \          / \   |
  //   a    x   To root  c  |
  //       / \     /  \     |
  //      b    c  a    b    |
  // LeftRotation<false> is right rotation.
  //    root          x       |
  //    /  \         / \      |
  //   x    c  To   a  root   |
  //  / \              /  \   |
  // a   b            b    c  |
  template <bool mode>
  static void LeftRotation(Node*& root) {
    Node* x = Right<mode>(root);
    Right<mode>(root) = Left<mode>(x);
    Left<mode>(x) = root;
    root = x;
    calculate_size(Left<mode>(x));
    calculate_size(x);
  }

  // RLRotation<true> is RL rotation, which is a right rotation followed by a
  // left rotation.
  //    root              y        |
  //    /  \            /   \      |
  //   a    x         root   x     |
  //       / \   To   / \   / \    |
  //      y   d      a   b c   d   |
  //     / \                       |
  //    b   c                      |
  // RLRotation<false> is LR rotation, which is a left rotation followed by a
  // right rotation.
  //    root             y         |
  //    /  \           /   \       |
  //   x    d         x    root    |
  //  / \      To    / \   /  \    |
  // a   y          a   b c    d   |
  //    / \                        |
  //   b   c                       |
  template <bool mode>
  static void RLRotation(Node*& root) {
    Node *x = Right<mode>(root), *y = Left<mode>(x);
    Left<mode>(x) = Right<mode>(y);
    Right<mode>(root) = Left<mode>(y);
    Left<mode>(y) = root;
    Right<mode>(y) = x;
    root = y;
    calculate_size2(root);
  }

  // Left rotation:
  //    root           x    |
  //    /  \          / \   |
  //   a    x   To root  c  |
  //       / \     /  \     |
  //      b    c  a    b    |
  static void LeftRotation(Node*& root) {
    Node* x = root->right;
    root->right = x->left;
    x->left = root;
    root = x;
    calculate_size(x->left);
    calculate_size(x);
  }

  // Right rotation:
  //    root          x       |
  //    /  \         / \      |
  //   x    c  To   a  root   |
  //  / \              /  \   |
  // a   b            b    c  |
  static void RightRotation(Node*& root) {
    Node* x = root->left;
    root->left = x->right;
    x->right = root;
    root = x;
    calculate_size(x->right);
    calculate_size(x);
  }

  // LR rotation:
  //    root             y         |
  //    /  \           /   \       |
  //   x    d         x    root    |
  //  / \      To    / \   /  \    |
  // a   y          a   b c    d   |
  //    / \                        |
  //   b   c                       |
  static void LRRotation(Node*& root) {
    Node *x = root->left, *y = x->right;
    x->right = y->left;
    root->left = y->right;
    y->left = x;
    y->right = root;
    root = y;
    calculate_size2(root);
  }

  // RL rotation:
  //    root              y        |
  //    /  \            /   \      |
  //   a    x         root   x     |
  //       / \   To   / \   / \    |
  //      y   d      a   b c   d   |
  //     / \                       |
  //    b   c                      |
  static void RLRotation(Node*& root) {
    Node *x = root->right, *y = x->left;
    x->left = y->right;
    root->right = y->left;
    y->left = root;
    y->right = x;
    root = y;
    calculate_size2(root);
  }

  Node* root_ = nullptr;
  static constexpr int delta = 3;
  static constexpr int gamma = 2;
};

#endif
