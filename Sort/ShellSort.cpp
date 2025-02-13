#include <chrono>
#include <cstddef>
#include <iostream>
#include <random>
#include <utility>
#include <vector>


void ShellSort(std::vector<int> &arr, size_t step) {
  size_t length = arr.size();
  size_t temp{};
  size_t index{};
  if (step == 0) {
    return;
  }
  while (index < length / 2) {
    while (index + step <= length) {
      if (arr[index] > arr[index + step]) {
        std::swap(arr[index], arr[index + step]);
      }
      index += step;
    }
    index = ++temp;
  }
  ShellSort(arr, step - 1);
}

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

[[deprecated("change the datasize")]]
void Print(std::vector<int> &arr) {
  for (auto &it : arr) {
    std::cout << it << ' ';
  }
  std::cout << '\n';
}

int main() {
  const int datasize = 10000;   // 数据数量 一万数据
  const int dataRange = 10000; // 数据范围 1~10000
  std::vector<int> testdata = generateRandomData(datasize, dataRange);
  std::cout << "Sort Begin " << '\n';
  try {
    auto start = std::chrono::high_resolution_clock::now();
    ShellSort(testdata, testdata.size() / 2);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Sort End " << '\n';
    for (auto &it : testdata) {
      std::cout << it << ' ';
    }
    std::cout << "Insert data accout" << datasize << " totally consume time "
              << duration.count() << " millisecond" << std::endl;
  } catch (std::exception &error) {
    std::cerr << "the error is" << error.what() << std::endl;
  }
  return 0;
}