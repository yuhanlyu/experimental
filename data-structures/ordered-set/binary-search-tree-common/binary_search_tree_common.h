#ifndef BINARY_SEARCH_TREE_COMMON_H
#define BINARY_SEARCH_TREE_COMMON_H

#include "rebalance/rebalance.h"
#include "traversal/traversal.h"

#include <iostream>
#include <string>

template <typename Node>
void FreeTree(Node* root) {
  if (root == nullptr) return;
  FreeTree(root->left);
  FreeTree(root->right);
  delete root;
}

template <typename Node>
void PrintTree(const Node* root) {
  PrintTree(root, "root");
}

template <typename Node>
void PrintTree(const Node* root, std::string prefix) {
  if (root == nullptr) return;
  PrintTree(root->left, prefix + "->left");
  std::cerr << prefix << " = " << root->value << '\n';
  PrintTree(root->right, prefix + "->right");
}

template <typename Node>
int TreeSize(const Node* root) {
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
void LeftRotation(Node*& root) {
  Node* x = root->right;
  root->right = x->left;
  x->left = root;
  root = x;
}

// Right rotation:
//    root          x       |
//    /  \         / \      |
//   x    c  To   a  root   |
//  / \              /  \   |
// a   b            b    c  |
template <typename Node>
void RightRotation(Node*& root) {
  Node* x = root->left;
  root->left = x->right;
  x->right = root;
  root = x;
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
void LRRotation(Node*& root) {
  Node *x = root->left, *y = x->right;
  x->right = y->left;
  root->left = y->right;
  y->left = x;
  y->right = root;
  root = y;
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
void RLRotation(Node*& root) {
  Node *x = root->right, *y = x->left;
  x->left = y->right;
  root->right = y->left;
  y->right = x;
  y->left = root;
  root = y;
}

#endif
