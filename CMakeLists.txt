cmake_minimum_required(VERSION 3.10)

project(SphereSetApproximation)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)

# 设置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# 添加头文件目录
include_directories(
  .
  include
  ${PROJECT_SOURCE_DIR}/lib
  ${PROJECT_SOURCE_DIR}/math
  ${PROJECT_SOURCE_DIR}/rtcore
)

# 编译 argparse.c 为目标文件
add_library(argparse OBJECT lib/argparse.c)

# 链接库和可执行文件
add_executable(main src/main.cpp rtcore/aabox.cpp math/vecmath.cpp)
target_link_libraries(main argparse) 