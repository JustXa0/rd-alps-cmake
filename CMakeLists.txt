cmake_minimum_required (VERSION 3.20 FATAL_ERROR)

project ("alps" LANGUAGES CXX CUDA)

find_library (NVAPI_LIBRARY NAMES nvapi64)

find_package (OpenGL REQUIRED)

set(CMAKE_CUDA_STANDARD 14)

add_executable (
    ALPS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Log/logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GPU/deviceDetection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GPU/encoding.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/hello.cu
)

set_target_properties(ALPS PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

target_include_directories (
    ALPS BEFORE PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/spdlog/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/NVIDIA/Video_Codec_SDK_12.1.14/interface/
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/R535-Developer/
    ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}

    # User-made headers
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

target_link_libraries (
    ALPS
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/build/src/Debug/glfw3.lib
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/NVIDIA/Video_Codec_SDK_12.1.14/Lib/x64/nvcuvid.lib
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/NVIDIA/Video_Codec_SDK_12.1.14/Lib/x64/nvencodeapi.lib
    DXGI
    
    ${CUDA_RUNTIME_LIBRARY}
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/R535-Developer/amd64/nvapi64.lib
    OpenGL::GL
    # Link CUDA libraries
    cudart_static
)