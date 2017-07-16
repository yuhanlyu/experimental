#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <vector>

#include "../binary-search-tree-common/binary_search_tree_common.h"

template <typename T>
struct BinarySearchTree {
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
    // When the tree is empty, create the node at root;
    if (root_ == nullptr) {
      root_ = new Node(x);
      return true;
    }
    Node* parent;
    for (Node* current = root_; current != nullptr;) {
      if (current->value == x) return false;
      parent = current;
      current = (x < current->value) ? current->left : current->right;
    }
    ((x < parent->value) ? parent->left : parent->right) = new Node(x);
    return true;
  }

  bool Delete(const T& x) {
    Node *parent = nullptr, *current = root_;
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
      for (parent = current; min->left != nullptr; min = min->left)
        parent = min;
      current->value = min->value;
      current = min;
    }
    // When the node needed to be removed has one child, move the non-null
    // subtree up. If both subtrees are null, then set the node to be null.
    Node* subtree = (current->left != nullptr ? current->left : current->right);
    // If root node will be deleted.
    if (parent == nullptr)
      root_ = subtree;
    else
      (parent->left == current ? parent->left : parent->right) = subtree;
    delete current;
    return true;
  }

  bool InsertRec(const T& x) { return InsertRec(root_, x); }

	bool DeleteRec(const T& x) { return DeleteRec(root_, x); }

  ~BinarySearchTree() { FreeTree(root_); }

  void InorderTraverse(std::vector<T>& result) const {
    return ::InorderTraverse(root_, result);
  }

  Node* root() const { return root_; }

  Node*& root() { return root_; }

 private:

  static bool InsertRec(Node*& node, const T& x) {
    // When the tree is empty, create the node at root;
    if (node == nullptr) {
      node = new Node(x);
      return true;
    }
    if (x == node->value) return false;
		return InsertRec(x < node->value ? node->left : node->right, x);
  }

  static bool DeleteRec(Node*& node, const T& x) {
    if (node == nullptr) return false;
		if (x == node->value) {
			if (node->left == nullptr || node->right == nullptr) {
      	// When the node needed to be removed has one child, move the non-null
      	// subtree up. If both subtrees are null, then set the node to be null.
      	Node* old_node = node;
      	node = (node->left != nullptr) ? node->left : node->right;
      	delete old_node;
				return true;
			}
    	// When the node needed to be removed has two children, pull the minimum
    	// value from the right tree and delete the minimum value in the right
    	// tree.
     	Node *parent = node, *min = node->right;
     	for (; min->left != nullptr; min = min->left) parent = min;
     	node->value = min->value;
     	(parent->left == min ? parent->left : parent->right) = min->right;
     	delete min;
    	return true;
		} 
		return DeleteRec(x < node->value ? node->left : node->right, x);
  }

  Node* root_ = nullptr;
};

#endif
