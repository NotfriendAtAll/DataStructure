#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

class heap {
public:
  void heap_sort(std::vector<int> &arr);
  void shift(std::vector<int> &arr, int length,int start);

private:
};

void heap::shift(std::vector<int> &arr, int length,int start) {
  int largest = start;
  int left = start * 2 + 1;
  int right = start * 2 + 2;
  if (left < length && arr[start] < arr[left]) {
    largest = left;
  }
  if (right < length && arr[start] < arr[right]) {
    largest = right;
  }
  if (largest != start) {
    std::swap(arr[largest], arr[start]);
    shift(arr,length,largest);
  }
}

void heap::heap_sort(std::vector<int> &arr) {
  int index{};
for(index=arr.size()/2-1;index>=0;index--){
  shift(arr, arr.size(),index);
}
for(int i=arr.size()-1;i>0;i--)
{
  std::swap(arr[i],arr[0]);
  shift(arr,i, 0);
}
}


void Print(std::vector<int> &arr) {
  for (auto &it : arr) {
    std::cout << it << ' ';
  }
  std::cout << '\n';
}
int main() { 
  std::vector<int>test{19,5,57,1};
  Print(test);
  heap heap;
  heap.heap_sort(test);
  Print(test);
  return 0; }