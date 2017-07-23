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
    union {
      Node* link[2] = {nullptr, nullptr};
      struct {
        Node* left;
        Node* right;
      };
    };
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

  bool Delete(const T& x) { return Delete(root_, x); }

  // Insert a value without using rotation.
  void InsertWithoutRotation(const T& x) { InsertWithoutRotation(root_, x); }

  // Delete a value without using rotation.
  bool DeleteWithoutRotation(const T& x) {
    return DeleteWithoutRotation(root_, x);
  }

  ~Treap() { FreeTree(root_); }

  void InorderTraverse(std::vector<T>& result) const {
    return ::InorderTraverse(root_, result);
  }

  bool IsHeap() const { return IsHeap(root_); }

  Node* root() const { return root_; }

  Node*& root() { return root_; }

 private:
  static bool IsHeap(const Node* node) {
    if (node == nullptr) return true;
    if (node->left != nullptr && node->priority > node->left->priority)
      return false;
    if (node->right != nullptr && node->priority > node->right->priority)
      return false;
    return IsHeap(node->left) && IsHeap(node->right);
  }

  static bool Insert(Node*& node, const T& x) {
    if (node == nullptr) {
      node = new Node(x);
      return true;
    }
    if (x == node->value) return false;
    bool is_right = x >= node->value;
    if (!Insert(node->link[is_right], x)) return false;
    if (node->link[is_right]->priority < node->priority)
      node = Rotate(node, !is_right);
    return true;
  }

  static bool Delete(Node*& node, const T& x) {
    Node dummy{node, node}, *parent = &dummy, *current = node;
    while (current != nullptr && x != current->value) {
      parent = current;
      current = x < current->value ? current->left : current->right;
    }
    if (current == nullptr) return false;
    bool is_right = (parent == &dummy ? false : current == parent->right);
    // Rotate the node until the node does not have two children.
    while (current->left && current->right) {
      bool next_is_right = current->left->priority < current->right->priority;
      parent->link[is_right] = Rotate(current, next_is_right);
      parent = parent->link[is_right];
      current = parent->link[next_is_right];
      is_right = next_is_right;
    }
    parent->link[is_right] =
        current->left == nullptr ? current->right : current->left;
    node = dummy.link[0];
    delete current;
    return true;
  }

  // Insert a value without using rotation.
  static void InsertWithoutRotation(Node*& node, const T& x) {
    if (node == nullptr) {
      node = new Node(x);
      return;
    }
    Node *new_node = new Node(x), *parent = nullptr, *current = node;
    while (current != nullptr && new_node->priority > current->priority) {
      parent = current;
      current = x < current->value ? current->left : current->right;
    }
    Split(current, x, new_node);
    if (parent == nullptr)
      node = new_node;
    else
      (x < parent->value ? parent->left : parent->right) = new_node;
  }

  // Delete a value without using rotation.
  static bool DeleteWithoutRotation(Node*& node, const T& x) {
    Node *parent = nullptr, *current = node;
    while (current != nullptr && current->value != x) {
      parent = current;
      current = (x < current->value) ? current->left : current->right;
    }
    if (current == nullptr) return false;
    if (parent == nullptr)
      Join(node, current);
    else
      Join(parent->left == current ? parent->left : parent->right, current);
    delete current;
    return true;
  }

  // Split the subtree rooted at node, so that all nodes that are smaller than
  // x is rooted at result->left, and other nodes are rooted at result->right.
  static void Split(Node* node, const T& x, Node* result) {
    // trees[0] stores right tree, trees[1] stores left tree.
    Node* trees[2] = {result, result};
    bool sub_tree_is_right[2] = {true, false};
    while (node != nullptr && x != node->value) {
      bool is_right = x >= node->value;
      trees[is_right]->link[sub_tree_is_right[is_right]] = node;
      trees[is_right] = node;
      sub_tree_is_right[is_right] = is_right;
      node = node->link[is_right];
    }
    trees[0]->link[sub_tree_is_right[0]] =
        trees[1]->link[sub_tree_is_right[1]] = nullptr;
  }

  // Merge the subtrees of current->left and current->right as node.
	// Note: On my machine, using links to implement this method tends to be
	// slower.
  static void Join(Node*& node, Node* current) {
    Node *left = current->left, *right = current->right;
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

  // is_right == false -> LeftRotate(root)
  // is_right == true -> RightRotate(root)
  template <typename Node>
  static Node* Rotate(Node* root, bool is_right) {
    Node* x = root->link[!is_right];
    root->link[!is_right] = x->link[is_right];
    x->link[is_right] = root;
    return x;
  }

  Node* root_ = nullptr;
};
#endif
