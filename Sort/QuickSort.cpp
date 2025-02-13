#include <chrono>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

std::vector<int> generateRandomData(int size, int range) {
  std::vector<int> randomNumbers;
  randomNumbers.reserve(size); // 预先分配空间
  // 使用基于时间的种子（如果性能要求高）
  auto seed =
      std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::mt19937 gen(seed);
  std::uniform_int_distribution<> dis(1, range);

  for (int i = 0; i < size; ++i) {
    randomNumbers.push_back(dis(gen));
  }
  return randomNumbers;
}

void QuickSort(std::vector<int> &arr, size_t left, size_t right) {
  auto left_begin = left;
  auto right_end = right;
  auto temp = arr[left];
  if (right == left) {
    return;
  }
  if (right - left == 1) {
    if (arr[left] > arr[right]) {
      std::swap(arr[left], arr[right]);
    }
    return;
  }

  while (left < right) {
    while (arr[right] >= temp && right > left) {
      right--;
    }
    if (right > left) {
      std::swap(arr[left], arr[right]);
    }
    left++;
    while (arr[left] <= temp && left < right) {
      left++;
    }
    if (left < right) {
      std::swap(arr[left], arr[right]);
    }
    right--;
  }
  arr[left] = temp;
  QuickSort(arr, left_begin, left - 1);
  QuickSort(arr, right + 1, right_end - 1);
}
int main() {
  const int datasize = 100;    // 数据数量 一万数据
  const int dataRange = 10000; // 数据范围 1~10000
  std::vector<int> arr{78, 12, 32, 54, 90, 63, 38};
  std::vector<int> testdata = generateRandomData(datasize, dataRange);
  std::cout << "Sort Begin " << '\n';
  auto start = std::chrono::high_resolution_clock::now();
  QuickSort(arr, 0, arr.size() - 1);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = end - start;
  std::cout << "Insert data accout " << datasize << " totally consume time "
            << duration.count() << " millisecond" << std::endl;
  std::cout << "Sort End " << '\n';
  return 0;
}