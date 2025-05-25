#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <cstdlib>
#include "../AVL.h" // 引入 AVL 树的实现

// 全局变量用于跟踪内存分配和释放
size_t allocatedMemory = 0;
size_t freedMemory = 0;

// 自定义内存分配函数
void* operator new(size_t size) {
    allocatedMemory += size;
    return std::malloc(size);
}

// 自定义内存释放函数
void operator delete(void* ptr, size_t size) noexcept {
    freedMemory += size;
    std::free(ptr);
}

// 生成随机整数数据
std::vector<int> generateRandomData(int size, int range) {
    std::vector<int> data(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, range);

    for (int i = 0; i < size; ++i) {
        data[i] = dis(gen);
    }
    return data;
}

void performanceTest() {
    AVLtree<int> avl;

    const int dataSize = 10000; // 数据量
    const int dataRange = 100000; // 数据范围

    // 生成随机数据
    std::vector<int> testData = generateRandomData(dataSize, dataRange);

    // 测量插入性能
    auto start = std::chrono::high_resolution_clock::now();
    for (const auto& value : testData) {
        avl.Insert(avl._root, value);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "Inserted " << dataSize << " random values into AVL Tree in "
              << duration.count() << " ms.\n";

    // 输出内存使用情况
    std::cout << "Memory allocated: " << allocatedMemory << " bytes\n";
    std::cout << "Memory freed: " << freedMemory << " bytes\n";
    std::cout << "Net memory usage: " << (allocatedMemory - freedMemory) << " bytes\n";
}
/*
Memory allocated: 344896 bytes
Memory freed: 0 bytes
Net memory usage: 344896 bytes
*/

int main() {
    std::cout << "=== AVL Tree Performance Test ===\n";
    performanceTest();
    return 0;
}