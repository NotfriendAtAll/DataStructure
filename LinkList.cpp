#include <iostream>
class Linklist;
class Node {
public:
  friend class Linklist;
  Node(int data, Node *next) : _data(data), _next(next) {}

private:
  int _data;
  Node *_next;
};

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

void Linklist::Insert(int key) {
  Node *new_node = new Node(key, nullptr);
  if (head == nullptr) {
    head = new_node;
  } else {
    Node *index = head;
    while (index->_next != nullptr) {
      index = index->_next;
    }
    index->_next = new_node;
  }
  length++;
}

void Linklist::Print() {
  Node *cur = head;
  while (cur != nullptr) {
    std::cout << cur->_data << "->";
    cur = cur->_next;
  }
  std::cout << "nullptr" << '\n';
}

void Linklist::Delete(int key) {
  if (!GetLength()) {
    std::cout << "Delete Error" << '\n';
    return;
  }
  Node *index = head;
  if (index->_data == key) {
    if (index->_next == nullptr) {
      delete index;
      head = nullptr;
    } else {
      while ((index->_next->_data != key) && (index->_next != nullptr)) {
        index = index->_next;
      }
      Node *flag = index->_next;
      index->_next = flag->_next;
      flag->_next = nullptr;
      delete flag;
    }
    length--;
  }
}

int Linklist::GetLength() { return length; }
int main() {
  Linklist list;
  list.Insert(11);
  list.Delete(11);
  list.Insert(12);
  list.Insert(13);
  list.Insert(14);
  list.Print();
  std::cout << "list" << list.GetLength();
  return 0;
}
/*
这是基于c++98的语言标准简单写的一个单链表，当然功能并不完善。
你也可以用c++11的标准来实现。最好不要手动释放内存，用RAII来管理会更好。
使用Clangd在Vscode上面编译通过。GCC和MSVC应该也可以。
*/
