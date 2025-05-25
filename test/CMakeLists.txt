cmake_minimum_required(VERSION 3.30)
project(AVLTest)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# 添加测试文件和主 AVL 实现文件
add_executable(AVLTest example.cpp )
target_include_directories(AVLTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
