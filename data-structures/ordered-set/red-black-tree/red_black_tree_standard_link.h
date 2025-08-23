#ifndef RED_BLACK_TREE_STANDARD_LINK_H
#define RED_BLACK_TREE_STANDARD_LINK_H

#include <iostream>
#include <vector>

#include "../binary-search-tree-common/binary_search_tree_common.h"

template <typename T>
struct RBTreeStandardLink {
 public:
  struct alignas(64) Node {
    // link[0] is left child and link[1] is right child.
    Node *link[2];
    Node *parent;
    T value{};
    bool red;
  };

  bool Insert(const T &x) {
    return Insert(header_.link[0], x, sentinel_, &header_);
  }

  bool Delete(const T &x) {
    return Delete(header_.link[0], x, sentinel_, &header_);
  }

  bool IsBalanced() const {
    if (sentinel_->red) return false;
    if (header_.link[0] != root()) return false;
    if (header_.red) return false;
    return BlackHeight(root()) != -1;
  }

  ~RBTreeStandardLink() { Free(root(), sentinel_); }

  void InorderTraverse(std::vector<T> &result) const {
    return Traverse(root(), sentinel_, result);
  }

  Node *root() const { return header_.link[0]; }

  Node *&root() { return header_.link[0]; }

  void PrintTree() const { PrintTree(root(), "root"); }

  void PrintTree(const Node *root, std::string prefix) const {
    if (root == sentinel_) return;
    PrintTree(root->link[0], prefix + "->left");
    std::cerr << prefix << " = " << root->value << ' '
              << (root->red ? 'R' : 'B') << " Parent:" << root->parent->value
              << '\n';
    PrintTree(root->link[1], prefix + "->right");
  }

 private:
  static bool Insert(Node *&root, const T &x, Node *sentinel, Node *header) {
    bool dir = 0;
    Node *current = root, *parent = header;
    for (sentinel->value = x; x != current->value;
         current = current->link[dir]) {
      dir = x >= current->value;
      parent = current;
    }
    if (current != sentinel) return false;
    current = parent->link[dir] = new Node{
        .link{sentinel, sentinel}, .parent{parent}, .value{x}, .red{true}};

    // Set the root to black so that the loop below can terminate naturally.
    root->red = false;
    // When root's both children are red, switch the children to black.
    // Removing this switch does not effect the correctness, but the result
    // tree may have a red root.
    if (root->link[0]->red && root->link[1]->red)
      root->link[0]->red = root->link[1]->red = false;
    // Invariant: Current must be red.
    Node *grand_parent = parent->parent;
    for (;;) {
      // If the parent is black, since all requirements are satisfied, we are
      // done.
      if (!parent->red) return true;

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

    // The properties we know at this point:
    // 1. Current and parent must be red, and uncle is black due to the loop.
    // 2. Grandparent must be black, sibling must be black, and children of
    //    current must be black. This is due to the property of red-black tree.
    // 3. parent = grand_parent->link[dir] and uncle  =
    // grand_parent->link[1-dir] Then, we just need to rotate accordingly.
    if (current == parent->link[1 - dir]) {
      // Since one additional rotation is required after this block,
      // the code in this block omit the links between grandparent and current.
      // The code in this block also omit the color change, since the color
      // will be changed afterwards.
      parent->link[1 - dir] = current->link[dir];
      current->link[dir]->parent = parent;
      current->link[dir] = parent;
      parent->parent = current;
      parent = current;
    }
    Rotate(grand_parent, parent, dir);
    grand_parent->red = true;
    parent->red = false;
    return true;
  }

  static bool Delete(Node *&root, const T &x, Node *sentinel, Node *header) {
    bool dir = 0;
    Node *current = root, *parent = header;
    for (sentinel->value = x; x != current->value;
         current = current->link[dir]) {
      dir = (x >= current->value);
      parent = current;
    }
    if (current == sentinel) return false;
    if (current->link[0] != sentinel && current->link[1] != sentinel) {
      // When the node to be deleted has two children, find the predecessor or
      // successor depending on default_dir_in_deletion.
      dir = 1;
      Node *replacement = current->link[dir];
      const bool opposite_dir = 1 - dir;
      for (parent = current; replacement->link[opposite_dir] != sentinel;
           replacement = replacement->link[opposite_dir]) {
        parent = replacement;
        dir = opposite_dir;
      }
      // For simplicity, just copy the value.
      // If the application needs to ensure pointer stability, then the
      // code should swap current and replacement.
      current->value = replacement->value;
      current = replacement;
    }

    // Now, the node to be deleted should have at most one child.

    Node *child =
        current->link[0] != sentinel ? current->link[0] : current->link[1];
    // If the node to be deleted has no child, then rebalance maybe required.
    const bool rebalance_required =
        child == sentinel && !current->red && current != root;
    if (child != sentinel) {
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
    if (!root->link[0]->red && !root->link[1]->red) root->red = true;
    Node *sibling;
    for (current = sentinel;;) {
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
      Rotate(parent, sibling, 1 - dir);
      sibling->red = false;
      sibling = parent->link[1 - dir];
      if (!sibling->link[0]->red && !sibling->link[1]->red) {
        sibling->red = true;
        return true;
      }
      parent->red = true;
    }

    // Now, sibling must be black and one of the sibling's child must be red.
    if (!sibling->link[1 - dir]->red) {
      // Since one additional rotation is required after this block,
      // the code in this block omit the links between parent and
      // close_nephew. The code in this block also omit the color change,
      // since the color will be changed afterwards.
      Node *close_nephew = sibling->link[dir];
      sibling->link[dir] = close_nephew->link[1 - dir];
      close_nephew->link[1 - dir]->parent = sibling;

      close_nephew->link[1 - dir] = sibling;
      sibling->parent = close_nephew;

      sibling = close_nephew;
    }
    Rotate(parent, sibling, 1 - dir);
    sibling->red = parent->red;
    parent->red = sibling->link[1 - dir]->red = false;
    return true;
  }

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
                       std::vector<T> &result) {
    if (root == sentinel) return;
    Traverse(root->link[0], sentinel, result);
    result.push_back(root->value);
    Traverse(root->link[1], sentinel, result);
  }

  static void Rotate(Node *parent, Node *current, bool dir) {
    parent->link[dir] = current->link[1 - dir];
    current->link[1 - dir]->parent = parent;

    current->parent = parent->parent;
    ((parent == parent->parent->link[0]) ? parent->parent->link[0]
                                         : parent->parent->link[1]) = current;

    current->link[1 - dir] = parent;
    parent->parent = current;
  }

  // The sentinel's parent pointer can be changed arbitrarily in Insert/Delete.
  // The sentinel's link[0]/link[1] pointers can be changed arbitrarily in
  // Delete. Thus, the code should not depending on sentinel's parent pointer.
  Node *sentinel_ = &dummy_;
  Node dummy_{.link{sentinel_, sentinel_}, .parent{sentinel_}, .red{false}};
  // Use a header node so that the link[0] pointer points to the real root.
  // The benefit is that, when rotating around a node, the code does not need to
  // check whether the node is root or not to find correct pointer to update.
  Node header_{dummy_};
};

#endif
