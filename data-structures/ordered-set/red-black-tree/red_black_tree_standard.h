#ifndef RED_BLACK_TREE_STANDARD_H
#define RED_BLACK_TREE_STANDARD_H

#include <iostream>
#include <vector>

#include "../binary-search-tree-common/binary_search_tree_common.h"

template <typename T>
struct alignas(64) RBTreeStandard {
 public:
  struct Node {
    using value_type = T;
    Node *left;
    Node *right;
    Node *parent;
    T value;
    bool red;
  };

  RBTreeStandard() {
    dummy_.left = header_.left = sentinel_;
    dummy_.right = header_.right = sentinel_;
    dummy_.parent = header_.parent = sentinel_;
    dummy_.red = header_.red = false;
  }
  bool Insert(const T &x) {
    // Empty tree.
    if (root_ == sentinel_) {
      root_ = NewNode(x, &header_, false);
      return true;
    }

    // Below, the tree cannot be empty.
    Node **link = &root_, *parent;
    do {
      Node *current = *link;
      if (x == current->value) return false;
      link = x < current->value ? &current->left : &current->right;
      parent = current;
    } while ((*link) != sentinel_);
    *link = NewNode(x, parent, true);

    // Set the root to black so that the loop below can terminate naturally.
    root_->red = false;
    // When root's both children are red, switch the children to black.
    // Removing this switch does not effect the correctness, but the result
    // tree may have a red root.
    if (root_->left->red && root_->right->red)
      root_->left->red = root_->right->red = false;
    // Invariant: Current must be red.
    Node *current = *link, *grand_parent = parent->parent;
    for (;;) {
      // If the parent is black, since all requirements are satisfied, we are
      // done.
      if (!parent->red) return true;

      Node *uncle = (parent == grand_parent->left) ? grand_parent->right
                                                   : grand_parent->left;
      // If uncle is black, then we find a place to rotate. The rotation will be
      // done after the loop.
      if (!uncle->red) break;

      // Color flip (parent and uncle are red) and move two levels up.
      parent->red = uncle->red = false;
      grand_parent->red = true;
      current = grand_parent;
      parent = current->parent;
      grand_parent = parent->parent;
    }

    // grand_parent->parent may be the header node.
    // Without the header node, the code needs to test whether grand_parent is
    // root explicitly.
    Node *&root_link = ((grand_parent == grand_parent->parent->left)
                            ? grand_parent->parent->left
                            : grand_parent->parent->right);
    // The properties we know at this point:
    // 1. Current and parent must be red, and uncle is black due to the loop.
    // 2. Grandparent must be black, sibling must be black, and children of
    //    current must be black. This is due to the property of red-black tree.
    // Then, we just need to rotate accordingly.
    // Note that we didn't update colors, since the colors will be updated
    // afterwards anyway.
    if (parent == grand_parent->left) {
      if (current != parent->left) {
        //       G             G                C
        //      / \           / \   (later)   /   \
        //     p   U  -->    c   U  ----->   p     g
        //      \           / \               \   / \
        //       c         p   S               T S   U
        //      / \         \
        //     T   S         T
        // Since one additional rotation is required after this block,
        // the code in this block omit the links between grandparent and
        // current. The code in this block also omit the color change, since the
        // color will be changed afterwards.
        parent->right = current->left;
        current->left->parent = parent;
        current->left = parent;
        parent->parent = current;
        parent = current;
      }
      //
      //        G           P
      //       / \         / \
      //      p   U  -->  c   g
      //     / \             / \
      //    c   S           S   U
      //
      grand_parent->left = parent->right;
      parent->right->parent = grand_parent;
      parent->parent = grand_parent->parent;
      root_link = parent;
      parent->right = grand_parent;
      grand_parent->parent = parent;
      grand_parent->red = true;
      parent->red = false;
    } else {
      if (current == parent->left) {
        parent->left = current->right;
        current->right->parent = parent;
        current->right = parent;
        parent->parent = current;
        parent = current;
      }
      grand_parent->right = parent->left;
      parent->left->parent = grand_parent;
      parent->parent = grand_parent->parent;
      root_link = parent;
      parent->left = grand_parent;
      grand_parent->parent = parent;
      grand_parent->red = true;
      parent->red = false;
    }
    return true;
  }

  bool Delete(const T &x) {
    Node **link, *current;
    for (link = &root_, current = *link;
         current != sentinel_ && x != current->value;) {
      link = x < current->value ? &current->left : &current->right;
      current = *link;
    }
    if (current == sentinel_) return false;
    // When the node to be deleted has two children, find the successor with
    // equal probability.
    if (current->left != sentinel_ && current->right != sentinel_) {
      Node *min = current->right;
      link = &(current->right);
      for (; min->left != sentinel_; link = &min->left, min = min->left) {
      }
      current->value = min->value;
      current = min;
    }

    // Now, the node to be deleted should have at most one child.
    bool rebalance_required = false;
    Node *child = current->left != sentinel_ ? current->left : current->right,
         *parent = current->parent;
    if (child == sentinel_) {
      // If the node to be deleted has no child, then rebalance maybe required.
      rebalance_required = !current->red && current != root_;
    } else {
      // If the node to be deleted has one child, then pull up the child.
      child->red = false;
      child->parent = current->parent;
    }
    *link = child;
    delete current;

    if (!rebalance_required) return true;

    // When both of root's children are black, set the root to red. In this way,
    // the code just needs to check parent->red in the following loop (avoiding
    // additionally checking parent == root). The reason is as follows:
    // 1.  When the root is red, then the loop would terminate when reaching the
    //     line of if (parent->red).
    // 2.  When the root is black, then at least one of the child is red. Due
    //     to the loop invariant, current must be black. Thus, when current
    //     reaches the black child, the sibling will be red and the loop
    //     terminates.
    if (!root_->left->red && !root_->right->red) root_->red = true;
    Node *sibling;
    for (current = sentinel_;;) {
      // Loop invariant: Current must be black.

      // If sibling is red, or sibling has at least one red child, then we find
      // a place to rotate. The rotation will be done after the loop.
      sibling = (current == parent->left) ? parent->right : parent->left;
      if (sibling->red || sibling->left->red || sibling->right->red) break;

      // Color flip (parent and uncle are red) and move two levels up.
      sibling->red = true;
      // If parent is red or parent is the root, then we are done.
      if (parent->red) {
        parent->red = false;
        return true;
      }
      current = parent;
      parent = current->parent;
    }

    Node *close_nephew, *distant_nephew;
    if (current == parent->left) {
      if (sibling->red) {
        //     P               S
        //    / \             / \
				//   c   s    -->    p  Dn
        //      / \         / \
				//     Cn Dn       c  Cn
        parent->right = sibling->left;
        sibling->left->parent = parent;

        sibling->parent = parent->parent;
        (parent->parent->left == parent ? parent->parent->left
                                        : parent->parent->right) = sibling;

        sibling->left = parent;
        parent->parent = sibling;

        sibling->red = false;
        sibling = parent->right;
        if (!sibling->left->red && !sibling->right->red) {
          sibling->red = true;
          return true;
        }
        parent->red = true;
      }
      // Now, sibling must be black and one of the sibling's child must be red.
      distant_nephew = sibling->right;
      close_nephew = sibling->left;
      if (!distant_nephew->red) {
        //
        //    (p)           (p)                       (Cn)
        //    / \           / \         (later)       /  \
        //   C   S    -->  C  cn        ------->     P    S
        //      / \           / \                   / \
				//     cn Dn         X   S                 C   X
        //                        \
				//                        Dn
        // Since one additional rotation is required after this block,
        // the code in this block omit the links between parent and
        // close_nephew. The code in this block also omit the color change,
        // since the color will be changed afterwards.
        sibling->left = close_nephew->right;
        close_nephew->right->parent = sibling;

        close_nephew->right = sibling;
        sibling->parent = close_nephew;

        sibling = close_nephew;
        distant_nephew = sibling->right;
        close_nephew = sibling->left;
      }
      // Now, sibling must be black and distant_nephew must be red.
      //      (p)             (s)
      //      / \             / \
			//     C   S     -->   P   Dn
      //        / \         / \
			//      (cn) dn      C  (cn)
      // Most color/pointers changing are in the end of the function.
      sibling->left = parent;
      parent->right = close_nephew;
    } else {
      if (sibling->red) {
        parent->left = sibling->right;
        sibling->right->parent = parent;

        sibling->parent = parent->parent;
        (parent->parent->left == parent ? parent->parent->left
                                        : parent->parent->right) = sibling;
        sibling->right = parent;
        parent->parent = sibling;

        sibling->red = false;
        sibling = parent->left;
        if (!sibling->left->red && !sibling->right->red) {
          sibling->red = true;
          return true;
        }
        parent->red = true;
      }
      distant_nephew = sibling->left;
      close_nephew = sibling->right;
      if (!distant_nephew->red) {
        sibling->right = close_nephew->left;
        close_nephew->left->parent = sibling;

        close_nephew->left = sibling;
        sibling->parent = close_nephew;

        sibling = close_nephew;
        distant_nephew = sibling->left;
        close_nephew = sibling->right;
      }
      sibling->right = parent;
      parent->left = close_nephew;
    }
    (parent == parent->parent->left ? parent->parent->left
                                    : parent->parent->right) = sibling;
    sibling->parent = parent->parent;
    parent->parent = sibling;
    close_nephew->parent = parent;
    sibling->red = parent->red;
    parent->red = distant_nephew->red = false;
    return true;
  }

  bool IsBalanced() const {
    if (sentinel_->red) return false;
    if (header_.left != root_) return false;
    if (header_.red) return false;
    return BlackHeight(root_) != -1;
  }

  ~RBTreeStandard() { FreeTree(root_, sentinel_); }

  void InorderTraverse(std::vector<T> &result) const {
    return ::InorderTraverse(root_, result, sentinel_);
  }

  Node *root() const { return root_; }

  Node *&root() { return root_; }

  void PrintTree() const { PrintTree(root_, "root"); }

  void PrintTree(const Node *root, std::string prefix) const {
    if (root == sentinel_) return;
    PrintTree(root->left, prefix + "->left");
    std::cerr << prefix << " = " << root->value << ' '
              << (root->red ? 'R' : 'B') << " Parent:" << root->parent->value
              << '\n';
    PrintTree(root->right, prefix + "->right");
  }

 private:
  int BlackHeight(const Node *node) const {
    if (node == sentinel_) return 1;
    if (node->red && (node->left->red || node->right->red)) return -1;
    int lh = BlackHeight(node->left), rh = BlackHeight(node->right);
    if (lh == -1 || rh == -1 || lh != rh) return -1;
    return lh + (node->red ? 0 : 1);
  }

  Node *NewNode(const T &x, Node *parent, bool red) {
    Node *new_node = new Node();
    new_node->left = sentinel_;
    new_node->right = sentinel_;
    new_node->parent = parent;
    new_node->red = red;
    new_node->value = x;
    return new_node;
  }

  // Use a header node so that the left pointer points to the real root.
  // The benefit is that, when rotating around a node, the code does not need to
  // check whether the node is root or not to find correct pointer to update.
  Node header_;
  Node *&root_ = header_.left;
  Node dummy_;
  // The sentinel's parent pointer can be changed arbitrarily in Insert/Delete.
  // The sentinel's left/right pointers can be changed arbitrarily in Delete.
  // Thus, the code should not depending on sentinel's parent pointer.
  Node *sentinel_ = &dummy_;
};

#endif
