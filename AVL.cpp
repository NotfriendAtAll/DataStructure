//
// Created by DELL on 25-1-28.
//
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;
template <class T> class BSTtree;

template <class T> class TreeNode {
public:
  template <class U> friend class BSTtree;
  TreeNode(T data)
      : height(0), _data(data), index(0), left(nullptr), right(nullptr) {}

private:
  int height;
  T _data;
  int index;
  TreeNode *left;
  TreeNode *right;
};

template <class T> class BSTtree {
public:
  // 所有的外部API
  BSTtree() : _root(nullptr) {}
  int GetHeight(TreeNode<T> *&root);
  bool Balance_Factors(TreeNode<T> *root);
  void rrRotation(TreeNode<T> **root);
  void llRotation(TreeNode<T> *&root);
  void Insert(TreeNode<T> *&root, const int &val);
  TreeNode<T> *FindParent(TreeNode<T> *root, int target);
  void Preorder(TreeNode<T> *root);
  void Inorder(TreeNode<T> *root);
  void Postorder(TreeNode<T> *root);
  void SetHegiht(TreeNode<T> *&root);
  void Check() { std::cout << "the root data is " << _root->_data << '\n'; }
  TreeNode<T> *GetRoot() { return _root; }
  // 根节点
  TreeNode<T> *_root;
};
// 平衡因子
template <class T> bool BSTtree<T>::Balance_Factors(TreeNode<T> *root) {
  int leftheight = GetHeight(root->left);
  int rightheight = GetHeight(root->right);
  if (std::abs(leftheight - rightheight) == 2) {
    std::cout << "yes ";
    return true;
  }

  return false;
}
template <class T> int BSTtree<T>::GetHeight(TreeNode<T> *&root) {
  if (root == nullptr) {
    return 0;
  }
  return std::max(GetHeight(root->left), GetHeight(root->right)) + 1;
}

template <class T> void BSTtree<T>::SetHegiht(TreeNode<T> *&root) {
  int left_height = 0, right_height = 0;
  if (root->right) {
    left_height = GetHeight(root->right);
  } else if (root->left) {
    right_height = GetHeight(root->left);
  }
  root->height = std::max(left_height, right_height) + 1;
}
template <class T>
TreeNode<T> *BSTtree<T>::FindParent(TreeNode<T> *root, int target) {
  if (root->left->_data == target || root->right->_data == target) {
    return root;
  } else if (root->_data < target) {
    return FindParent(root->right, target);
  } else {
    return FindParent(root->left, target);
  }
}

template <class T> void BSTtree<T>::rrRotation(TreeNode<T> **root) {
  TreeNode<T> *current = (*root)->right;
  (*root)->right = current->left;
  current->left = *root;
  if (_root == *root) {
    _root = current;
  } else {
    TreeNode<T> *parent = FindParent(_root, (*root)->_data);
    TreeNode<T> **temp = &parent;
    (*temp)->right = current;
    SetHegiht(parent);
  }
  SetHegiht(current);
  SetHegiht((*root)->left);
}
template <class T> void BSTtree<T>::llRotation(TreeNode<T> *&root) {}

template <class T> void BSTtree<T>::Insert(TreeNode<T> *&root, const int &val) {
  if (root == nullptr) {
    root = new TreeNode(val);
  } else {
    if (root->_data < val) {
      Insert(root->right, val);
      // RR 调整
      if (Balance_Factors(root)) {
        if (val > root->right->_data) {
          rrRotation(&root);
        } // RL调整
        else {
          llRotation(root->right);
          rrRotation(&root);
        }
      }
    } else if (root->_data == val) {
      root->index++;
      return;
    } else {
      Insert(root->left, val);
      // LL 调整
      if (Balance_Factors(root)) {
        if (root->left->_data > val) {
          llRotation(root);
        } // LR 调整
        else {
          rrRotation(&root->left);
          llRotation(root);
        }
      }
    }
  }
  SetHegiht(root);
}
template <class T> void BSTtree<T>::Preorder(TreeNode<T> *root) {
  if (root == nullptr) {
    return;
  }
  std::cout << root->_data << " ";
  Preorder(root->left);
  Preorder(root->right);
}

template <class T> void BSTtree<T>::Inorder(TreeNode<T> *root) {
  if (root == nullptr) {
    return;
  }
  Inorder(root->left);
  std::cout << root->_data << " ";
  Inorder(root->right);
}

template <class T> void BSTtree<T>::Postorder(TreeNode<T> *root) {
  if (root == nullptr) {
    return;
  }
  Postorder(root->left);
  Postorder(root->right);
  std::cout << root->_data << " ";
}
int main() {
  BSTtree<int> bst;
  std::vector<int> test_arr{1, 2, 3, 4, 5, 6, 7, 8};
  for (auto &it : test_arr) {
    bst.Insert(bst._root, it);
  }
  bst.Preorder(bst._root);
  std::cout << '\n';
  bst.Inorder(bst._root);
  std::cout << '\n';
  bst.Postorder(bst._root);
  std::cout << '\n';
  auto height = bst.GetHeight(bst._root);
  std::cout << "the tree height is" << height << '\n';
  bst.Check();
  std::cout << "End" << '\n';
  return 0;
}
