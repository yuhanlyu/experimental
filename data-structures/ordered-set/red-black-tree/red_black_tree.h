#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <vector>

#include "../binary-search-tree-common/binary_search_tree_common.h"

template <typename T>
struct RBTree {
 public:
  struct Node {
    using value_type = T;
    explicit Node(const T& x, bool is_red = true) : value(x), red(is_red) {}
    Node() = default;
    union {
      Node* link[2] = {sentinel, sentinel};
      struct {
        Node* left;
        Node* right;
      };
    };
    T value;
    bool red = false;
  };

  bool Insert(const T& x) { return Insert(root_, x); }

  bool Delete(const T& x) {
    bool deleted = Delete(root_, x);
    root_->red = false;
    return deleted;
  }

  bool BottomUpInsert(const T& x) {
    bool done = false, inserted = BottomUpInsert(root_, x, done);
    root_->red = false;
    return inserted;
  }

  bool BottomUpDelete(const T& x) {
    bool done = false, deleted = BottomUpDelete(root_, x, done);
    root_->red = false;
    return deleted;
  }

  bool IsBalanced() const {
    if (sentinel->red) return false;
    if (sentinel->right != sentinel) return false;
    if (sentinel->left != sentinel) return false;
    if (root_->red) return false;
    return BlackHeight(root_) != -1;
  }

  bool TopDownInsert(const T& x) { return TopDownInsert(root_, x); }

  bool TopDownDelete(const T& x) { return TopDownDelete(root_, x); }

  ~RBTree() { FreeTree(root_, sentinel); }

  void InorderTraverse(std::vector<T>& result) const {
    return ::InorderTraverse(root_, result, sentinel);
  }

  Node* root() const { return root_; }

  Node*& root() { return root_; }

  void PrintTree() const { PrintTree(root_, "root"); }

  static void PrintTree(const Node* root, std::string prefix) {
    if (root == sentinel) return;
    PrintTree(root->left, prefix + "->left");
    std::cerr << prefix << " = " << root->value << ' '
              << (root->red ? 'R' : 'B') << '\n';
    PrintTree(root->right, prefix + "->right");
  }

 private:
  static int BlackHeight(const Node* node) {
    if (node == sentinel) return 1;
    if (node->red && (node->left->red || node->right->red)) return -1;
    int lh = BlackHeight(node->left), rh = BlackHeight(node->right);
    if (lh == -1 || rh == -1 || lh != rh) return -1;
    return lh + (node->red ? 0 : 1);
  }

  static bool Insert(Node*& node, const T& x) {
    if (node == sentinel) {
      node = new Node(x, false);
      return true;
    }
    if (node->left->red && node->right->red)
      node->left->red = node->right->red = false;
    Node **parent = &node, **safe_node = &node;
    // Find the lowest black node that has one black child.
    while ((*parent) != sentinel) {
      Node*& current = *parent;
      if (x == current->value) return false;
      // Use bitwise or is faster than the logical or.
      if (!current->red && (!current->left->red | !current->right->red))
        safe_node = parent;
      parent = x < current->value ? &current->left : &current->right;
    }
    *parent = new Node(x);
    Node *&update_node = *safe_node,
         *next =
             x < update_node->value ? update_node->left : update_node->right,
         *current = next;
    if (next == *parent) return true;
    bool need_rotation = next->red;
    if (need_rotation) current = x < next->value ? next->left : next->right;
    // Flip color from the current to parent.
    while (current != *parent) {
      current->red = true;
      current->left->red = current->right->red = false;
      current = x < current->value ? current->left : current->right;
      current = x < current->value ? current->left : current->right;
    }
    if (!need_rotation) return true;
    // At this point, safe_node is black, next is red, next's sibling is
    // black, and grand_child is red.
    update_node->red = true;
    if (x < update_node->value)
      update_node = x < next->value ? RightRotate(update_node) : LRRotate(update_node);
    else
      update_node = x < next->value ? RLRotate(update_node) : LeftRotate(update_node);
    update_node->red = false;
    return true;
  }

  static bool Delete(Node*& node, const T& x) {
    Node **parent = &node, **safe_node = &node, *current;
    if (!node->red && !node->left->red && !node->right->red) node->red = true;
    const T* delete_value = &x;
    // Find the node to be deleted and the lowest red node or black node with
    // red child/grandchild.
    for (current = node; current != sentinel; current = *parent) {
      // Using bitwise or is faster than logical or.
      if (current->red | current->left->red | current->right->red |
          current->left->left->red | current->left->right->red |
          current->right->left->red | current->right->right->red)
        safe_node = parent;
      if (x == current->value) break;
      parent = (x < current->value) ? &current->left : &current->right;
    }
    if (current == sentinel) return false;
    // When the node needed to be removed has two children, pull the minimum
    // value from the right tree and delete the minimum value in the right
    // tree.
    if (current->left != sentinel && current->right != sentinel) {
      Node* min = current->right;
      for (parent = &current->right; min->left != sentinel; min = min->left) {
        if (min->red | min->left->red | min->right->red | min->left->left->red |
            min->left->right->red | min->right->left->red |
            min->right->right->red)
          safe_node = parent;
        parent = &min->left;
      }
      current->value = min->value;
      delete_value = &current->value;
      current = min;
    }
    // The node pointed by current will be replaced by subtree.
    Node* subtree =
        (current->left != sentinel ? current->left : current->right);
    // If both current and subtree are black, rebalance is required.
    bool require_rebalance = current->red == subtree->red;
    delete current;
    // Assign subtree as black, since subtree is going to represent a black
    // node.
    subtree->red = false;
    *parent = subtree;
    if (!require_rebalance) return true;

    Node *next, *sibling;
    if (*delete_value < (*safe_node)->value) {
      next = (*safe_node)->left;
      sibling = (*safe_node)->right;
    } else {
      next = (*safe_node)->right;
      sibling = (*safe_node)->left;
    }
    // At this point, next is black.
    // For each black nodes below *safe_node, mark its sibling as red.
    for (current = next; current != subtree && current != sentinel;) {
      if (*delete_value < current->value) {
        current->right->red = true;
        current = current->left;
      } else {
        current->left->red = true;
        current = current->right;
      }
    }
    // When safe_node is black and sibling is red, rotate accordingly.
    if (!(*safe_node)->red && sibling->red) {
      Node*& node = *safe_node;
      node->red = true;
      sibling->red = false;
      if (*delete_value < node->value) {
        sibling = sibling->left;
        node = LeftRotate(node);
        safe_node = &node->left;
      } else {
        sibling = sibling->right;
        node = RightRotate(node);
        safe_node = &node->right;
      }
    }
    // When sibling's both children are black, recolor.
    if (!sibling->left->red && !sibling->right->red) {
      (*safe_node)->red = false;
      return sibling->red = true;
    }
    // At this point, both next and sibling are black, and one of sibling's
    // child is red.
    Node*& update_node = *safe_node;
    bool old_node_color = update_node->red;
    if (*delete_value < update_node->value)
      update_node = sibling->right->red ? LeftRotate(update_node) : RLRotate(update_node);
    else
      update_node = sibling->left->red ? RightRotate(update_node) : LRRotate(update_node);
    update_node->red = old_node_color;
    update_node->left->red = update_node->right->red = false;
    return true;
  }

  static bool BottomUpInsert(Node*& node, const T& x, bool& done) {
    // When the tree is empty, create the node at root;
    if (node == sentinel) {
      node = new Node(x);
      return true;
    }
    if (x == node->value) return false;
    if (x < node->value) {
      if (!BottomUpInsert(node->left, x, done)) return false;
      if (done) return true;
      // When the child is black, no violation can occur.
      if (!node->left->red) return done = true;
      // If children has same color, then flip the colo.
      if (node->right->red) {
        node->left->red = node->right->red = false;
        return node->red = true;
      }
      // If children has different color, rotate acordingly.
      if (node->left->left->red || node->left->right->red) {
        node = node->left->right->red ? LRRotate(node) : RightRotate(node);
        node->red = false;
        return done = node->right->red = true;
      }
    } else {
      if (!BottomUpInsert(node->right, x, done)) return false;
      if (done) return true;
      // When the child is black, no violation can occur.
      if (!node->right->red) return done = true;
      // If children has same color, then flip the colo.
      if (node->left->red) {
        node->left->red = node->right->red = false;
        return node->red = true;
      }
      // If children has different color, rotate acordingly.
      if (node->right->right->red || node->right->left->red) {
        node = node->right->left->red ? RLRotate(node) : LeftRotate(node);
        node->red = false;
        return done = node->left->red = true;
      }
    }
    return true;
  }

  static bool BottomUpDelete(Node*& node, const T& x, bool& done) {
    if (node == sentinel) return false;
    const T* delete_value = &x;
    if (x == node->value) {
      if (node->left == sentinel || node->right == sentinel) {
        Node* to_be_deleted = node;
        node = node->left == sentinel ? node->right : node->left;
        if (to_be_deleted->red)
          done = true;
        else if (node->red) {
          // If the child is red, recolor it as black.
          node->red = false;
          done = true;
        }
        delete to_be_deleted;
        return true;
      }
      Node* successor = node->right;
      while (successor->left != sentinel) successor = successor->left;
      node->value = successor->value;
      delete_value = &node->value;
    }
    if (*delete_value < node->value) {
      if (!BottomUpDelete(node->left, *delete_value, done)) return false;
      if (done) return true;
      Node **parent = &node, *&sibling = node->right;
      // When sibling is red, rotate to obtain a black sibling.
      if (sibling->red) {
        node->red = true;
        node = LeftRotate(node);
        node->red = false;
        // After rotation, adjust the sibling and parent.
        sibling = node->left->right;
        parent = &node->left;
      }
      if (sibling == sentinel) return true;
      // If black sibling has two black children.
      if (!sibling->left->red && !sibling->right->red) {
        if ((*parent)->red) {
          (*parent)->red = false;
          done = true;
        }
        return sibling->red = true;
      }
      // Black sibling has at least one red child.
      bool old_node_color = (*parent)->red;
      *parent = sibling->right->red ? LeftRotate(*parent) : RLRotate(*parent);
      (*parent)->red = old_node_color;
      (*parent)->left->red = (*parent)->right->red = false;
      return done = true;
    } else {
      if (!BottomUpDelete(node->right, *delete_value, done)) return false;
      if (done) return true;
      Node **parent = &node, *&sibling = node->left;
      // When sibling is red, rotate to obtain a black sibling.
      if (sibling->red) {
        node->red = true;
        node = RightRotate(node);
        node->red = false;
        // After rotation, adjust the sibling and parent.
        sibling = node->right->left;
        parent = &node->right;
      }
      if (sibling == sentinel) return true;
      // If black sibling has two black children.
      if (!sibling->left->red && !sibling->right->red) {
        if ((*parent)->red) {
          (*parent)->red = false;
          done = true;
        }
        return sibling->red = true;
      }
      // Black sibling has at least one red child.
      bool old_node_color = (*parent)->red;
      *parent = sibling->left->red ? RightRotate(*parent) : LRRotate(*parent);
      (*parent)->red = old_node_color;
      (*parent)->left->red = (*parent)->right->red = false;
      return done = true;
    }
  }

  static bool TopDownInsert(Node*& node, const T& x) {
    if (node == sentinel) {
      node = new Node(x, false);
      return true;
    }
    if (x == node->value) return false;
    for (Node *nil = &dummy, **gg_parent = &nil, **g_parent = &nil,
              **parent = &node;
         ;) {
      // Loop invariant: the sibling of parent (pointed by g_parent) is black.
      // current is the node points by the parent, but after the rotation,
      // parent might point to other node. But the search path is determined by
      // the current.
      Node* current = *parent;
      if (current == sentinel)
        current = *parent = new Node(x);
      else if (x == current->value)
        return node->red = false;
      else if (current->left->red && current->right->red) {
        // Flip color.
        current->red = true;
        current->left->red = current->right->red = false;
      }
      // When two red nodes are connected.
      if (current->red && (*g_parent)->red) {
        (*gg_parent)->red = true;
        if (x < (*gg_parent)->value)
          *gg_parent = x > (*g_parent)->value ? LRRotate(*gg_parent)
                                 : RightRotate(*gg_parent);
        else
          *gg_parent = x < (*g_parent)->value ? RLRotate(*gg_parent)
                                 : LeftRotate(*gg_parent);
        (*gg_parent)->red = false;
        // When rotation occurs, rotation cannot occurs in the next iteration.
        // 	 After double rotation, since current becomes black, red nodes
        // 	 violation won't occur in the next iteration.
        // 	 After single rotation, although current is red, since the
        // children
        // 	 and grand children must be black, red nodes violation won't
        // occur
        // 	 in the next iteration.
        // It is safe to set parent to be nil, since when double rotation
        // occurs, we loss the track of g_parent and gg_parent.
        parent = &nil;
      }
      if (x == current->value) break;
      gg_parent = g_parent;
      g_parent = parent;
      parent = x < current->value ? &current->left : &current->right;
    }
    node->red = false;
    return true;
  }

  static bool TopDownDelete(Node*& node, const T& x) {
    if (node == sentinel) return false;
    // Set sibling and g_parent to nil pointer to simplify the initial
    // condition.
    Node *to_be_deleted = sentinel, nil, *sibling = &nil, **g_parent = &sibling;
    for (Node **parent = &node, **next, **next_sibling; *parent != sentinel;
         g_parent = parent, parent = next, sibling = *next_sibling) {
      // Loop invariant: when current is black, the sibling is black, and
      // the parent node (pointed by g_parent) is red.
      Node*& current = *parent;
      if (x == current->value) to_be_deleted = current;
      if (x < current->value) {
        next = &current->left;
        next_sibling = &current->right;
      } else {
        next = &current->right;
        next_sibling = &current->left;
      }
      // Rebalance is required only when the current and the next node are
      // black.
      if (current->red || (*next)->red) continue;
      // When next sibling is red, rotate.
      if ((*next_sibling)->red) {
        current->red = true;
        (*next_sibling)->red = false;
        if (x < current->value) {
          *parent = LeftRotate(*parent);
          parent = &(*parent)->left;
        } else {
          *parent = RightRotate(*parent);
          parent = &(*parent)->right;
        }
        continue;
      }
      // Current has two black children.
      // If sibling has two black children, flip the color.
      if (!sibling->right->red && !sibling->left->red) {
        (*g_parent)->red = false;
        current->red = sibling->red = true;
        continue;
      }
      // If sibling has one red child, rebalance base on whether the
      // current node is left or right of its parent.
      if (*parent == (*g_parent)->left) {
        *g_parent = sibling->right->red ? LeftRotate(*g_parent) : RLRotate(*g_parent);
        parent = &(*g_parent)->left->left;
      } else {
        *g_parent = sibling->left->red ? RightRotate(*g_parent) : LRRotate(*g_parent);
        parent = &(*g_parent)->right->right;
      }
      current->red = (*g_parent)->red = true;
      (*g_parent)->left->red = (*g_parent)->right->red = false;
    }
    if (to_be_deleted == sentinel) return node->red = false;
    // When the loop terminates, (*g_parent)->value is the successor of x.
    to_be_deleted->value = (*g_parent)->value;
    to_be_deleted = *g_parent;
    *g_parent =
        (*g_parent)->left == sentinel ? (*g_parent)->right : (*g_parent)->left;
    delete to_be_deleted;
    node->red = false;
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
    x->left = y->right;
    root->right = y->left;
    y->left = root;
    y->right = x;
		return y;
  }

  static Node dummy;
  static constexpr Node* sentinel = &dummy;

  Node* root_ = sentinel;
};

// TODO(C++17): use inline variable.
template <typename T>
typename RBTree<T>::Node RBTree<T>::dummy;
#endif
