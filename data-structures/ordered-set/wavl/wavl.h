#ifndef WAVL_H
#define WAVL_H

#include <vector>

#include "../binary-search-tree-common/binary_search_tree_common.h"

template <typename T>
struct WAVL {
 public:
  struct alignas(32) Node {
    using value_type = T;
    explicit Node(const T& x) : value(x), odd_rank(false) {}
    Node(Node* l, Node* r) : left(l), right(r) {}
    Node() = default;
    Node* left = sentinel;
    Node* right = sentinel;
    T value;
    bool odd_rank = true;  // Used by sentinel, represent rank -1.
  };

  bool Insert(const T& x) {
    if (root_ == sentinel) {
      root_ = new Node(x);
      return true;
    }
    Node **parent = &root_, **safe_node = &root_;
    bool parent_parity = root_->odd_rank;
    // Find the safe node and the place to insert node.
    for (Node* current = *parent; current != sentinel; current = *parent) {
      if (x == current->value) return false;
      // if current is a 2-child node or is a 1, 2 node, then we found a safe
      // node.
      if (current->odd_rank == parent_parity ||
          current->left->odd_rank != current->right->odd_rank) {
        safe_node = parent;
      }
      parent_parity = current->odd_rank;
      parent = x < current->value ? &current->left : &current->right;
    }
    *parent = new Node(x);
    Node*& node = *safe_node;
    // Promote all nodes below the safe_node.
    for (Node* current = x < node->value ? node->left : node->right;
         current != *parent;) {
      current->odd_rank = !current->odd_rank;
      current = x < current->value ? current->left : current->right;
    }
    if (x < node->value) {
      // When the new inserted node is a 1-child, no rebalance is required.
      if (node->odd_rank != node->left->odd_rank) return true;

      // After this, the new inserted node is a 0-child.
      // For either promote/rotate, the parity will change.
      node->odd_rank = !node->odd_rank;
      const bool old_odd_rank = !node->odd_rank;

      // If current node is a 1, 2 node, then we are done.
      if (old_odd_rank != node->right->odd_rank) return true;

      // Rotate according to node->left->right->parity.
      if (old_odd_rank == node->left->right->odd_rank) {
        RightRotate(node);
      } else {
        node->left->odd_rank = !node->left->odd_rank;
        node->left->right->odd_rank = !node->left->right->odd_rank;
        LRRotate(node);
      }
    } else {
      // When the new inserted node is a 1-child, no rebalance is required.
      if (node->odd_rank != node->right->odd_rank) return true;

      // After this, the new inserted node is a 0-child.
      // For either promote/rotate, the parity will change.
      node->odd_rank = !node->odd_rank;
      const bool old_odd_rank = !node->odd_rank;

      // If current node is a 1, 2 node, then we are done.
      if (old_odd_rank != node->left->odd_rank) return true;

      // Rotate according to node->right->left->odd_rank.
      if (old_odd_rank == node->right->left->odd_rank) {
        LeftRotate(node);
      } else {
        node->right->odd_rank = !node->right->odd_rank;
        node->right->left->odd_rank = !node->right->left->odd_rank;
        RLRotate(node);
      }
    }
    return true;
  }

  bool Delete(const T& x) {
    const T* delete_value = &x;
    Node **link = &root_, **safe_node = &root_, *current = *link,
         *parent = sentinel;
    bool parent_odd_rank = root_->odd_rank, parent_one_child = false;
    // Find the safe node and the place to delete node.
    for (; current != sentinel; current = *link) {
      // Safe node is the parent of a 1-child or the parent of a 1, 2 node whose
      // 1-child is not a 2,2 node.
      if (IsSafeNodeForDelete(current, parent_odd_rank) &&
          (x != current->value ||
           (current->left != sentinel && current->right != sentinel)))
        safe_node = link;
      if (x == current->value) break;
      parent_one_child = parent_odd_rank != current->odd_rank;
      parent = current;
      parent_odd_rank = parent->odd_rank;
      link = x < current->value ? &current->left : &current->right;
    }
    if (current == sentinel) return false;

    // When the node needed to be removed has two children, pull the minimum
    // value from the right tree and delete the minimum value in the right
    // tree.
    if (current->left != sentinel && current->right != sentinel) {
      Node* min = current->right;
      parent_one_child = parent->odd_rank != current->odd_rank;
      parent = current;
      for (link = &current->right; min->left != sentinel; min = min->left) {
        if (IsSafeNodeForDelete(min, parent->odd_rank)) safe_node = link;
        parent_one_child = parent->odd_rank != min->odd_rank;
        parent = min;
        link = &min->left;
      }
      current->value = min->value;
      delete_value = &current->value;
      current = min;
    }
    Node* child = (current->left != sentinel ? current->left : current->right);

    Node*& node = *safe_node;

    const bool delete_one_child = current->odd_rank != parent->odd_rank;
    *link = child;
    delete current;
    current = child;

    Node* demote_chain_end = child;
    // If pulling up to root_, then we are done.
    if (current == root_) return true;

    if (delete_one_child) {
      //  If deleting a 1-child.
      //  If sibling is not a sentinel, parent must be a 1, 1 node.
      //  After deletion, parent is a 1, 2 node and we are done.
      if ((parent->left == child ? parent->right : parent->left) != sentinel)
        return true;

      // Otherwise, deleting a 1-child of an unary node
      // Since the parent becomes a 2, 2 leaf, we demote the parent.
      parent->odd_rank = !parent->odd_rank;
      // Now, parent is a 1, 1 leaf. Parent can be a 1-child or 2-child before
      // demotion. If parent is a 1-child before demotion, then we are done.
      if (parent_one_child || parent == root_) return true;
      demote_chain_end = parent;
    }

    // Demote all nodes below the safe_node.
    parent = *delete_value < node->value ? node->left : node->right;
    current = *delete_value < parent->value ? parent->left : parent->right;
    for (; parent != demote_chain_end;) {
      Node* sibling =
          *delete_value < parent->value ? parent->right : parent->left;
      if (sibling->odd_rank != parent->odd_rank && sibling != sentinel)
        sibling->odd_rank = !sibling->odd_rank;
      parent->odd_rank = !parent->odd_rank;
      parent = current;
      current = *delete_value < parent->value ? parent->left : parent->right;
    }

    // If rotation is not required, safe node must be a 1-child.
    // We can demove the safe node and we are done.
    if (!RotationRequired(node, *delete_value)) {
      // If safe node is a 1, 3 node and rotation is not required, the 1-child
      // must not be on the search path. Then, demote the 1-child.
      if (node->left->odd_rank == node->right->odd_rank) {
        Node* one_child =
            *delete_value < node->value ? node->right : node->left;
        if (one_child != sentinel && one_child != child)
          one_child->odd_rank = !one_child->odd_rank;
      }
      node->odd_rank = !node->odd_rank;
      return true;
    }

    if (*delete_value < node->value) {
      node->right->odd_rank = !node->right->odd_rank;
      if (node->odd_rank != node->right->right->odd_rank) {
        RLRotate(node);
        return true;
      }
      if (node->left != sentinel || node->right->left != sentinel)
        node->odd_rank = !node->odd_rank;
      LeftRotate(node);
    } else {
      node->left->odd_rank = !node->left->odd_rank;
      if (node->odd_rank != node->left->left->odd_rank) {
        LRRotate(node);
        return true;
      }
      if (node->right != sentinel || node->left->right != sentinel)
        node->odd_rank = !node->odd_rank;
      RightRotate(node);
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

  bool IsBalanced() const {
    if (sentinel->odd_rank != true) {
      std::cout << "Sentinel must have rank -1\n";
      return false;
    }
    return ComputeRank(root_) != -2;
  }

  ~WAVL() { FreeTree(root_, sentinel); }

  void InorderTraverse(std::vector<T>& result) const {
    return ::InorderTraverse(root_, result, sentinel);
  }

  void PrintTree() const { return PrintTree(root_, "root"); }

  Node* root() const { return root_; }

  Node*& root() { return root_; }

 private:
  static int FromRankParityToRankDifference(const Node* node,
                                            const Node* parent) {
    return node->odd_rank == parent->odd_rank ? 2 : 1;
  }

  static void PrintTree(const Node* root, std::string prefix) {
    if (root == sentinel) return;
    PrintTree(root->left, prefix + "->left");
    std::cerr << prefix << " = " << root->value << ", "
              << "Rank parity: " << root->odd_rank << ", "
              << FromRankParityToRankDifference(root->left, root) << ", "
              << FromRankParityToRankDifference(root->right, root) << ' '
              << ((root->left == sentinel && root->right == sentinel) ? "leaf"
                  : (root->left != sentinel && root->right != sentinel)
                      ? "binary"
                      : "unary")
              << " node\n";
    PrintTree(root->right, prefix + "->right");
  }

  static int ComputeRank(const Node* node) {
    if (node == sentinel) return -1;
    int left_rank = ComputeRank(node->left);
    int right_rank = ComputeRank(node->right);
    if (left_rank == -2 || right_rank == -2) return -2;
    // No 2, 2 leaf.
    if (node->left == node->right && node->odd_rank == node->left->odd_rank) {
      std::cout << "Cannot have 2, 2 leaf\n";
      return -2;
    }
    left_rank += (node->odd_rank == node->left->odd_rank ? 2 : 1);
    right_rank += (node->odd_rank == node->right->odd_rank ? 2 : 1);
    // Left tree's rank must be equalt to right tree's rank.
    if (left_rank != right_rank) {
      std::cout << "Left rank != Right rank\n";
      return -2;
    }
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
      if (node->odd_rank != node->left->odd_rank) return done = true;

      // After this, the new inserted node is a 0-child.
      // For either promote/rotate, the parity will change.
      node->odd_rank = !node->odd_rank;
      const bool old_odd_rank = !node->odd_rank;

      // If current node is a 0, 1 node, then upper layer should rebalance.
      if (old_odd_rank != node->right->odd_rank) return true;

      // Rotate according to node->left->right->parity.
      if (old_odd_rank == node->left->right->odd_rank) {
        RightRotate(node);
      } else {
        node->left->odd_rank = !node->left->odd_rank;
        node->left->right->odd_rank = !node->left->right->odd_rank;
        LRRotate(node);
      }
    } else {
      if (!Insert(node->right, x, done)) return false;
      if (done) return true;
      // When the new inserted node is a 1-child, no rebalance is required.
      if (node->odd_rank != node->right->odd_rank) return done = true;

      // After this, the new inserted node is a 0-child.
      // For either promote/rotate, the parity will change.
      node->odd_rank = !node->odd_rank;
      const bool old_odd_rank = !node->odd_rank;

      // If current node is a 0, 1 node, then upper layer should rebalance.
      if (old_odd_rank != node->left->odd_rank) return true;

      // Rotate according to node->right->left->odd_rank.
      if (old_odd_rank == node->right->left->odd_rank) {
        LeftRotate(node);
      } else {
        node->right->odd_rank = !node->right->odd_rank;
        node->right->left->odd_rank = !node->right->left->odd_rank;
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
      if (node->odd_rank == node->left->odd_rank) {
        // When node is not leaf, no rebalancing is required.
        if (node->left != sentinel || node->right != sentinel)
          return done = true;
        // Leaf node cannot has rank 1.
        node->odd_rank = !node->odd_rank;
        return true;
      }
      // At this point, the rank difference between left and current is 3.
      // If the rank difference between right and current is 2, demote.
      if (node->odd_rank == node->right->odd_rank) {
        node->odd_rank = !node->odd_rank;
        return true;
      }
      // If the rank difference between right and current is 1, and
      // node->right can be demote, then demote current and right.
      if (node->right->odd_rank == node->right->left->odd_rank &&
          node->right->odd_rank == node->right->right->odd_rank) {
        node->odd_rank = !node->odd_rank;
        node->right->odd_rank = !node->right->odd_rank;
        return true;
      }
      done = true;
      node->right->odd_rank = !node->right->odd_rank;
      if (node->odd_rank != node->right->right->odd_rank) {
        RLRotate(node);
        return true;
      }
      if (node->left != sentinel || node->right->left != sentinel)
        node->odd_rank = !node->odd_rank;
      LeftRotate(node);
    } else {
      if (!Delete(node->right, *delete_value, done)) return false;
      if (done) return true;
      // If the rank difference between right and current is 2.
      if (node->odd_rank == node->right->odd_rank) {
        // When node is not leaf, no rebalancing is required.
        if (node->left != sentinel || node->right != sentinel)
          return done = true;
        node->odd_rank = !node->odd_rank;
        return true;
      }
      // At this point, the rank difference between right and current is 3.
      // If the rank difference between left and current is 2, demote.
      if (node->odd_rank == node->left->odd_rank) {
        node->odd_rank = !node->odd_rank;
        return true;
      }
      // If the rank difference between left and current is 1, and
      // node->left can be demote, then demote current and left.
      if (node->left->odd_rank == node->left->left->odd_rank &&
          node->left->odd_rank == node->left->right->odd_rank) {
        node->odd_rank = !node->odd_rank;
        node->left->odd_rank = !node->left->odd_rank;
        return true;
      }
      done = true;
      node->left->odd_rank = !node->left->odd_rank;
      if (node->odd_rank != node->left->left->odd_rank) {
        LRRotate(node);
        return true;
      }
      if (node->right != sentinel || node->left->right != sentinel)
        node->odd_rank = !node->odd_rank;
      RightRotate(node);
    }
    return true;
  }

  static bool IsSafeNodeForDelete(Node* current, bool parent_parity) {
    // If current is a 1-child, then current is a safe node.
    if (current->odd_rank != parent_parity) return true;
    // After this, current is a 2-child.
    // If current is a 2, 2 node, then current is not a safe node.
    if (current->left->odd_rank == current->right->odd_rank) return false;
    Node* one_child = current->odd_rank != current->left->odd_rank
                          ? current->left
                          : current->right;
    // If the 1-child is a 1, 2 node, then current is a safe node.
    if (one_child->left->odd_rank != one_child->right->odd_rank) return true;
    // The 1-child must be 1, 1 node or 2, 2 node now.
    // If the 1-child is a 2, 2 node, then current is not a safe node.
    if (one_child->odd_rank == one_child->left->odd_rank) return false;
    // If the 1-child is a 1, 1 node, current is a safe node only when 1-child
    // is not a leaf.
    return one_child->left != one_child->right;
  }

  static bool RotationRequired(Node* current, const T& x) {
    // If safe node becomes 3, 2 node, then no rotation is required.
    if (current->left->odd_rank != current->right->odd_rank) return false;
    // Safe node is 3, 1 node now, one child must not be on the search path.
    Node* one_child = x < current->value ? current->right : current->left;
    // If the 1-child is a 1, 2 node, then rotation is required.
    if (one_child->left->odd_rank != one_child->right->odd_rank) return true;

    // The 1-child must be 1, 1 node or 2, 2 node now.
    // If the 1-child is a 1, 1 node, rotation is required.
    return one_child->odd_rank != one_child->left->odd_rank;
  }
  static bool RotationRequired(Node* current) {
    // If safe node becomes 3, 2 node, then no rotation is required.
    if (current->left->odd_rank != current->right->odd_rank) return false;
    // Safe node is 3, 1 node now, one child must not be on the search path.
    Node* one_child = current->odd_rank != current->left->odd_rank
                          ? current->left
                          : current->right;
    // If the 1-child is a 1, 2 node, then rotation is required.
    if (one_child->left->odd_rank != one_child->right->odd_rank) return true;

    // The 1-child must be 1, 1 node or 2, 2 node now.
    // If the 1-child is a 1, 1 node, rotation is required.
    return one_child->odd_rank != one_child->left->odd_rank;
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
