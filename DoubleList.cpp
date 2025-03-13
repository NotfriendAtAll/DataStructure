#include <iostream>
#include <memory>

template <typename T> class DoubleList;

template <class T> class LinkNode {
  template <typename U> friend class DoubleList;

public:
  explicit LinkNode(T data) : data((data)), pre(nullptr), next(nullptr) {}

private:
  T data;
  LinkNode<T> *pre;
  LinkNode<T> *next;
};

template <class T> class DoubleList {
public:
  explicit DoubleList() : head(nullptr) {}
  ~DoubleList() { freelist(); }
  void freelist();
  void Push(T data);
  void Print();
  void Delete(T key);
  bool IsEmpty();

private:
  LinkNode<T> *head;
};

template <class T> void DoubleList<T>::Push(T data) {
  auto *temp = new LinkNode<T>(data);
  if (head == nullptr) {
    head = temp;
  } else {
    auto *start = head;
    while (start->next) {
      start = start->next;
    }
    start->next = temp;
    temp->pre = start;
  }
}

template <class T> void DoubleList<T>::Print() {
  auto *temp = head;
  while (temp) {
    std::cout << temp->data << "->";
    temp = temp->next;
  }
  std::cout << "nullptr";
}

template <class T> void DoubleList<T>::freelist() {
  while (head) {
    std::shared_ptr<LinkNode<T>> current(head);
    head = head->next;
  }
}

template <class T> bool DoubleList<T>::IsEmpty() {
  return head == nullptr ? true : false;
}

template <class T> void DoubleList<T>::Delete(T key) {
  auto *index = head;
  if (IsEmpty()) {
    std::cout << "The length of Doublelist is 0;it cannot delete!" << '\n';
    return;
  }
  if (index->data == key) {
    head = nullptr;
    std::shared_ptr<LinkNode<T>> end(index->next);
  } else {
    while (index->next->data != key) {
      index = index->next;
    }
    auto *flag = index->next;
    index->next = flag->next;
    flag->next->pre = index;
    flag->pre = flag->next = nullptr;
    std::shared_ptr<LinkNode<T>> end(flag);
  }
}
int main() {
  DoubleList<int> list;
  list.Push(1);
  list.Delete(1);
  list.Push(2);
  list.Push(3);
  list.Print();
  return 0;
}

/*这是基于c++ 11的语言标准简单写的一个双链表，当然功能并不完善。
与之前的单链表不同的是，不再手动管理内存，但是如你所见，智能指针好像作用不大，毕竟我这个作为一个学习案例。
 用RAII来管理会更好。 但是这个例子呢，没有考虑一些多线程的环境，依旧需要改进。
 本案例使用Clang(版本 19.1.1)和GCC(14.0)在Vscode上面编译通过。
 )和MSVC应该也可以。你可以试着在VS2022编译，当然也推荐godbolt!
 */
