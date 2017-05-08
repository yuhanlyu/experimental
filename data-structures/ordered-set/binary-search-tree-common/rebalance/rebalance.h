#ifndef BINARY_SEARCH_TREE_REBALANCE_H
#define BINARY_SEARCH_TREE_REBALANCE_H

#include <stack>
#include <vector>

// Rebalance the tree by copying all nodes to a vector and rebuild.
template <typename Node>
void NaiveRebalance(Node*& root) {
  if (root == nullptr) return;
  std::vector<Node*> nodes = ConvertTreeToVector(root);
  root = ConvertVectorToTree(nodes, 0, nodes.size());
}

// Build a tree from nodes.
template <typename Node>
Node* ConvertVectorToTree(const std::vector<Node*>& nodes, int begin, int end) {
  if (begin == end) return nullptr;
  int mid = (begin + end) / 2;
  Node* root = nodes[mid];
  root->left = ConvertVectorToTree(nodes, begin, mid);
  root->right = ConvertVectorToTree(nodes, mid + 1, end);
  return root;
}

// Convert a binary search tree to a vector in sorted order.
template <typename Node>
std::vector<Node*> ConvertTreeToVector(Node* node) {
  std::vector<Node*> nodes;
  for (std::stack<Node*> stack; !stack.empty() || node != nullptr;) {
    if (node != nullptr) {
      stack.push(node);
      node = node->left;
    } else {
      nodes.emplace_back(stack.top());
      node = stack.top()->right;
      stack.pop();
    }
  }
  return nodes;
}

// Rebalance the tree by flatten the tree and rebuild.
// TODO: implement the iterative version in the thesis.
template <typename Node>
void RebalanceByFlatten(Node*& root) {
  if (root == nullptr) return;
  int size = 0;
  Node dummy(nullptr, Flatten(root, &dummy, size));
  BuildTree(dummy.right, size);
  root = dummy.left;
}

// Build a balanced tree from a list pointed by head, assuming the length of
// the list is at least n + 1. Returning the n + 1's node in the list and the
// return node's left pointing to the root of the created balanced tree.
template <typename Node>
Node* BuildTree(Node* head, int size) {
  if (size == 0) {
    head->left = nullptr;
    return head;
  }
  --size;
  Node* root = BuildTree(head, size - size / 2);
  Node* last = BuildTree(root->right, size / 2);
  root->right = last->left;
  last->left = root;
  return last;
}

// Flatten a tree rooted at root use the right pointer, then append the list
// pointed by head.
template <typename Node>
Node* Flatten(Node* root, Node* head, int& size) {
  if (root == nullptr) return head;
  root->right = Flatten(root->right, head, size);
  return Flatten(root->left, root, ++size);
}

// Rebalance proposed by Day.
template <typename Node>
void RebalanceDay(Node*& root) {
  if (root == nullptr) return;
  int size = 0;
  Node dummy(nullptr, Strip(root, static_cast<Node*>(nullptr), size));
  VineToTreeDay(&dummy, size);
  root = dummy.right;
}

// Flatten a tree rooted at root use the right pointer, then append the list
// pointed by head and clear all left pointers.
template <typename Node>
Node* Strip(Node* root, Node* head, int& size) {
  if (root == nullptr) return head;
  root->right = Strip(root->right, head, size);
  Node* left = root->left;
  root->left = nullptr;
  return Strip(left, root, ++size);
}

// Day's vine to tree. The last level of the tree will not be filled from left
// to right.
template <typename Node>
void VineToTreeDay(Node* root, int size) {
  for (int NBack = size - 1, M = NBack / 2; M > 0; M = NBack / 2) {
    Compress(root, M);
    NBack = NBack - M - 1;
  }
}

// Rebalance proposed by Stout and Warren.
template <typename Node>
void RebalanceDSW(Node*& root) {
  if (root == nullptr) return;
  Node dummy(nullptr, root);
  VineToTree(&dummy, TreeToVine(&dummy));
  root = dummy.right;
}

// Flatten the tree.
template <typename Node>
int TreeToVine(Node* root) {
  int size = 0;
  for (Node *tail = root, *remainder = tail->right; remainder != nullptr;) {
    // If no lef subtree, move right.
    if (remainder->left == nullptr) {
      tail = remainder;
      remainder = remainder->right;
      ++size;
    } else {
      // Eliminate the leftward subtree by right rotation.
      Node* tempPtr = remainder->left;
      remainder->left = tempPtr->right;
      tempPtr->right = remainder;
      remainder = tempPtr;
      tail->right = tempPtr;
    }
  }
  return size;
}

// The size of the largest perfect binar tree with number of nodes bounded by
// size.
int FullSize(int size) {
  int result = 1;
  while (result <= size) result += result + 1;
  return result / 2;
}

// Convert a list to a balanced tree. The last level will be filled from left to
// right.
template <typename Node>
void VineToTree(Node* root, int size) {
  int full_count = FullSize(size);
  Compress(root, size - full_count);
  for (size = full_count; size > 1; size /= 2) Compress(root, size / 2);
}

// Compress a list of tree by left rotation.
template <typename Node>
void Compress(Node* root, int size) {
  for (int j = 0; j < size; ++j) {
    Node* child = root->right;
    root->right = child->right;
    root = root->right;
    child->right = root->left;
    root->left = child;
  }
}

#endif
