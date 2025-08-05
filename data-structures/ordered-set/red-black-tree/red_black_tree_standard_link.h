#ifndef RED_BLACK_TREE_STANDARD_LINK_H
#define RED_BLACK_TREE_STANDARD_LINK_H

#include <iostream>
#include <vector>

#include "../binary-search-tree-common/binary_search_tree_common.h"

template <typename T>
struct alignas(64) RBTreeStandardLink {
 public:
  struct Node {
    using value_type = T;
    // link[0] is left child and link[1] is right child.
    Node *link[2];
    Node *parent;
    T value;
    bool red;
  };

  RBTreeStandardLink() {
    dummy_.link[0] = header_.link[0] = sentinel_;
    dummy_.link[1] = header_.link[1] = sentinel_;
    dummy_.parent = header_.parent = sentinel_;
    dummy_.red = header_.red = false;
  }

  struct Node *NewNode(const T &x, Node *parent, bool red) {
    Node *new_node = new Node();
    new_node->link[0] = sentinel_;
    new_node->link[1] = sentinel_;
    new_node->parent = parent;
    new_node->red = red;
    new_node->value = x;
    return new_node;
  }

  bool Insert(const T &x) {
    // Empty tree.
    if (root_ == sentinel_) {
      root_ = NewNode(x, &header_, false);
      return true;
    }

    // Below, the tree cannot be empty.
    bool dir = 0;
    Node *current = root_, *parent;
    do {
      if (x == current->value) return false;
      dir = x >= current->value;
      parent = current;
      current = current->link[dir];
    } while (current != sentinel_);
    current = parent->link[dir] = NewNode(x, parent, true);

    // When root's both children are red, switch the children to black.
    // The purpose of this switching is to avoid setting root to red during
    // the color flipping in the loop below, which require an additional
    // checking if (grand_parent == root_) return true; before setting
    // the grand parent to red.
    root_->red = false;
    if (root_->link[0]->red && root_->link[1]->red)
      root_->link[0]->red = root_->link[1]->red = false;
    // Invariant: Current must be red.
    Node *grand_parent = parent->parent;
    for (;;) {
      // If the parent is black, since all requirements are satisfied, we are
      // done.
      if (!parent->red) {
        return true;
      }

      dir = (parent != grand_parent->link[0]);
      Node *uncle = grand_parent->link[1 - dir];
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
    Node *&link = ((grand_parent == grand_parent->parent->link[0])
                       ? grand_parent->parent->link[0]
                       : grand_parent->parent->link[1]);
    // The properties we know at this point:
    // 1. Current and parent must be red, and uncle is black due to the loop.
    // 2. Grandparent must be black, sibling must be black, and children of
    //    current must be black. This is due to the property of red-black tree.
    // 3. parent = grand_parent->link[dir] and uncle  =
    // grand_parent->link[1-dir] Then, we just need to rotate accordingly.
    if (current == parent->link[1 - dir]) {
      parent->link[1 - dir] = current->link[dir];
      current->link[dir]->parent = parent;
      current->link[dir] = parent;
      parent->parent = current;
      parent = current;
    }
    grand_parent->link[dir] = parent->link[1 - dir];
    parent->link[1 - dir]->parent = grand_parent;
    parent->parent = grand_parent->parent;
    parent->link[1 - dir] = grand_parent;
    grand_parent->parent = parent;
    grand_parent->red = true;
    parent->red = false;
    link = parent;
    return true;
  }

  bool Delete(const T &x) {
    bool dir = 0;
    Node *current, *parent = &header_;
    for (current = root_; current != sentinel_ && x != current->value;) {
      dir = (x >= current->value);
      parent = current;
      current = current->link[dir];
    }
    if (current == sentinel_) return false;
    if (current->link[0] != sentinel_ && current->link[1] != sentinel_) {
      // When the node to be deleted has two children, find the predecessor or
      // successor depending on default_dir_in_deletion.
      dir = default_dir_in_deletion;
      Node *replacement = current->link[dir];
      const bool opposite_dir = 1 - dir;
      for (parent = current; replacement->link[opposite_dir] != sentinel_;
           replacement = replacement->link[opposite_dir]) {
        parent = replacement;
        dir = opposite_dir;
      }
      current->value = replacement->value;
      current = replacement;
      // Change the default so that the algorithm find predecessor or successor
      // alternatively.
      default_dir_in_deletion = !default_dir_in_deletion;
    }

    // Now, the node to be deleted should have at most one child.
    bool rebalance_required = false;
    Node *child =
        current->link[0] != sentinel_ ? current->link[0] : current->link[1];

    if (child == sentinel_) {
      // If the node to be deleted has no child, then rebalance maybe required.
      rebalance_required = !current->red && current != root_;
    } else {
      // If the node to be deleted has one child, then pull up the child.
      child->red = false;
      child->parent = current->parent;
    }
    parent->link[dir] = child;
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
    if (!root_->link[0]->red && !root_->link[1]->red) root_->red = true;
    Node *sibling;
    for (current = sentinel_;;) {
      // Loop invariant: Current must be black.

      // If sibling is red, or sibling has at least one red child, then we find
      // a place to rotate. The rotation will be done after the loop.
      sibling = parent->link[1 - dir];
      if (sibling->red || sibling->link[0]->red || sibling->link[1]->red) break;

      // Color flip (parent and uncle are red) and move two levels up.
      sibling->red = true;
      // If parent is red or parent is the root, then we are done.
      if (parent->red) {
        parent->red = false;
        return true;
      }
      current = parent;
      parent = current->parent;
      dir = (current != parent->link[0]);
    }

    if (sibling->red) {
      parent->link[1 - dir] = sibling->link[dir];
      sibling->link[dir]->parent = parent;

      sibling->parent = parent->parent;
      (parent->parent->link[dir] == parent ? parent->parent->link[dir]
                                           : parent->parent->link[1 - dir]) =
          sibling;
      sibling->link[dir] = parent;
      parent->parent = sibling;

      sibling->red = false;
      sibling = parent->link[1 - dir];
      if (!sibling->link[0]->red && !sibling->link[1]->red) {
        sibling->red = true;
        return true;
      }
      parent->red = true;
    }

    // Now, sibling must be black and one of the sibling's child must be red.
    Node *close_nephew = sibling->link[dir],
         *distant_nephew = sibling->link[1 - dir];
    if (!distant_nephew->red) {
      // Note that we did not set the color, since the color
      // will be set by the following case.
      parent->link[1 - dir] = close_nephew;
      close_nephew->parent = parent;

      sibling->link[dir] = close_nephew->link[1 - dir];
      close_nephew->link[1 - dir]->parent = sibling;

      close_nephew->link[1 - dir] = sibling;
      sibling->parent = close_nephew;

      sibling = close_nephew;
      close_nephew = sibling->link[dir];
      distant_nephew = sibling->link[1 - dir];
    }
    (parent == parent->parent->link[dir] ? parent->parent->link[dir]
                                         : parent->parent->link[1 - dir]) =
        sibling;
    sibling->parent = parent->parent;

    sibling->link[dir] = parent;
    parent->parent = sibling;

    parent->link[1 - dir] = close_nephew;
    close_nephew->parent = parent;

    sibling->red = parent->red;
    parent->red = distant_nephew->red = false;
    return true;
  }

  bool IsBalanced() const {
    if (sentinel_->red) return false;
    if (header_.link[0] != root_) return false;
    if (header_.red) return false;
    return BlackHeight(root_) != -1;
  }

  ~RBTreeStandardLink() { Free(root_, sentinel_); }

  void InorderTraverse(std::vector<T> &result) const {
    return Traverse(root_, sentinel_, result);
  }

  Node *root() const { return root_; }

  Node *&root() { return root_; }

  void PrintTree() const { PrintTree(root_, "root"); }

  void PrintTree(const Node *root, std::string prefix) const {
    if (root == sentinel_) return;
    PrintTree(root->link[0], prefix + "->left");
    std::cerr << prefix << " = " << root->value << ' '
              << (root->red ? 'R' : 'B') << " Parent:" << root->parent->value
              << '\n';
    PrintTree(root->link[1], prefix + "->right");
  }

 private:
  int BlackHeight(const Node *node) const {
    if (node == sentinel_) return 1;
    if (node->red && (node->link[0]->red || node->link[1]->red)) return -1;
    int lh = BlackHeight(node->link[0]), rh = BlackHeight(node->link[1]);
    if (lh == -1 || rh == -1 || lh != rh) return -1;
    return lh + (node->red ? 0 : 1);
  }

  static void Free(const Node *root, const Node *sentinel = nullptr) {
    if (root == sentinel) return;
    Free(root->link[0], sentinel);
    Free(root->link[1], sentinel);
    delete root;
  }

  static void Traverse(const Node *root, const Node *sentinel,
                       std::vector<typename Node::value_type> &result) {
    if (root == sentinel) return;
    Traverse(root->link[0], sentinel, result);
    result.push_back(root->value);
    Traverse(root->link[1], sentinel, result);
  }

  // Use a header node so that the link[0] pointer points to the real root.
  // The benefit is that, when rotating around a node, the code does not need to
  // check whether the node is root or not to find correct pointer to update.
  Node header_;
  Node *&root_ = header_.link[0];
  Node dummy_;
  // The sentinel's parent pointer can be changed arbitrarily in Insert/Delete.
  // The sentinel's link[0]/link[1] pointers can be changed arbitrarily in
  // Delete. Thus, the code should not depending on sentinel's parent pointer.
  Node *sentinel_ = &dummy_;

  bool default_dir_in_deletion = false;
};

#endif
