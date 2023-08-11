cmake_minimum_required (VERSION 3.26)

project ("alps" LANGUAGES CXX)

add_executable (
    ALPS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_include_directories (
    ALPS PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/spdlog/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/include
)

target_link_libraries (
    ALPS PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/build/src/Debug/glfw3.lib
)
