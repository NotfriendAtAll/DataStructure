## Data Structure
**DataStructure**
---

## Build Project (Linux Environment with Clang 18)
To build the project, follow these steps:

```bash
# Step 1: Create a build directory
mkdir build

# Step 2: Generate build files using CMake with Ninja
cmake -G Ninja -B ./build -DCMAKE_CXX_COMPILER=clang++-18

# Step 3: Build the project
cd ./build
ninja

# Step 4: Run the executable
./main
```

### Requirements
- **Operating System**: Linux (Ubuntu 20.04 or later recommended)
- **Compiler**: Clang 18 (supports C++20 standard)
- **Build System**: CMake (version 3.28 or later) with Ninja
- **Dependencies**: Ensure `libstdc++` or `libc++` is installed for C++ standard library support.

---

### Project Structure
```
project
├── CMakeLists.txt
├── include
│   └── hello.h
├── src
│   ├── hello.cpp
│   ├── main.cpp
├── build
│   ├── cmakefiles
│   ├── ninja.build
│   └── other build files...
└── lib
```

---

### Extracurricular Topics
***
Let's make a guess: "The data structures taught in school—you might not know where to use them or what they're for, right?"  
However, from a narrow perspective, these basic data structures are somewhat like certain knowledge points in high school—external requirements dictate that you must learn them, even if they're not frequently used at work. Indeed, the data structures used in work are different from what we learn, but the logic remains the same.  
This document is merely a record of my learning and is far from complete; it can be said to be quite insufficient.
***
- Basic Data Structures

 (Regarding definitions, these are AI-generated) 
1. **_List_** 
    *** 
    Here's an analysis of the logic of an Insert function I wrote.
***
```cpp 
void Linklist::Insert(int key) {
        /*Construct node*/
    length++;
}
```
***
    The deletion logic is similar, so I won't elaborate. As for doubly linked lists, the logic is similar, just with an additional pointer, making it slightly more complex.
    //You might wonder why not directly call delete - smart pointers help us manage memory reclamation, and manual memory release is unsafe. This is just an example, not very illustrative, but understanding the concept is what matters.
---
2. **_Stack_** 
- Definition
***
Stack
A stack is a Last In First Out (LIFO) data structure. It supports two main operations:

• Push: Adds an element to the top of the stack.

• Pop: Removes and returns the top element of the stack.

The stack's characteristic is that operations can only be performed at the top, and the last element pushed is always the first to be popped.

Simple definition: A stack is a LIFO data structure that only allows insertion and deletion operations at the top.
***
```cpp
template <class T, size_t size> class Stack {
public:
  Stack() : topindex(0) { std::fill(_stack, _stack + size, T()); }
  void Check();
private:
  int topindex;
  T _stack[size];
};
```
Above is the basic structure of a simple Stack, implemented using an array. Of course, you could use a **Vector**, but then why write data structures? Haha. Unlike before, I used some template knowledge here - templates were introduced in the C++98 standard. **STL Standard Library** - you can read about it if interested.
```cpp
void Push(T key);
void Pop();
bool IsFull();
void Check();
```
As for these APIs, the logic is too simple to elaborate on.
3. **_Queue_** 
***
- Definition
***
Queue is a First In First Out (FIFO) data structure. It supports two main operations:

• Enqueue: Adds an element to the end of the queue.

• Dequeue: Removes and returns the element from the front of the queue.

The queue's characteristic is that the first element to enter is always the first to leave.

Simple definition: A queue is a FIFO data structure that allows insertion at the tail and deletion at the head.
```cpp
template <class T, size_t size> class Queue {
public:
  Queue() : topindex(0) { std::fill(_Queue, _Queue + size, T()); }
  void Check();
private:
  int topindex;
  T _Queue[size];
};
```
Looking at this structure, you might realize it's just a slightly modified Stack. In fact, a List can be modified to create a Stack or Queue, resulting in **Linked Stack, Linked Queue**.
***
4. **_Tree_** 
- Definition
***
Tree is a non-linear data structure composed of nodes, where each node can have multiple child nodes. Trees are characterized by having no cycles, and each node (except the root) has one parent node. Common types include binary trees (each node has at most two children) and binary search trees (left subtree values are smaller than the root, right subtree values are larger than the root).

Simple definition: A tree is a non-linear data structure composed of nodes, where each node can have multiple child nodes and contains no cycles.
For simplicity, I'll jump directly to **AVL** (Binary Sort Search Tree). **BST** (Binary Search Tree) can be considered a simplified version of **AVL**.
```cpp
template <class T> class BSTtree;
template <class T> class TreeNode {
public:
  template <class U> friend class BSTtree;
  left(nullptr), right(nullptr) {}
private:
  int height;
  TreeNode *right;
};
```
***
This is the basic tree structure.

**int height** (Records the current node's height);

**T _data**  (Records the current node's value);

**int index**  (Records whether the current node is duplicated, 0 means no duplication);

**TreeNode *left**  (Records the current node's left child);

**TreeNode *right**  (Records the current node's right child);
***
Basic Tree APIs
```cpp
template <class T> class BSTtree {
public:
  BSTtree() : _root(nullptr) {}
  TreeNode<T> *_root;//Tree's root node
};
```
***
Let's introduce some simple APIs
```cpp
template <class T> int BSTtree<T>::GetHeight(TreeNode<T> *&root) {
  if (root == nullptr) {
  return std::max(GetHeight(root->left), GetHeight(root->right)) + 1;
}Compare the heights of left and right subtrees, take the maximum value plus 1, return 0 if empty.
```
***
```cpp
template <class T> void BSTtree<T>::SetHegiht(TreeNode<T> *&root) {
  int left_height = 0, right_height = 0;//Initialize to 0
  root->height = std::max(left_height, right_height) + 1;
}Compare left and right subtrees, take the max, which becomes the current root's height.
```
***
```cpp
template <class T>
TreeNode<T> *BSTtree<T>::FindParent(TreeNode<T> *root, T target)
{
if ((root->left != nullptr) && root->left->_data == target) {
    return root;
  }
}This logic is relatively simple, based on binary tree properties; binary search logic to find the parent node of the target
```
***
```cpp
template <class T> void BSTtree<T>::Insert(TreeNode<T> *&root, const int &val) {
  if (root == nullptr) {
  SetHegiht(root);//Don't forget to set the node's height
}
```
***
```cpp
template <class T> bool BSTtree<T>::Balance_Factors(TreeNode<T> *root) {
  int leftheight = GetHeight(root->left);
  return false;
}//I set it so that if the difference between left and right subtrees is 2, the tree is considered unbalanced. The print statements were for debugging convenience.
```
***
```cpp
//Using double pointer
template <class T> void BSTtree<T>::rrRotation(TreeNode<T> **root) { // *root is the grandparent of the node causing imbalance
  TreeNode<T> *current = (*root)->right;//Get the parent of the node causing imbalance
  (*root)->right = current->left;
  current->left = *root;
  if (_root == *root)//Check if this is the first rotation
   {
    _root = current;//Update _root node
  } else {
    TreeNode<T> *parent = FindParent(_root, (*root)->_data);//Get the parent node of the input *root
    TreeNode<T> **temp = &parent;
    (*temp)->right = current;
    SetHegiht(parent);//Update node height
  }
  SetHegiht(current);//Update current node height, same below
if ((*root)->right != nullptr) {
    SetHegiht((*root)->right);
  }
}
```
***
Why use double pointers? One reason is to modify the address of a single pointer. Of course, pointer references could also be used with single pointers. However, when I tried using pointer references, I found a strange bug. Here's the code, though note that this tree structure has an additional parent pointer and lacks a height member variable compared to the current version.
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
    current->right = root->left;//The bug occurs here - both current->right and root become nullptr simultaneously, which I discovered while debugging in CLion. This happens because current->right and root share the same address. Other operations work fine. I haven't found another solution yet. Here's a funny story: I thought I could solve it using **&, but that led to an even more bizarre error - the compiler complained "attempting to bind TreeNode** to non-const TreeNode**& reference, that's when I realized that fool was trying to bind an rvalue to a non-const lvalue reference". Haha.
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
Let's look at the test code. Remember to free heap memory. As for why we're not testing with a million data points, there are two reasons: limited computer memory and single-threaded execution.
```cpp
const int datasize = 10000; // Data size one million
  const int dataRange = 10000; // Data range 1~1000000
  auto start = std::chrono::high_resolution_clock::now();
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = end - start;
```
However, testing single-threaded insertion of 100,000 numbers in the range 1~100000 takes about 15,000+ milliseconds.
```cpp
template <class T> void BSTtree<T>::Preorder(TreeNode<T> *root) {
  if (root == nullptr) {
    return;
  }
  std::cout << root->_data << " ";
  Preorder(root->left);
  Preorder(root->right);
}//Preorder traversal: first print the node, then traverse left subtree, then right subtree, exit recursion when encountering null.
```
***
The logic for inorder and postorder traversal is similar.
Of course, the **AVL** code was tested and compiled successfully on CLion, and I only tested some examples. The code should theoretically be problem-free. Here's the CMake file:
```cpp
cmake_minimum_required(VERSION 3.28) //minimum cmake version
project(ClionCode) //project name
set(CMAKE_CXX_STANDARD 20) //language standard c++20
add_executable(ClionCode test.cpp) //executable file
```
---
I definitely recommend using **(Clion/VS2022/VsCode)+CMake with vcpkg(C++ package manager)+MarkBench(testing framework)**
to develop and manage your Project. Admittedly, development is much more convenient on Linux, though Windows works too.
---
4. **_Graph_**
- Definition
***
Graph
A graph is a non-linear data structure composed of vertices (nodes) and edges. It supports representing many-to-many relationships between objects. Key components:

• Vertices: Basic elements representing objects
• Edges: Lines connecting vertices, representing relationships between objects
• Direction: Edges can be directed (with arrows) or undirected

Simple definition: A graph is a structure made up of vertices and edges that can represent complex relationships between objects.

### **1. Basic Structure**
Think of it as a "City Transportation Network":
- Vertices are like cities (e.g., Beijing, Shanghai)
- Edges are like highways between cities
- The neighbor list is like each city's "contact list" showing which cities it connects to directly

### **2. Implementation**
```cpp
class Node {
public:
    string name;  // City name
    vector<shared_ptr<Node>> neighbors;  // List of connected cities
    explicit Node(string nodeName) : name(move(nodeName)) {}
};

class Graph {
private:
    unordered_map<string, shared_ptr<Node>> nodes;  // All cities in the network
public:
    void addNode(const string& name);
    void addEdge(const string& from, const string& to, bool bidirectional = false);
    void BFS(const string& start);
    void DFS(const string& start);
};
```

### **3. Graph Traversal**
Two main methods:

1. **BFS (Breadth-First Search)**
   - Like exploring a city level by level
   - Uses a queue to track nodes to visit
   - Good for finding shortest paths

2. **DFS (Depth-First Search)**
   - Like exploring one complete path before backtracking
   - Uses a stack (or recursion)
   - Good for exploring all possible paths

```cpp
void Graph::BFS(const string& start) {
    queue<shared_ptr<Node>> q;
    unordered_set<string> visited;
    
    auto startNode = nodes[start];
    q.push(startNode);
    visited.insert(start);
    
    while (!q.empty()) {
        auto current = q.front();
        q.pop();
        cout << current->name << " ";
        
        for (const auto& neighbor : current->neighbors) {
            if (!visited.count(neighbor->name)) {
                visited.insert(neighbor->name);
                q.push(neighbor);
            }
        }
    }
}
```

This completes the implementation of basic data structures including List, Stack, Queue, Tree, and Graph. The code has been tested and works correctly with the specified build system.

For more advanced features and optimizations, consider:
- Using smart pointers for memory management
- Adding error handling
- Implementing more complex algorithms (Dijkstra's, A*, etc.)
- Adding serialization support
- Implementing thread-safe versions

---
Build and test with:
```bash
mkdir build
cd build
cmake ..
make
./test
```