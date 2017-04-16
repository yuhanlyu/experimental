#ifndef BINARY_SEARCH_TREE_COMMON_H
#define BINARY_SEARCH_TREE_COMMON_H

template <typename T>
void InorderTraverse(T* root, std::vector<typename T::value_type>& result) {
  if (root == nullptr) return;
  InorderTraverse(root->left, result);
  result.push_back(root->value);
  InorderTraverse(root->right, result);
}

template <typename T>
void PreorderTraverse(T* root, std::vector<typename T::value_type>& result) {
  if (root == nullptr) return;
  result.push_back(root->value);
  PreorderTraverse(root->left, result);
  PreorderTraverse(root->right, result);
}

template <typename T>
void PostorderTraverse(T* root, std::vector<typename T::value_type>& result) {
  if (root == nullptr) return;
  PostorderTraverse(root->left, result);
  PostorderTraverse(root->right, result);
  result.push_back(root->value);
}

#endif
