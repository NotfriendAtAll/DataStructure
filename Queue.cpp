#include <cstddef>
#include <iostream>

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

template <class T, size_t size> void Queue<T, size>::Push(T key) {
  if (IsFull()) {
    std::cout << "Push Error" << '\n';
    return;
  }
  _Queue[topindex++] = key;
}

template <class T, size_t size> bool Queue<T, size>::IsFull() {
  return topindex == size ? true : false;
}

template <class T, size_t size> void Queue<T, size>::Pop() {
  if (topindex == 0) {
    std::cout << "Pop Error" << '\n';
    return;
  }
  auto it = _Queue[0];
  std::cout << "the Pop element is " << it << '\n';
  int falg = 1;
  while (falg < topindex) {
    _Queue[--falg] = _Queue[falg];
    falg += 2;
  }

  _Queue[--topindex]=0;
}
template <class T, size_t size> void Queue<T, size>::Check() {
  if (topindex == 0) {
    std::cout << "skip"<<'\n';
    return;
  }
  auto flag = 0;
  while (flag < topindex ) {
    std::cout << "the Queue exit elements " << _Queue[flag] << '\n';
    flag++;
  }
}

int main() {
  Queue<int, 7> Queue;
  Queue.Push(4);
  Queue.Check();
  Queue.Pop();
  Queue.Push(5);
  Queue.Push(8);
  Queue.Push(7);
  Queue.Pop();
  Queue.Check();
  return 0;
}
