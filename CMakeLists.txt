cmake_minimum_required(VERSION 3.00)

project(TestTraits VERSION 2.2.8 LANGUAGES CXX)

add_subdirectory(./googletest)
add_subdirectory(./TestTraits)
add_subdirectory(./example)

list(APPEND subTargets 
Example
)

foreach(target IN LISTS subTargets)

set_target_properties(${target}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/install-root/${target}/lib/static
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/install-root/${target}/lib/dynamic
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/install-root/${target}/
)

endforeach()