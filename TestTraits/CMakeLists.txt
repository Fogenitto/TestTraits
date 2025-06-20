cmake_minimum_required(VERSION 3.00)

set(LibName TestTraits)

#lib definition
add_library(${LibName} INTERFACE) 

target_include_directories(${LibName} INTERFACE         
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(${LibName} INTERFACE cxx_std_17) 

