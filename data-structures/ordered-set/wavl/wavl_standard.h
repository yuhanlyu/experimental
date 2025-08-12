#ifndef WAVL_STANDARD_H
#define WAVL_STANDARD_H

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

template <typename T>
struct WAVLStandard {
 public:
  struct Node {
    using value_type = T;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
    T value;
    bool rank_parity = false;  // rank 0 -> false
  };

  WAVLStandard() {
    sentinel_->left = header_.left = sentinel_;
    sentinel_->right = header_.right = sentinel_;
    sentinel_->parent = sentinel_;
    header_.parent = &header_;
    sentinel_->rank_parity = header_.rank_parity = true;  // rank -1
  }

  ~WAVLStandard() { FreeTree(root_, sentinel_); }

  bool Insert(const T& x) {
    // Empty tree.
    if (root_ == sentinel_) {
      root_ = NewNode(x, &header_);
      return true;
    }
    Node **link = &root_, *parent = &header_;
    for (Node* current = *link; current != sentinel_;) {
      if (x == current->value) return false;
      link = x < current->value ? &current->left : &current->right;
      parent = current;
      current = *link;
    }
    *link = NewNode(x, parent);

    Node* current = *link;
    // Set the header rank parity so that the loop does not need to test current
    // == root_. When current = root_, current must get promoted in the previous
    // iteration. Thus, current->rank_parity != parent->rank_parity and loop
    // terminates.
    header_.rank_parity = root_->rank_parity;
    for (;;) {
      // If the current becomes 1-child of the parent (the parent become 1, 1
      // node), then we are done.
      if (current->rank_parity != parent->rank_parity) return true;

      // Now, the current must be 0-child of the parent.
      const Node* sibling =
          (current == parent->left) ? parent->right : parent->left;
      // If parent is a 0, 2 node, then we find a place to rotate.
      if (current->rank_parity == sibling->rank_parity) break;
      // Now, parent is a 0, 1 node, promote the parent and proceed at a higher
      // level.
      parent->rank_parity = 1 - parent->rank_parity;
      current = parent;
      parent = current->parent;
    }

    // Now, parent is a 0, 2 node and current is a 1, 2 node, since the current
    // must get promoted in the previous iteration.
    Node* inner_child =
        ((current == parent->left) ? current->right : current->left);
    if (current == parent->left) {
      if (inner_child->rank_parity != current->rank_parity) {
        // Current's inner child is a 2-child.
        //
        //      p                 p
        //     / \       -->     / \
        //    c   x             i   x
        //   / \               / \
        //  l   i             c   z
        //     / \           / \
        //    y   z         l   y
        // Since one additional rotation is required after this block,
        // the code in this block omit the links between parent and
        // child. The code in this block also omit the parity change of the
        // parent, since the parity will be changed afterwards.
        inner_child->left->parent = current;
        current->right = inner_child->left;
        inner_child->left = current;
        current->parent = inner_child;

        inner_child->rank_parity = 1 - inner_child->rank_parity;
        current->rank_parity = 1 - current->rank_parity;
        current = inner_child;
        inner_child = current->right;
      }
      // Current's inner child is a 2-child.
      // Note that for the fall-through case, the inner child may not be a
      // 2-child.
      //
      //      p                 c
      //     / \       -->     / \
      //    c   x             l   p
      //   / \                   / \
      //  l   i                 i   x
      // Note that there are more operations after the block.
      parent->left = inner_child;
      current->right = parent;
    } else {
      if (inner_child->rank_parity != current->rank_parity) {
        inner_child->right->parent = current;
        current->left = inner_child->right;
        inner_child->right = current;
        current->parent = inner_child;
        inner_child->rank_parity = 1 - inner_child->rank_parity;
        current->rank_parity = 1 - current->rank_parity;
        current = inner_child;
        inner_child = current->left;
      }
      parent->right = inner_child;
      current->left = parent;
    }
    (parent == parent->parent->left ? parent->parent->left
                                    : parent->parent->right) = current;
    current->parent = parent->parent;
    inner_child->parent = parent;
    parent->parent = current;
    parent->rank_parity = 1 - parent->rank_parity;
    return true;
  }

  bool Delete(const T& x) {
    Node **link, *current;
    for (link = &root_, current = *link;
         current != sentinel_ && x != current->value;) {
      link = x < current->value ? &current->left : &current->right;
      current = *link;
    }
    if (current == sentinel_) return false;
    // When the node to be deleted has two children, find the successor.
    if (current->left != sentinel_ && current->right != sentinel_) {
      Node* min = current->right;
      link = &(current->right);
      for (; min->left != sentinel_; link = &min->left, min = min->left) {
      }
      current->value = min->value;
      current = min;
    }
    Node *child = current->left != sentinel_ ? current->left : current->right,
         *parent = current->parent;

    // Set header_->rank_parity = root_->rank_parity.
    // In this way, if root_->rank_parity is changed, root_->rank_parity will be
    // the same as header_->rank_parity.
    header_.rank_parity = 1 - root_->rank_parity;
    const bool delete_one_child = current->rank_parity != parent->rank_parity;
    *link = child;
    child->parent = parent;
    delete current;
    current = child;

    // If pulling up to root_, then we are done.
    // if (current == root_) return true;
    if (delete_one_child) {
      //  If deleting a 1-child.
      //  If sibling is not a sentinel, parent must be a 1, 1 node.
      //  After deletion, parent is a 1, 2 node and we are done.
      if ((parent->left == child ? parent->right : parent->left) != sentinel_)
        return true;

      // Otherwise, deleting a 1-child of an unary node
      // Since the parent becomes a 2, 2 leaf, we demote the parent.
      parent->rank_parity = 1 - parent->rank_parity;
      // Now, parent is a 1, 1 leaf. Parent can be a 2-child or a 3-child.
      // If parent is a 2-child, then we are done.
      if (parent->rank_parity == parent->parent->rank_parity) return true;

      // Otherwise, parent is a 3-child.
      current = parent;
      parent = current->parent;
    }

    // Now, current must be a 3-child.
    Node* sibling;
    for (;;) {
      sibling = (current == parent->left ? parent->right : parent->left);
      // If sibling is a 1-child and sibling is not a 2, 2, node, we find a
      // place to rotate.
      if (sibling->rank_parity != parent->rank_parity &&
          (sibling->left->rank_parity != sibling->rank_parity ||
           sibling->right->rank_parity != sibling->rank_parity))
        break;

      sibling->rank_parity = parent->rank_parity;
      parent->rank_parity = 1 - parent->rank_parity;
      //  If parent is not a 3-child, then we are done.
      if (parent->rank_parity == parent->parent->rank_parity) return true;
      current = parent;
      parent = current->parent;
    }

    // Now, parent must be a 1, 3 node. Current must be the 3-child.
    // Sibling is not a 2, 2 node (exactly one of the child is 1-child, the
    // other is 2-child).
    Node* close_nephew =
        current == parent->left ? sibling->left : sibling->right;
    bool double_rotate = false;
    if (current == parent->left) {
      if (sibling->right->rank_parity == sibling->rank_parity) {
        // Distant nephew is a 2-child, so close nephew is a 1-child.
        //       p                p        (later)      cn
        //     /   \     -->     / \       ------->    /   \
        //    c     s           c  cn                 p     s
        //         / \             / \               / \   / \
        //        cn  dn          x   s             c   x y  dn
        //       /  \                / \
        //      x    y              y  dn
        // Since one additional rotation is required after this block,
        // the code in this block omit the links between parent and
        // close nephew. The code in this block also omit the parity change of
        // the parent, since the parity will be changed afterwards.
        sibling->left = close_nephew->right;
        close_nephew->right->parent = sibling;
        close_nephew->right = sibling;
        sibling->parent = close_nephew;
        close_nephew->rank_parity = 1 - close_nephew->rank_parity;
        sibling->rank_parity = 1 - sibling->rank_parity;
        sibling = close_nephew;
        close_nephew = sibling->left;
        double_rotate = true;
      }
      // Now, Distant nephew is a 1-child, so close newphew can be 1- or
      // 2-child. Current's inner child is a 2-child. Note that for the
      // fall-through case, the inner child may not be a 2-child.
      //      p               s
      //     / \     -->     / \
      //    c   s           p  dn
      //       / \         / \
      //      cn  dn      c  cn
      // Note that there are more operations after the block.
      parent->right = close_nephew;
      sibling->left = parent;
    } else {
      if (sibling->left->rank_parity == sibling->rank_parity) {
        sibling->right = close_nephew->left;
        close_nephew->left->parent = sibling;
        close_nephew->left = sibling;
        sibling->parent = close_nephew;
        close_nephew->rank_parity = 1 - close_nephew->rank_parity;
        sibling->rank_parity = 1 - sibling->rank_parity;
        sibling = close_nephew;
        close_nephew = sibling->right;
        double_rotate = true;
      }
      parent->left = close_nephew;
      sibling->right = parent;
    }
    (parent == parent->parent->left ? parent->parent->left
                                    : parent->parent->right) = sibling;
    sibling->parent = parent->parent;
    close_nephew->parent = parent;
    parent->parent = sibling;
    sibling->rank_parity = 1 - sibling->rank_parity;
    // If parent is a leaf or double rotation is needed, demote twice, but
    // parity will not change. Otherwise, demote once.
    if (parent->left != parent->right && !double_rotate)
      parent->rank_parity = 1 - sibling->rank_parity;
    return true;
  }

  void InorderTraverse(std::vector<T>& result) const {
    ::InorderTraverse(root_, result, sentinel_);
  }

  void PrintTree() const { PrintTree(root_, "root", sentinel_); }

  bool IsBalanced() const {
    if (sentinel_->rank_parity != true) {
      std::cout << "Sentinel must have rank -1\n";
      return false;
    }
    return ComputeRank(root_, sentinel_) != -2;
  }

 private:
  Node* NewNode(const T& value, Node* parent) {
    Node* n = new Node();
    n->parent = parent;
    n->left = sentinel_;
    n->right = sentinel_;
    n->value = value;
    n->rank_parity = false;  // rank 0
    return n;
  }

  static int FromRankParityToRankDifference(const Node* node,
                                            const Node* parent) {
    return node->rank_parity == parent->rank_parity ? 2 : 1;
  }

  static void PrintTree(const Node* root, std::string prefix,
                        const Node* sentinel) {
    if (root == sentinel) return;
    PrintTree(root->left, prefix + "->left", sentinel);
    std::cerr << prefix << " = " << root->value << ", "
              << "Rank parity: " << root->rank_parity << ", "
              << FromRankParityToRankDifference(root, root->parent) << "-child "
              << FromRankParityToRankDifference(root->left, root) << ", "
              << FromRankParityToRankDifference(root->right, root) << ' '
              << ((root->left == sentinel && root->right == sentinel) ? "leaf"
                  : (root->left != sentinel && root->right != sentinel)
                      ? "binary"
                      : "unary")
              << " node\n";
    PrintTree(root->right, prefix + "->right", sentinel);
  }

  // Compute the rank of the subtrees. If the rank does not satisfy wavl
  // requirement, then return -2.
  static int ComputeRank(const Node* node, const Node* sentinel) {
    if (node == sentinel) return -1;
    int left_rank = ComputeRank(node->left, sentinel);
    int right_rank = ComputeRank(node->right, sentinel);
    if (left_rank == -2 || right_rank == -2) return -2;
    // No 2, 2 leaf.
    if (node->left == node->right &&
        node->rank_parity == node->left->rank_parity) {
      std::cout << "Cannot have 2, 2 leaf\n";
      return -2;
    }
    left_rank += (node->rank_parity == node->left->rank_parity ? 2 : 1);
    right_rank += (node->rank_parity == node->right->rank_parity ? 2 : 1);
    // Left tree's rank must be equalt to right tree's rank.
    if (left_rank != right_rank) {
      std::cout << "Left rank != Right rank\n";
      return -2;
    }
    return left_rank;
  }

  Node header_;
  Node*& root_ = header_.left;
  Node dummy_;
  Node* sentinel_ = &dummy_;
};

#endif
