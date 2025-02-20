#include <iostream>
#include <utility>
#include <vector>

void Bubble(std::vector<int> &arr) {
  for (int i = 0; i < arr.size() - 1; i++) {
    for (int j = i; j < arr.size(); j++) {
      if (arr[j] > arr[j + 1]) {
        std::swap(arr[j], arr[j + 1]);
      }
    }
  }
}

void Print(std::vector<int> &arr) {
  for (auto &it : arr) {
    std::cout << it << ' ';
  }
  std::cout << '\n';
}
int main() {
  std::vector<int> test{31, 2, 62, 39, 61};
  Print(test);
  Bubble(test);
  Print(test);
  return 0;
}