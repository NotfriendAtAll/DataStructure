//
// Created by DELL on 25-1-28.
//
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>
#include <random>
#include <vector>

template <class T> class BSTtree;

template <class T> class TreeNode {
public:
  template <class U> friend class BSTtree;
  TreeNode(T data)
      : height(0), _data(data), index(0), left(nullptr), right(nullptr) {}
~TreeNode()=default;
private:
  int height;
  T _data;
  int index;
 TreeNode<T>*left;
  TreeNode<T> *right;
};

template <class T> class BSTtree {
public:
  // 所有的外部API
  BSTtree() : _root(nullptr) {}
  ~BSTtree(){Destory(_root);}
  int GetHeight(TreeNode<T> *&root);
  bool Balance_Factors(TreeNode<T> *root);
  void rrRotation(TreeNode<T> **root);
  void llRotation(TreeNode<T> **root);
  void Insert(TreeNode<T> *&root, const T &val);
  TreeNode<T> *FindParent(TreeNode<T> *root, T target);
  void Preorder(TreeNode<T> *root);
  void Inorder(TreeNode<T> *root);
  void Postorder(TreeNode<T> *root);
  void SetHegiht(TreeNode<T> *&root);
  void Destory(TreeNode<T>*root);
  void Check() { std::cout << "the root data is " << _root->_data << '\n'; }
  void ExitTarget(TreeNode<T> *root, T target);
  TreeNode<T> *GetRoot() { return _root; }
  // 根节点
  TreeNode<T> *_root;
};
// 平衡因子
template <class T> bool BSTtree<T>::Balance_Factors(TreeNode<T> *root) {
  int leftheight = GetHeight(root->left);
  int rightheight = GetHeight(root->right);
  if (std::abs(leftheight - rightheight) == 2) {
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
TreeNode<T> *BSTtree<T>::FindParent(TreeNode<T> *root, T target) {
  if ((root->left != nullptr) && root->left->_data == target) {
    return root;
  }
  if ((root->right != nullptr) && root->right->_data == target) {
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
    if (parent->right == *root) {
      (*temp)->right = current;
    } else {
      (*temp)->left = current;
    }
    SetHegiht(parent);
  }
  SetHegiht(current);
  if ((*root)->right != nullptr) {
    SetHegiht((*root)->right);
  }
}

template <class T> void BSTtree<T>::llRotation(TreeNode<T> **root) {
  TreeNode<T> *current = (*root)->left;
  (*root)->left = current->right;
  current->right = *root;
  if (_root == *root) {
    _root = current;
  } else {
    TreeNode<T> *parent = FindParent(_root, (*root)->_data);
    TreeNode<T> **temp = &parent;
    if (parent->right == *root) {
      (*temp)->right = current;
    } else {
      (*temp)->left = current;
    }
    SetHegiht(parent);
  }
  SetHegiht(current);
  if ((*root)->left != nullptr) {
    SetHegiht((*root)->left);
  }
}

template <class T> void BSTtree<T>::Insert(TreeNode<T> *&root, const T &val) {
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
          llRotation(&(root->right));
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
          llRotation(&root);
        } // LR 调整
        else {
          rrRotation(&(root->left));
          llRotation(&root);
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
template <class T> void BSTtree<T>::ExitTarget(TreeNode<T> *root, T target) {
  if (root->_data == target) {
    std::cout << "Exit the target,and the index=" << root->index << std::endl;
    return;
  } else if (root->_data < target) {
    FindParent(root->right, target);
  } else {
    FindParent(root->left, target);
  }
}
template <class T>
void BSTtree<T>:: Destory(TreeNode<T> *root){
  if (root==nullptr) {
  return;
  }
  Destory(root->left);
  Destory(root->right);
  delete root;
}

// 生成随机整数数据
std::vector<int> generateRandomData(int size, int range) {
  std::vector<int> randomNumbers;
  try {
    randomNumbers.reserve(size); // 预先分配空间
    // 使用基于时间的种子（如果性能要求高）
    auto seed =
        std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dis(1, range);

    for (int i = 0; i < size; ++i) {
      randomNumbers.push_back(dis(gen));
    }

  } catch (const std::exception &e) {
    std::cerr << "Exception is" << e.what() << std::endl;
  }
  return randomNumbers;
}

int main() {
  const int datasize = 10000; // 数据数量 一百万数据
  const int dataRange = 10000; // 数据范围 1~1000000
  BSTtree<int> bst;
  std::vector<int> test_arr{6, 5, 4, 3, 2, 1};
  std::vector<int> testdata = generateRandomData(datasize, dataRange);
  try {
  auto start = std::chrono::high_resolution_clock::now();
  /*for (auto &it :testdata) {
  std::cout<<it<<' ';
  }*/
  // std::cout<<std::endl;
  for (auto &it : testdata) {
    bst.Insert(bst._root, it);
  }
  auto end = std::chrono::high_resolution_clock::now();
  // 计算并输出插入时间
  std::chrono::duration<double, std::milli> duration = end - start;
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
  std::cout << "插入 " << datasize << " 个数据耗时: " << duration.count()
            << " 毫秒" << std::endl;
  } catch (std::exception&error) {
  std::cerr<<"The exception is"<<error.what()<<std::endl;
  }
  return 0;
}