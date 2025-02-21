## 数据结构 
**DataStructure**
---

## Build Project
```cpp
mkdir build
cmake -G Ninja -B ./build
cd ./build
Ninja
.exe
```
The list of the project 
---
 project
***
CMakeLists.txt
---
include
---
 1. hello.h
 ***
src
---
   1. hello.cpp
   2. main.cpp
   ***
   build
   ---
   cmakefiles,ninja.build,.cmake,...
   ***
   lib
   ---
- 课外话题
***
      先盲猜一波：“学校教学的数据结构，你可能不知道用在那里，有什么用也不清楚，是吗？”
      但是，从狭义的角度来看，这些基础的数据结构有点类似高中学的某个知识点，就是外界的要求是，你不能不学，即便工作时用的地方不多。毕竟工作时用的 数据结构 还真和我们学的不一样，逻辑都是相通，这是事实。同时本文档仅是用于本人学习的记录，并不完善，可以说是十分不足。
***
- 基础数据结构

 (关于定义，这些都是基于Ai生成的) 
1. **_List_** 
    *** 
    链表
    - 定义 
    ***
    1.链表（Linked List）
      链表是一种线性数据结构，由一系列节点组成，每个节点包含两部分：

      • 数据域：存储实际的数据。

      • 指针域：存储指向下一个节点的指针（或引用）。

      链表的特点是节点在内存中可以分散存储，通过指针将它们连接起来。链表分为单链表和双链表。
      简单定义：链表是由一系列节点组成的数据结构，每个节点包含数据域和指向下一个节点的指针域。
      ***
      ```cpp 
      class Linklist;
      class Node {
      public:
      friend class Linklist;
      Node(int data, Node *next) : _data(data), _next(next) {}
      private:
      int _data;
      Node *_next;
      };
      /*
      这是最基本的结构，数据域和指针域。
      再来看看这个class,包含了list的基本接口(API).*/
      class Linklist {
      public:
      Linklist() : head(nullptr), length(0) {}
      void Insert(int key);
      void Print();
      void Delete(int key);
      int GetLength();

      private:
      Node *head;
      int length;
      };
      ```
      当然，Linklist类里面的Private成员 head，相当于哨兵头的作用。
      Length用于记录当前表的长度。另外你需要实现以下API
      ：Insert Delete ...
    这里分析一个我写的Insert的逻辑。
***
```cpp 
void Linklist::Insert(int key) {
        /*构造节点*/
    Node *new_node = new Node(key, nullptr);
        /*判断head节点是否为空*/
    if (head == nullptr) {
        head = new_node;
    }
    else {
        /*用index节点记录，同时找到要插入的位置*/
        Node *index = head;
        while (index->_next != nullptr) {
        index = index->_next;
        }
        /*插入节点*/
        index->_next = new_node;
    }
        /*别忘了新增表的长度*/
    length++;
}
```
***
    删除是类似的逻辑，这里就不多赘述。这里啰嗦以下，双链表逻辑也是相通的，就是多了一个指针，麻烦一点。
    ```cpp
    template <class T> void DoubleList<T>::freelist() {
    while (head) {
    std::shared_ptr<LinkNode<T>> current(head);
    head = head->next;
    }
    }//可能好奇为啥不直接调用delete，智能指针帮助我们来监管内存的回收，手动释放内存不安全，这仅是一个例子，当然不形象，理解意思就好。
---
2. **_Stack_** 
- 定义
***
栈（Stack）
栈是一种后进先出（LIFO，Last In First Out）的数据结构。它支持两种主要操作：

• 入栈（Push）：将一个元素添加到栈的顶部。

• 出栈（Pop）：移除并返回栈顶的元素。

栈的特点是只能在栈顶进行操作，最后入栈的元素总是最先出栈。

简单定义：栈是一种后进先出的数据结构，只允许在栈顶进行插入和删除操作。
***
```cpp
template <class T, size_t size> class Stack {
public:
  Stack() : topindex(0) { std::fill(_stack, _stack + size, T()); }
  ~Stack() = default;
  void Push(T key);
  void Pop();
  bool IsFull();
  void Check();
private:
  int topindex;
  T _stack[size];
};
```
以上就是简陋的Stack的基本结构，我是用基于数组来操作的，当然**Vector**也可以，那你为啥还写数据结构呢？哈哈哈。与之前不同的是，用了一点模板知识，模板是c++98标准里面诞生的。**STL标准库**，有兴趣可以去读读。
```cpp
void Push(T key);
void Pop();
bool IsFull();
void Check();
```
至于这几个个API，逻辑太简单了，就不赘述了。
3. **_Queue_** 
***
- 定义
***
队列(Queue) 是一种先进先出（FIFO，First In First Out）的数据结构。它支持两种主要操作：

• 入队（Enqueue）：将一个元素添加到队列的尾部。

• 出队（Dequeue）：移除并返回队列头部的元素。

队列的特点是先进入的元素总是最先出队。

简单定义：队列是一种先进先出的数据结构，允许在尾部插入元素，在头部删除元素。
```cpp
template <class T, size_t size> class Queue {
public:
  Queue() : topindex(0) { std::fill(_Queue, _Queue + size, T()); }
  ~Queue() = default;
  void Push(T key);
  void Pop();
  bool IsFull();
  void Check();
private:
  int topindex;
  T _Queue[size];
};
```
看到这个结构，你应该反应过来，这不就是Stack改了一点吗。实际上，List改改就能做成Stack，Queue，那么就是 **链栈，链列**。
***
4. **_Tree_** 
- 定义
***
树(Tree) 是一种非线性的数据结构，由节点组成，每个节点可以有多个子节点。树的特点是没有环，且每个节点（除了根节点）都有一个父节点。常见的树有二叉树（每个节点最多有两个子节点）、二叉搜索树（左子树的所有节点值小于根节点值，右子树的所有节点值大于根节点值）等。

简单定义：树是一种非线性的数据结构，由节点组成，每个节点可以有多个子节点，且没有环。
基于树的基本结构不是很难理解，所以为了方便，我就直接快进到**AVL**（二叉排序搜索树）。**BST**(二叉搜索树)可以说是**AVL**的一个简陋版本。
```cpp
template <class T> class BSTtree;
template <class T> class TreeNode {
public:
  template <class U> friend class BSTtree;
  TreeNode(T data): height(0), _data(data), index(0), 
  left(nullptr), right(nullptr) {}
private:
  int height;
  T _data;
  int index;
  TreeNode *left;
  TreeNode *right;
};
```
***
这个就是树的基本结构。

**int height** (记录当前节点的高度);

**T _data**  (记录当前节点的值域);

**int index**  (记录当前节点的是否重复，0表示不重复);

**《TreeNode *left》**  (记录当前节点左孩子);

**《TreeNode *right》**  (记录当前节点右孩子);
***
树的基本API
```cpp
template <class T> class BSTtree {
public:
  BSTtree() : _root(nullptr) {}
  int GetHeight(TreeNode<T> *&root);//拿到当前节点的高度
  bool Balance_Factors(TreeNode<T> *root);//检查是否失衡
  void rrRotation(TreeNode<T> **root);//右旋
  void llRotation(TreeNode<T> *&root);//左旋
  void Insert(TreeNode<T> *&root, const int &val);//插入
  TreeNode<T> *FindParent(TreeNode<T> *root, int target);//找到当前节点的父节点
  void Preorder(TreeNode<T> *root);//前序遍历
  void Inorder(TreeNode<T> *root);//中序遍历
  void Postorder(TreeNode<T> *root);//后序遍历
  void SetHegiht(TreeNode<T> *&root);//设置当前节点的高度
  void Check() { std::cout << "the root data is " << _root->_data << '\n'; } ///test 函数
  TreeNode<T> *GetRoot() { return _root; }
  TreeNode<T> *_root;//树的root节点
};
```
***
接下来介绍一些简单的API
```cpp
template <class T> int BSTtree<T>::GetHeight(TreeNode<T> *&root) {
  if (root == nullptr) {
    return 0;
  }
  return std::max(GetHeight(root->left), GetHeight(root->right)) + 1;
}通过比较左右子树的height，取一个最大值加1，为空直接返回0.
```
***
```cpp
template <class T> void BSTtree<T>::SetHegiht(TreeNode<T> *&root) {
  int left_height = 0, right_height = 0;//初始化为0
  if (root->right) {
    right_height = GetHeight(root->right);//递归拿到右孩子的高度
  } else if (root->left) {
    left_height = GetHeight(root->left);//递归拿到右孩子的高度
  }
  root->height = std::max(left_height, right_height) + 1;
}对左右子树比较，取一个max，就是此时root的高度。
```
***
```cpp
template <class T>
TreeNode<T> *BSTtree<T>::FindParent(TreeNode<T> *root, T target)
{
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
}这个逻辑就比较简单，就是基于二叉树的特点；二分逻辑通过找target就可以找到该节点的父节点
```
***
```cpp
template <class T> void BSTtree<T>::Insert(TreeNode<T> *&root, const int &val) {
  if (root == nullptr) {
    root = new TreeNode(val);//root为空就构造节点
  } else {
    if (root->_data < val) {
      Insert(root->right, val);//大于当前节点的插入右孩子
      // RR 调整
      if (Balance_Factors(root))//判断插入是否失衡
       {
        if (val > root->right->_data){
          rrRotation(&root);
        } // RL调整
        else {
          llRotation(&(root->right));
          rrRotation(&root);
        }
      }
    } else if (root->_data == val) {
      root->index++;//这个index可以满足插入相同的值
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
  SetHegiht(root);//别忘记同时设置节点的高度
}
```
***
```cpp
template <class T> bool BSTtree<T>::Balance_Factors(TreeNode<T> *root) {
  int leftheight = GetHeight(root->left);
  int rightheight = GetHeight(root->right);
  if (std::abs(leftheight - rightheight) == 2) {
    return true;
  }
  return false;
}//我设置的是如果左右子树相差2，就认为树已经失衡，至于打印的内容是当时为了方便调试，观测代码
```
***
```cpp
//二级指针来操作
template <class T> void BSTtree<T>::rrRotation(TreeNode<T> **root) { // *root是导致失衡节点的父节点的父节点
  TreeNode<T> *current = (*root)->right;//拿到导致失衡节点的父节点
  (*root)->right = current->left;
  current->left = *root;
  if (_root == *root)//判断是否是第一次旋转
   {
    _root = current;//更新_root 根 节点
  } else {
    TreeNode<T> *parent = FindParent(_root, (*root)->_data);//拿到传入的*root的父节点
    TreeNode<T> **temp = &parent;
    (*temp)->right = current;
    SetHegiht(parent);//更新节点的高度
  }
  SetHegiht(current);//更新current节点的高度,同下
if ((*root)->right != nullptr) {
    SetHegiht((*root)->right);
  }
}
```
***
为啥用二级指针来操作，一个原因，要改一级指针的地址。当然一级指针也可以用指针引用。但是，我用指针引用来操作的时候，发现有bug，很奇怪。代码如下，当然以下的树结构比现在的多了一个parent指针，少了一个记录height的成员变量。
```cpp
template <class T> void BSTtree<T>::rrRotation(TreeNode<T> *&root) {
  TreeNode<T> *current = root->parent;
  if (current->parent) {
    if (current->parent->right == current) {
      current->parent->right = root;
    } else {
      current->parent->left = root;
    }
    root->parent = current->parent;
    root->left = current;
    current->parent = root;
  } else {
    root->parent = nullptr;
    current->parent = root;
    current->right = root->left;//bug就是出在这里，current->right和root同时变成了nullptr,我在clion里调试发现的。其他操作的都没有问题。因为current->right和root地址是相同的。但是，我暂时没有想到其他的解决办法。讲个笑话，当时我还以为能用**&去解决问题，结果出了更离谱的错误，编译器直接报错 “试图将TreeNode**绑定到非常量TreeNode**&引用上,我当时就知道那个傻蛋把右值绑定到一个非常量左值引用上"。哈哈。
    if (root->left) {
      root->left->parent = current;
    }
    else{
      root->left = current;
    }
  }
}
```
***
来看看测试代码，务必记住释放堆内存。另外，至于为啥不用一百万数据来检测，两个原因，电脑可运行内存有限，单线程运行。
```cpp
const int datasize = 10000; // 数据数量 一百万数据
  const int dataRange = 10000; // 数据范围 1~1000000
  auto start = std::chrono::high_resolution_clock::now();
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = end - start;
```
但是测试的是单线程插入十万个数据，数据范围是1~100000，插入时间大概是，1.5w多毫秒。
```cpp
template <class T> void BSTtree<T>::Preorder(TreeNode<T> *root) {
  if (root == nullptr) {
    return;
  }
  std::cout << root->_data << " ";
  Preorder(root->left);
  Preorder(root->right);
}前序遍历，先打印该节点，再遍历左子树，再遍历右子树，遇空就退出递归。
```
***
至于中序遍历和后序遍历都是类似的逻辑。
当然**AVL**的代码是在clion上测试编译通过的，我也只是测试部分例子，代码理论上没有问题。CMake文件如下
```cpp
cmake_minimum_required(VERSION 3.28) //cmake最低版本
project(ClionCode) //项目名字
set(CMAKE_CXX_STANDARD 20) //语言标准 c++20
add_executable(ClionCode test.cpp) //可执行文件
```
---
我肯定推荐你使用 **(Clion/VS2022/VsCode)+CMake搭配vcpkg(c++包管理工具)+MarkBench(测试框架)**
来开发与管理你的Project,不得承认，linux上开发会方便的多，Windows也可以。
---
4. **_Graph_** 
- 定义

在数据结构中，图是一种由顶点（或称为节点）和边（或称为弧）组成的数据结构。它用于表示对象之间的多对多关系。具体来说：• 顶点（Vertex）**：图中的基本元素，表示一个对象。• 边（Edge）：连接两个顶点的线，表示两个对象之间的关系。如果边有方向，称为有向边，此时图是有向图；如果边没有方向，称为无向边，此时图是无向图。
***
**1. 整体结构**
想象你要建立一个「城市交通网络模型」：
- **节点(Node)**：代表城市（比如北京、上海）
- **边(Edge)**：代表城市之间的公路
- **邻接表**：就像每个城市的「通讯录」，记录它能直接到达哪些城市

代码中的 `Graph` 类就是整个交通网络模型。
### **2. 节点类 (Node Class)**
```cpp
class Node {
public:
    string name;  // 城市名称
    vector<shared_ptr<Node>> neighbors; // 相邻城市列表
    explicit Node(string nodeName) : name(move(nodeName)) {}
};
```
- **name**：城市的名字（比如 "北京"）
- **neighbors**：这个城市可以直接到达的邻居城市列表
- **shared_ptr**：智能指针（类似「自动管家」），能自动管理内存，防止内存泄漏
---
### **3. 图的构建方法**
#### **(1) 添加节点**
```cpp
void addNode(const string& nodeName) {
    if (!nodes.count(nodeName)) { // 如果不存在这个城市
        nodes[nodeName] = make_shared<Node>(nodeName); // 新建一个城市
    }
}
```
- 作用：确保不会重复添加同名城市
- 示例：`addNode("北京")` 会在图中创建北京节点
#### **(2) 添加边**
```cpp
void addEdge(const string& from, const string& to, bool bidirectional = false) {
    addNode(from);  // 确保起点存在
    addNode(to);    // 确保终点存在
    nodes[from]->neighbors.push_back(nodes[to]); // 添加单向路
    if (bidirectional) {
        nodes[to]->neighbors.push_back(nodes[from]); // 如果是双向，添加反向路
    }
}
```
- 作用：在两个城市之间修路
- 示例：`addEdge("北京", "上海")` 表示修一条北京到上海的单向公路
- `bidirectional=true` 时，相当于双向公路（比如北京←→上海）
---
### **4. 遍历算法**
#### **(1) BFS（广度优先搜索）**
```cpp
void BFS(const string& startNode) {
    // ...（初始化队列和访问标记）
    while (!q.empty()) {
        auto current = q.front(); // 取出队列第一个城市
        q.pop();
        cout << current->name << " "; // 输出城市名
        // 遍历所有邻居
        for (const auto& neighbor : current->neighbors) {
            if (!visited[neighbor->name]) { // 如果邻居没被访问过
                visited[neighbor->name] = true; // 标记为已访问
                q.push(neighbor); // 加入队列
            }
        }
    }
}
```
- **过程**：
  1. 从起点开始，先访问所有直接相邻的城市
  2. 再访问这些相邻城市的相邻城市
  3. 使用队列（排队机制）保证顺序
#### **(2) DFS（深度优先搜索）**
```cpp
void DFS(const string& startNode) {
    // ...（初始化栈和访问标记）
    while (!s.empty()) {
        auto current = s.top(); // 取出栈顶城市
        s.pop();
        cout << current->name << " "; // 输出城市名

        // 反向遍历邻居（为了和递归DFS顺序一致）
        for (auto it = rbegin(current->neighbors); it != rend(current->neighbors); ++it) {
            if (!visited[(*it)->name]) {
                visited[(*it)->name] = true;
                s.push(*it);
            }
        }
    }
}
```
- **过程**：
  1. 从起点出发，随机选一个方向走到尽头
  2. 遇到死路后回退到上一个岔路
  3. 使用栈（后进先出）实现回退机制
- **注意**：代码中反向遍历邻居是为了匹配递归DFS的顺序
---
本案例在VsCode上用Clangd编译通过。