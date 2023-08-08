cmake_minimum_required(VERSION 3.27)

set(CMAKE_CUDA_ARCHITECTURES "80;86;87")
enable_language(CUDA)

# Start of library building
add_library(STARTUP ${CMAKE_CURRENT_SOURCE_DIR}/Startup/cudaStartup.cu)

target_include_directories(STARTUP PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include/CUDA
    ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/Nvidia/Interface
    ${CUDA_INCLUDE_DIRS}
)

set_directory_properties(PROPERTIES CUDA_STANDARD 12.2)
