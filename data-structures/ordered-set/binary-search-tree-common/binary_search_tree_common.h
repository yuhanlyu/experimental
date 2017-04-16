#ifndef BINARY_SEARCH_TREE_COMMON_H
#define BINARY_SEARCH_TREE_COMMON_H

#include <queue>
#include <stack>
#include <vector>

template <typename T>
void InorderTraverseRec(const T* root,
                        std::vector<typename T::value_type>& result) {
  if (root == nullptr) return;
  InorderTraverse(root->left, result);
  result.push_back(root->value);
  InorderTraverse(root->right, result);
}

template <typename T>
void InorderTraverse(const T* node,
                     std::vector<typename T::value_type>& result) {
  for (std::stack<const T*> stack; !stack.empty() || node != nullptr;) {
    if (node != nullptr) {
      stack.push(node);
      node = node->left;
    } else {
      result.push_back(stack.top()->value);
      node = stack.top()->right;
      stack.pop();
    }
  }
}

template <typename T>
void InorderTraverse(const T* node, typename T::value_type* result) {
  int last = 0;
  for (std::stack<const T*> stack; !stack.empty() || node != nullptr;) {
    if (node != nullptr) {
      stack.push(node);
      node = node->left;
    } else {
      result[last++] = stack.top()->value;
      node = stack.top()->right;
      stack.pop();
    }
  }
}

template <typename T>
void InorderTraverseMorris(T* node, typename T::value_type* result) {
  for (int last = 0; node != nullptr;) {
    if (node->left != nullptr) {
      T* previous = node->left;
      while (previous->right != nullptr && previous->right != node)
        previous = previous->right;
      if (previous->right != nullptr) {
        result[last++] = node->value;
        node = node->right;
        previous->right = nullptr;
      } else {
        previous->right = node;
        node = node->left;
      }
    } else {
      result[last++] = node->value;
      node = node->right;
    }
  }
}

template <typename T>
void PreorderTraverseRec(const T* root,
                         std::vector<typename T::value_type>& result) {
  if (root == nullptr) return;
  result.push_back(root->value);
  PreorderTraverse(root->left, result);
  PreorderTraverse(root->right, result);
}

template <typename T>
void PreorderTraverse(const T* node,
                      std::vector<typename T::value_type>& result) {
  if (node == nullptr) return;
  std::stack<const T*> stack;
  for (stack.push(node); !stack.empty(); result.push_back(node->value)) {
    node = stack.top();
    stack.pop();
    // Push right child first so that left child will be processed first.
    if (node->right != nullptr) stack.push(node->right);
    if (node->left != nullptr) stack.push(node->left);
  }
}

template <typename T>
void PreorderTraverse(const T* node, typename T::value_type* result) {
  if (node == nullptr) return;
  int last = 0;
  std::stack<const T*> stack;
  for (stack.push(node); !stack.empty(); result[last++] = node->value) {
    node = stack.top();
    stack.pop();
    // Push right child first so that left child will be processed first.
    if (node->right != nullptr) stack.push(node->right);
    if (node->left != nullptr) stack.push(node->left);
  }
}

template <typename T>
void PreorderTraverseMorris(T* node, typename T::value_type* result) {
  for (int last = 0; node != nullptr;) {
    if (node->left != nullptr) {
      T* previous = node->left;
      while (previous->right != nullptr && previous->right != node)
        previous = previous->right;
      if (previous->right != nullptr) {
        node = node->right;
        previous->right = nullptr;
      } else {
        result[last++] = node->value;
        previous->right = node;
        node = node->left;
      }
    } else {
      result[last++] = node->value;
      node = node->right;
    }
  }
}

template <typename T>
void PostorderTraverseRec(const T* root,
                          std::vector<typename T::value_type>& result) {
  if (root == nullptr) return;
  PostorderTraverse(root->left, result);
  PostorderTraverse(root->right, result);
  result.push_back(root->value);
}

template <typename T>
void PostorderTraverse(const T* node,
                       std::vector<typename T::value_type>& result) {
  std::stack<const T*> stack;
  for (const T* previous = nullptr; !stack.empty() || node != nullptr;) {
    // Keep moving left.
    if (node != nullptr) {
      stack.push(node);
      node = node->left;
    } else {
      const T* top = stack.top();
      // If right child exists and backtrack from left, traverse right subtree.
      if (top->right != nullptr && top->right != previous) {
        node = top->right;
      } else {
        // Both subtrees are traversed.
        result.push_back(top->value);
        previous = top;
        stack.pop();
      }
    }
  }
}

template <typename T>
void PostorderTraverse(const T* node, typename T::value_type* result) {
  int last = 0;
  std::stack<const T*> stack;
  for (const T* previous = nullptr; !stack.empty() || node != nullptr;) {
    // Keep moving left.
    if (node != nullptr) {
      stack.push(node);
      node = node->left;
    } else {
      const T* top = stack.top();
      // If right child exists and backtrack from left, traverse right subtree.
      if (top->right != nullptr && top->right != previous) {
        node = top->right;
      } else {
        // Both subtrees are traversed.
        result[last++] = top->value;
        previous = top;
        stack.pop();
      }
    }
  }
}

template <typename T>
void reverse(T* begin, T* end) {
  for (T *current = begin, *next = begin->right; current != end;) {
    T* temp = next->right;
    next->right = current;
    current = next;
    next = temp;
  }
}

template <typename T>
void PostorderTraverseMorris(T* node, typename T::value_type* result) {
  int last = 0;
  // Use dummy node to simplify the program assuming T has a default
  // constructor.
  T dummy;
  dummy.left = node;
  for (node = &dummy; node != nullptr;) {
    if (node->left == nullptr) {
      node = node->right;
    } else {
      T* previous = node->left;
      while (previous->right != nullptr && previous->right != node)
        previous = previous->right;
      if (previous->right == nullptr) {
        previous->right = node;
        node = node->left;
      } else {
        reverse(node->left, previous);
        for (T* current = previous;; current = current->right) {
          result[last++] = current->value;
          if (current == node->left) break;
        }
        reverse(previous, node->left);
        previous->right = nullptr;
        node = node->right;
      }
    }
  }
}

template <typename T>
void LevelOrderTraverseQueue(const T* node,
                             std::vector<typename T::value_type>& result) {
  if (node == nullptr) return;
  std::queue<const T*> queue;
  queue.push(node);
  while (!queue.empty()) {
    node = queue.front();
    queue.pop();
    result.push_back(node->value);
    if (node->left != nullptr) queue.push(node->left);
    if (node->right != nullptr) queue.push(node->right);
  }
}

// Use two vectors to traverse the tree in level order.
// The nodes in the current level are stored in vector current. The nodes in
// the next level are stored in vector next.
template <typename T>
void LevelOrderTraverse(const T* node,
                        std::vector<typename T::value_type>& result) {
  if (node == nullptr) return;
  for (std::vector<const T *> current{node}, next; !current.empty();
       current.clear(), current.swap(next)) {
    for (const T* node : current) {
      result.push_back(node->value);
      if (node->left != nullptr) next.push_back(node->left);
      if (node->right != nullptr) next.push_back(node->right);
    }
  }
}

template <typename T>
void FreeTree(T* root) {
  if (root == nullptr) return;
  FreeTree(root->left);
  FreeTree(root->right);
  delete root;
}

#endif
