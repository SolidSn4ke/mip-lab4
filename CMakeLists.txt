cmake_minimum_required(VERSION 3.10.0)
project(mip-lab4 VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(mip-lab4  ${SOURCES})
target_include_directories(mip-lab4 PRIVATE src)

find_package(httplib REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(mip-lab4 PRIVATE httplib::httplib nlohmann_json::nlohmann_json)