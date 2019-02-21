#ifndef WAVL_H
#define WAVL_H

#include <vector>

#include "../binary-search-tree-common/binary_search_tree_common.h"

template <typename T>
struct WAVL {
 public:
  struct Node {
    using value_type = T;
    explicit Node(const T& x) : value(x), rank_parity(false) {}
    Node(Node* l, Node* r) : left(l), right(r) {}
    Node() = default;
    Node* left = sentinel;
    Node* right = sentinel;
    T value;
    bool rank_parity = true;  // Used by sentinel, represent rank -1.
  };

  bool Insert(const T& x) {
    if (root_ == sentinel) {
      root_ = new Node(x);
      return true;
    }
    Node **parent = &root_, **safe_node = &root_;
    bool parent_parity = root_->rank_parity;
    // Find the safe node and the place to insert node.
		for (Node* current = *parent; current != sentinel; current = *parent) {
      if (x == current->value) return false;
      // if current is a 2-child node or is a 1, 2 node, then we found a safe
			// node.
      if (current->rank_parity == parent_parity ||
          current->left->rank_parity != current->right->rank_parity) {
        safe_node = parent;
      }
      parent_parity = current->rank_parity;
      parent = x < current->value ? &current->left : &current->right;
    }
    *parent = new Node(x);
    Node*& node = *safe_node;
    // Promote all nodes below the safe_node.
    for (Node* current = x < node->value ? node->left : node->right;
         current != *parent;) {
      current->rank_parity = !current->rank_parity;
      current = x < current->value ? current->left : current->right;
    }
    if (x < node->value) {
			// When the new inserted node is a 1-child, no rebalance is required.
      if (node->rank_parity != node->left->rank_parity) return true;

      // After this, the new inserted node is a 0-child.
      // For either promote/rotate, the parity will change.
      node->rank_parity = !node->rank_parity;
      const bool old_rank_parity = !node->rank_parity;

			// If current node is a 1, 2 node, then we are done.
      if (old_rank_parity != node->right->rank_parity) return true;

      // Rotate according to node->left->right->parity.
      if (old_rank_parity == node->left->right->rank_parity) {
        RightRotate(node);
      } else {
        node->left->rank_parity = !node->left->rank_parity;
        node->left->right->rank_parity = !node->left->right->rank_parity;
        LRRotate(node);
      }
    } else {
			// When the new inserted node is a 1-child, no rebalance is required.
      if (node->rank_parity != node->right->rank_parity) return true;

      // After this, the new inserted node is a 0-child.
      // For either promote/rotate, the parity will change.
      node->rank_parity = !node->rank_parity;
      const bool old_rank_parity = !node->rank_parity;

			// If current node is a 1, 2 node, then we are done.
      if (old_rank_parity != node->left->rank_parity) return true;

      // Rotate according to node->right->left->rank_parity.
      if (old_rank_parity == node->right->left->rank_parity) {
        LeftRotate(node);
      } else {
        node->right->rank_parity = !node->right->rank_parity;
        node->right->left->rank_parity = !node->right->left->rank_parity;
        RLRotate(node);
      }
    }
    return true;
  }

	// TODO: Finish implementation and test.
  bool Delete(const T& x) {
    Node **parent = &root_, **safe_node = &root_, *current;
    bool parent_parity = root_->rank_parity;
    const T* delete_value = &x;
    // Find the safe node and the place to delete node.
		for (current = *parent; current != sentinel; current = *parent) {
      if (x == current->value) break;
      // When current node is 2-child of parent or current node is a (1, 2) node
      // safe_node is set to parent.
			if (IsSafeNodeForDelete(current, parent_parity)) safe_node = parent;
      parent_parity = current->rank_parity;
      parent = x < current->value ? &current->left : &current->right;
    }
		if (current == sentinel) return false;
    // When the node needed to be removed has two children, pull the minimum
    // value from the right tree and delete the minimum value in the right
    // tree.
		if (current->left != sentinel && current->right != sentinel) {
      Node* min = current->right;
      for (parent = &current->right; min->left != sentinel; min = min->left) {
			  if (IsSafeNodeForDelete(min, parent_parity)) safe_node = parent;
        parent_parity = min->rank_parity;
        parent = &min->left;
      }
      current->value = min->value;
      delete_value = &current->value;
      current = min;
    }
		// Removes the leave.
		*parent = current->left != sentinel ? current->left : current->right;
		delete current;

		Node*& node = *safe_node;
    // Demote all nodes below the safe_node.
    for (current = *delete_value < node->value ? node->left : node->right;
         current != *parent;) {
      current->rank_parity = !current->rank_parity;
      current = *delete_value < current->value ? current->left : current->right;
    }
 
    return true;
  }

  bool RecursiveInsert(const T& x) {
    bool done = false;
    return Insert(root_, x, done);
  }

  bool RecursiveDelete(const T& x) {
    bool done = false;
    return Delete(root_, x, done);
  }

  bool IsBalanced() const { return ValidateRank(root_) != -1; }

  ~WAVL() { FreeTree(root_, sentinel); }

  void InorderTraverse(std::vector<T>& result) const {
    return ::InorderTraverse(root_, result, sentinel);
  }

  void PrintTree() const { return PrintTree(root_, "root"); }

  Node* root() const { return root_; }

  Node*& root() { return root_; }

 private:
  static void PrintTree(const Node* root, std::string prefix) {
    if (root == sentinel) return;
    PrintTree(root->left, prefix + "->left");
    std::cerr << prefix << " = " << root->value << " with " << root->rank_parity
              << '\n';
    PrintTree(root->right, prefix + "->right");
  }

  static int ValidateRank(const Node* node) {
    if (node == sentinel) return 0;
    int left_rank = ValidateRank(node->left);
    int right_rank = ValidateRank(node->right);
    if (left_rank == -1 || right_rank == -1) return -1;
		// No 2, 2 leaf.
    if (left_rank == 0 && right_rank == 0 &&
        node->rank_parity == node->left->rank_parity)
      return -1;
    left_rank += (node->rank_parity == node->left->rank_parity ? 2 : 1);
    right_rank += (node->rank_parity == node->right->rank_parity ? 2 : 1);
		// Left tree's rank must be equalt to right tree's rank.
    if (left_rank != right_rank) return -1;
    return left_rank;
  }

  static bool Insert(Node*& node, const T& x, bool& done) {
    // When the tree is empty, create the node at root;
    if (node == sentinel) {
      node = new Node(x);
      return true;
    }
    if (x == node->value) return false;
    if (x < node->value) {
      if (!Insert(node->left, x, done)) return false;
      if (done) return true;
			// When the new inserted node is a 1-child, no rebalance is required.
      if (node->rank_parity != node->left->rank_parity) return done = true;

      // After this, the new inserted node is a 0-child.
      // For either promote/rotate, the parity will change.
      node->rank_parity = !node->rank_parity;
      const bool old_rank_parity = !node->rank_parity;

			// If current node is a 0, 1 node, then upper layer should rebalance.
      if (old_rank_parity != node->right->rank_parity) return true;

      // Rotate according to node->left->right->parity.
      if (old_rank_parity == node->left->right->rank_parity) {
        RightRotate(node);
      } else {
        node->left->rank_parity = !node->left->rank_parity;
        node->left->right->rank_parity = !node->left->right->rank_parity;
        LRRotate(node);
      }
    } else {
      if (!Insert(node->right, x, done)) return false;
      if (done) return true;
			// When the new inserted node is a 1-child, no rebalance is required.
      if (node->rank_parity != node->right->rank_parity) return done = true;

      // After this, the new inserted node is a 0-child.
      // For either promote/rotate, the parity will change.
      node->rank_parity = !node->rank_parity;
      const bool old_rank_parity = !node->rank_parity;

			// If current node is a 0, 1 node, then upper layer should rebalance.
      if (old_rank_parity != node->left->rank_parity) return true;

      // Rotate according to node->right->left->rank_parity.
      if (old_rank_parity == node->right->left->rank_parity) {
        LeftRotate(node);
      } else {
        node->right->rank_parity = !node->right->rank_parity;
        node->right->left->rank_parity = !node->right->left->rank_parity;
        RLRotate(node);
      }
    }
    return done = true;
  }

  static bool Delete(Node*& node, const T& x, bool& done) {
    if (node == sentinel) return false;
    const T* delete_value = &x;
    if (x == node->value) {
      if (node->left == sentinel || node->right == sentinel) {
        Node* to_be_deleted = node;
        node = node->left == sentinel ? node->right : node->left;
        delete to_be_deleted;
        return true;
      }
      Node* successor = node->right;
      while (successor->left != sentinel) successor = successor->left;
      node->value = successor->value;
      delete_value = &node->value;
    }
    if (*delete_value < node->value) {
      if (!Delete(node->left, *delete_value, done)) return false;
      if (done) return true;
      // If the rank difference between left and current is 2.
      if (node->rank_parity == node->left->rank_parity) {
        // When node is not leaf, no rebalancing is required.
        if (node->left != sentinel || node->right != sentinel)
          return done = true;
        // Leaf node cannot has rank 1.
        node->rank_parity = !node->rank_parity;
        return true;
      }
      // At this point, the rank difference between left and current is 3.
      // If the rank difference between right and current is 2, demote.
      if (node->rank_parity == node->right->rank_parity) {
        node->rank_parity = !node->rank_parity;
        return true;
      }
      // If the rank difference between right and current is 1, and node->right
      // can be demote, then demote current and right.
      if (node->right->rank_parity == node->right->left->rank_parity &&
          node->right->rank_parity == node->right->right->rank_parity) {
        node->rank_parity = !node->rank_parity;
        node->right->rank_parity = !node->right->rank_parity;
        return true;
      }
      done = true;
      node->right->rank_parity = !node->right->rank_parity;
      if (node->rank_parity != node->right->right->rank_parity) {
        RLRotate(node);
        return true;
      }
      if (node->left != sentinel || node->right->left != sentinel)
        node->rank_parity = !node->rank_parity;
      LeftRotate(node);
    } else {
      if (!Delete(node->right, *delete_value, done)) return false;
      if (done) return true;
      // If the rank difference between right and current is 2.
      if (node->rank_parity == node->right->rank_parity) {
        // When node is not leaf, no rebalancing is required.
        if (node->left != sentinel || node->right != sentinel)
          return done = true;
        node->rank_parity = !node->rank_parity;
        return true;
      }
      // At this point, the rank difference between right and current is 3.
      // If the rank difference between left and current is 2, demote.
      if (node->rank_parity == node->left->rank_parity) {
        node->rank_parity = !node->rank_parity;
        return true;
      }
      // If the rank difference between left and current is 1, and node->left
      // can be demote, then demote current and left.
      if (node->left->rank_parity == node->left->left->rank_parity &&
          node->left->rank_parity == node->left->right->rank_parity) {
        node->rank_parity = !node->rank_parity;
        node->left->rank_parity = !node->left->rank_parity;
        return true;
      }
      done = true;
      node->left->rank_parity = !node->left->rank_parity;
      if (node->rank_parity != node->left->left->rank_parity) {
        LRRotate(node);
        return true;
      }
      if (node->right != sentinel || node->left->right != sentinel)
        node->rank_parity = !node->rank_parity;
      RightRotate(node);
    }
    return true;
  }

	static bool IsSafeNodeForDelete(Node* current, bool parent_parity) {
		// If current is a 1-child, then current is a safe node.
		if (current->rank_parity != parent_parity) return true;
		// After this, current is a 2-child.
		// If current is a 2, 2 node, then current is not a safe node.
		if (current->left->rank_parity == current->right->rank_parity) return false;
		Node* one_child = current->rank_parity != current->left->rank_parity ?
			current->left : current->right;
		// If the 1-child is not a 2, 2, node, then current is a safe node.
		return one_child->left->rank_parity != one_child->right->rank_parity;
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

  static inline Node dummy;
  static constexpr Node* sentinel = &dummy;
  Node* root_ = sentinel;
};

#endif
