#ifndef BINARY_SEARCH_TREE_TRAVERSAL_H
#define BINARY_SEARCH_TREE_TRAVERSAL_H

#include <queue>
#include <stack>
#include <vector>

template <typename Node>
void InorderTraverseRec(const Node* root,
                        std::vector<typename Node::value_type>& result) {
  if (root == nullptr) return;
  InorderTraverse(root->left, result);
  result.push_back(root->value);
  InorderTraverse(root->right, result);
}

template <typename Node>
void InorderTraverse(const Node* node,
                     std::vector<typename Node::value_type>& result) {
  for (std::stack<const Node*> stack; !stack.empty() || node != nullptr;) {
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

template <typename Node>
void InorderTraverse(const Node* node, typename Node::value_type* result) {
  int last = 0;
  for (std::stack<const Node*> stack; !stack.empty() || node != nullptr;) {
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

template <typename Node>
void InorderTraverseMorris(Node* node, typename Node::value_type* result) {
  for (int last = 0; node != nullptr;) {
    if (node->left != nullptr) {
      Node* previous = node->left;
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

template <typename Node>
void PreorderTraverseRec(const Node* root,
                         std::vector<typename Node::value_type>& result) {
  if (root == nullptr) return;
  result.push_back(root->value);
  PreorderTraverse(root->left, result);
  PreorderTraverse(root->right, result);
}

template <typename Node>
void PreorderTraverse(const Node* node,
                      std::vector<typename Node::value_type>& result) {
  if (node == nullptr) return;
  std::stack<const Node*> stack;
  for (stack.push(node); !stack.empty(); result.push_back(node->value)) {
    node = stack.top();
    stack.pop();
    // Push right child first so that left child will be processed first.
    if (node->right != nullptr) stack.push(node->right);
    if (node->left != nullptr) stack.push(node->left);
  }
}

template <typename Node>
void PreorderTraverse(const Node* node, typename Node::value_type* result) {
  if (node == nullptr) return;
  int last = 0;
  std::stack<const Node*> stack;
  for (stack.push(node); !stack.empty(); result[last++] = node->value) {
    node = stack.top();
    stack.pop();
    // Push right child first so that left child will be processed first.
    if (node->right != nullptr) stack.push(node->right);
    if (node->left != nullptr) stack.push(node->left);
  }
}

template <typename Node>
void PreorderTraverseMorris(Node* node, typename Node::value_type* result) {
  for (int last = 0; node != nullptr;) {
    if (node->left != nullptr) {
      Node* previous = node->left;
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

template <typename Node>
void PostorderTraverseRec(const Node* root,
                          std::vector<typename Node::value_type>& result) {
  if (root == nullptr) return;
  PostorderTraverse(root->left, result);
  PostorderTraverse(root->right, result);
  result.push_back(root->value);
}

template <typename Node>
void PostorderTraverse(const Node* node,
                       std::vector<typename Node::value_type>& result) {
  std::stack<const Node*> stack;
  for (const Node* previous = nullptr; !stack.empty() || node != nullptr;) {
    // Keep moving left.
    if (node != nullptr) {
      stack.push(node);
      node = node->left;
    } else {
      const Node* top = stack.top();
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

template <typename Node>
void PostorderTraverse(const Node* node, typename Node::value_type* result) {
  int last = 0;
  std::stack<const Node*> stack;
  for (const Node* previous = nullptr; !stack.empty() || node != nullptr;) {
    // Keep moving left.
    if (node != nullptr) {
      stack.push(node);
      node = node->left;
    } else {
      const Node* top = stack.top();
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

template <typename Node>
void reverse(Node* begin, Node* end) {
  for (Node *current = begin, *next = begin->right; current != end;) {
    Node* temp = next->right;
    next->right = current;
    current = next;
    next = temp;
  }
}

template <typename Node>
void PostorderTraverseMorris(Node* node, typename Node::value_type* result) {
  int last = 0;
  // Use dummy node to simplify the program assuming Node has a default
  // constructor.
  Node dummy(node, nullptr);
  for (node = &dummy; node != nullptr;) {
    if (node->left == nullptr) {
      node = node->right;
    } else {
      Node* previous = node->left;
      while (previous->right != nullptr && previous->right != node)
        previous = previous->right;
      if (previous->right == nullptr) {
        previous->right = node;
        node = node->left;
      } else {
        reverse(node->left, previous);
        for (Node* current = previous;; current = current->right) {
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

template <typename Node>
void LevelOrderTraverseQueue(const Node* node,
                             std::vector<typename Node::value_type>& result) {
  if (node == nullptr) return;
  std::queue<const Node*> queue;
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
// The nodes in the current level are stored in vector current. The nodes
// in the next level are stored in vector next.
template <typename Node>
void LevelOrderTraverse(const Node* node,
                        std::vector<typename Node::value_type>& result) {
  if (node == nullptr) return;
  for (std::vector<const Node *> current{node}, next; !current.empty();
       current.clear(), current.swap(next)) {
    for (const Node* node : current) {
      result.push_back(node->value);
      if (node->left != nullptr) next.push_back(node->left);
      if (node->right != nullptr) next.push_back(node->right);
    }
  }
}

template <typename Node>
void FreeTree(Node* root) {
  if (root == nullptr) return;
  FreeTree(root->left);
  FreeTree(root->right);
  delete root;
}

#endif
