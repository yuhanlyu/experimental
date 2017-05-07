#ifndef BINARY_SEARCH_TREE_COMMON_H
#define BINARY_SEARCH_TREE_COMMON_H

#include "rebalance/rebalance.h"
#include "traversal/traversal.h"

template <typename Node>
void FreeTree(Node* root) {
  if (root == nullptr) return;
  FreeTree(root->left);
  FreeTree(root->right);
  delete root;
}

template <typename Node>
int TreeSize(Node* root) {
  if (root == nullptr) return 0;
  return 1 + TreeSize(root->left) + TreeSize(root->right);
}

// Left rotation:
//    root           x    |
//    /  \          / \   |
//   a    x   To root  c  |
//       / \     /  \     |
//      b    c  a    b    |
template <typename Node>
Node* LeftRotation(Node* root) {
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
template <typename Node>
Node* RightRotation(Node* root) {
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
template <typename Node>
Node* LRRotation(Node* root) {
  Node *x = root->left, y = x->right;
  x->right = y->left;
  y->left = x;
  root->left = y->right;
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
template <typename Node>
Node* RLRotation(Node* root) {
  Node *x = root->right, y = x->left;
  x->left = y->right;
  y->right = x;
  root->right = y->left;
  y->left = root;
  return y;
}

#endif
