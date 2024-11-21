cmake_minimum_required(VERSION 3.10)

project(SphereSetApproximation)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")  # enable assert
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS}")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG}")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-int-in-bool-context -Wsign-compare")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS}")
    set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fsanitize=address")
endif()

option(BUILD_PERFORMANCE_TEST "More subdivisition for performance test" OFF)
option(BUILD_OPENMP "Enable support for OpenMP" ON)
option(BUILD_LOG "Enable verbose log" OFF)

# 设置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# 添加头文件目录
include_directories(
  SYSTEM
  include
  include/3rd_party
  ${PROJECT_SOURCE_DIR}/lib
)

# 编译 argparse.c 为目标文件
add_library(argparse OBJECT lib/argparse.c)

if(BUILD_PERFORMANCE_TEST)
    add_definitions(-DPERFORMANCE_TEST)
endif(BUILD_PERFORMANCE_TEST)

if(BUILD_OPENMP)
    add_definitions(-DWITH_OMP)
endif(BUILD_OPENMP)

if(BUILD_LOG)
    add_definitions(-DLOG_OUTPUT)
endif(BUILD_LOG)

set(sphere_set_approximate_SRC
  src/sphere_set_approximate/mesh_test.cpp
  src/sphere_set_approximate/point_in_mesh.cpp
  src/sphere_set_approximate/pointset.cpp
  src/sphere_set_approximate/powell.cpp
  src/sphere_set_approximate/sov.cpp
  src/sphere_set_approximate/sphere_set_approximate.cpp
  src/sphere_set_approximate/sphere.cpp
  src/sphere_set_approximate/visualize.cpp
)

add_library( sphere_set_approximator
  src/sphere_set_approximator.cpp
  src/manifold/BVH.cpp
  src/manifold/Intersection.cpp
  src/manifold/Model_OBJ.cpp
  src/rtcore/aabox.cpp 
  src/rtcore/objmesh.cpp 
  src/math/vecmath.cpp
  ${sphere_set_approximate_SRC}
)
target_link_libraries( sphere_set_approximator
  argparse
) 

add_executable(main
  src/main.cpp
)
target_link_libraries( main
  PRIVATE
  sphere_set_approximator
)