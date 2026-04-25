cmake_minimum_required(VERSION 3.10.0)
project(mip-lab4 VERSION 0.1.0 LANGUAGES C CXX)

add_executable(mip-lab4  src/main.cpp)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(mip-lab4 PRIVATE fmt::fmt)