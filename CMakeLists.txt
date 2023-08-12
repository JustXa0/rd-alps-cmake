cmake_minimum_required (VERSION 3.20 FATAL_ERROR)

project ("alps" LANGUAGES CXX CUDA)

set(CMAKE_CUDA_STANDARD 14)

add_executable (
    ALPS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/hello.cu
)

set_target_properties(ALPS PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

target_include_directories (
    ALPS PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/spdlog/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/include
)

target_link_libraries (
    ALPS PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/build/src/Debug/glfw3.lib
)
