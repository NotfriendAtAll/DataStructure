#include <algorithm>
#include <cstddef>
#include <iostream>

template <class T, size_t size> class Stack {
public:
  Stack() : topindex(0) { std::fill(_stack, _stack + size, T()); }
  ~Stack() = default;
  void Push(T key);
  void Pop();
  bool IsFull();

private:
  int topindex;
  T _stack[size];
};

template <class T, size_t size> void Stack<T, size>::Push(T key) {
  if (IsFull()) {
    std::cout << "Push Error" << '\n';
    return;
  }
  _stack[topindex++] = key;
}

template <class T, size_t size> bool Stack<T, size>::IsFull() {
  return topindex == size ? true : false;
}

template <class T, size_t size> void Stack<T, size>::Pop() {
  if (topindex == 0) {
    std::cout << "Pop Error" << '\n';
    return;
  }
  auto it = _stack[--topindex];
  std::cout << "the Pop element is " << it << '\n';
}

int main() {
  Stack<int, 7> stack;
  stack.Push(4);
  stack.Pop();
  stack.Push(5);
  stack.Push(8);
  stack.Push(7);
  stack.Pop();
  return 0;
}
/*当然这个例子还是比较简陋，多线程环境下依旧不能使用。不可否认的是，这个案例cpp又被我写成了shift,毕竟，把c的思想
面向过程和 cpp的思想 面向对象结合起来，感觉四不像
如果你想自己实现更加实用的底层库，请参考c++标准模板库STL的实现。
另外，不分开成.cpp和.h文件，就是懒，放在一起叫.hpp会更合适。本案例，用cland在vscode上面编译通过，同时，clion搭配cmake体验效果更佳。
*/
