#ifndef DSL_H
#define DSL_H

#include <limits>
#include <vector>

template <typename T>
struct DSL {
 public:
  struct Node {
    using value_type = T;
    Node(const T& x, Node* r, Node* d) : right(r), down(d), value(x) {}
    Node(Node* r, Node* d) : Node(std::numeric_limits<T>::max(), r, d) {}
    Node() : Node(this, this) {}
    Node* right;
    Node* down;
    T value;
  };

  bool Insert(const T& x) {
    bottom->value = x;
    for (Node* cur = header; cur != bottom; cur = cur->down) {
      while (x > cur->value) cur = cur->right;
      // If gap = 3, or at the bottom level.
      if (cur->value > cur->down->right->right->value) {
        cur->right = new Node(cur->value, cur->right, cur->down->right->right);
        cur->value = cur->down->right->value;
      } else if (cur->down == bottom)
        return false;
    }
    // Raise the header.
    if (header->right != tail) header = new Node(tail, header);
    return true;
  }

  bool Delete(const T& x) {
    if (header->down == bottom) return false;
    bool success = true;
    bottom->value = x;
    T last_above = header->value, predecessor;
    for (Node *cur = header->down, *previous, *next; cur != bottom;
         cur = next) {
      // Find the gap to be drop and the previous gap.
      for (; x > cur->value; cur = cur->right) previous = cur;
      next = cur->down;
      // If the gap size is one or in the bottom level.
      if (cur->value == next->right->value) {
        // If not in the last gap, merge with or borrow from the next gap.
        if (cur->value != last_above) {
          Node* tmp = cur->right;
          // If the next gap has size one, merge with the next gap.
          if (tmp->value == tmp->down->right->value || next == bottom) {
            cur->right = tmp->right;
            cur->value = tmp->value;
            delete tmp;
          } else {
            // Borrow from the next gap.
            cur->value = tmp->down->value;
            tmp->down = tmp->down->right;
          }
        } else if (previous->value <= previous->down->right->value) {
          // When the previous gap has only one element, merge.
          // At the bottom level, find the predecessor of x.
          if (next == bottom) predecessor = previous->value;
          previous->right = cur->right;
          previous->value = cur->value;
          delete cur;
          cur = previous;
        } else {
          // When the previous gap has more than one element, borrow.
          Node* tmp = (previous->value == previous->down->right->right->value
                           ? previous->down->right
                           : previous->down->right->right);
          previous->value = tmp->value;
          cur->down = tmp->right;
        }
      } else if (next == bottom) {
        // Cannot find the key. Since the header may need to be lowered,
        // should not return yet.
        success = false;
        break;
      }
      last_above = cur->value;
    }
    if (success) {
      // Replace v by its predecessor.
      for (Node* cur = header->down; cur != bottom; cur = cur->down) {
        while (x > cur->value) cur = cur->right;
        if (x == cur->value) cur->value = predecessor;
      }
    }
    // Lower the header, if necessary.
    if (header->down->right == tail) {
      Node* to_be_deleted = header;
      header = header->down;
      delete to_be_deleted;
    }
    return success;
  }

  void InorderTraverse(std::vector<T>& result) const {
    Node* cur = header;
    while (cur->down != bottom) cur = cur->down;
    for (; cur->right != tail; cur = cur->right) result.push_back(cur->value);
  }

  // Check the gaps is between 1 and 3.
  bool CheckGap() const {
    for (Node* cur = header; cur->down != bottom; cur = cur->down) {
      for (Node* begin = cur; begin != tail; begin = begin->right) {
        int gap_size = 0;
        for (Node* down = begin->down; down->value != begin->value;
             down = down->right) {
          ++gap_size;
        }
        if (gap_size < 1 || gap_size > 3) return false;
      }
    }
    return true;
  }

  ~DSL() {
    while (header != bottom) {
      Node* next = header->down;
      for (Node* cur = header; cur != tail;) {
        Node* to_be_deleted = cur;
        cur = cur->right;
        delete to_be_deleted;
      }
      header = next;
    }
  }

 private:
  static Node bottom_node;
  static Node tail_node;
  static constexpr Node* bottom = &bottom_node;
  static constexpr Node* tail = &tail_node;
  Node* header = new Node(tail, bottom);
};

// TODO(C++17): use inline variables.
template <typename T>
typename DSL<T>::Node DSL<T>::bottom_node;
template <typename T>
typename DSL<T>::Node DSL<T>::tail_node;
#endif
