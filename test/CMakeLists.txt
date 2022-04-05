cmake_minimum_required(VERSION 2.8)

project(c++project/test)

find_package(Eigen3 REQUIRED)

add_executable(test test.cpp)
target_link_libraries(test Eigen3::Eigen)