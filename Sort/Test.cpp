#include "Test.h"
#include <chrono>
#include <random>
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