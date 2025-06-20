cmake_minimum_required(VERSION 3.00)

file(GLOB_RECURSE SOURSES "*.cpp")

add_executable(Example ${SOURSES})

target_link_libraries(Example PUBLIC TestTraits gtest)
