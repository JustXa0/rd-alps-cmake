cmake_minimum_required (VERSION 3.20 FATAL_ERROR)

project ("alps" LANGUAGES CUDA CXX)

find_library (NVAPI_LIBRARY NAMES nvapi64)

find_package (OpenGL REQUIRED)
find_package (CUDAToolkit REQUIRED)

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

    # User-made headers
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

target_link_libraries (
    ALPS
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/build/src/Debug/glfw3.lib
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/NVIDIA/Video_Codec_SDK_12.1.14/Lib/x64/nvcuvid.lib
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/NVIDIA/Video_Codec_SDK_12.1.14/Lib/x64/nvencodeapi.lib
    CUDA::cudart_static  # Link against CUDA Runtime API
    CUDA::cuda_driver
    #C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v12.2\\lib\\x64\\cudadevrt.lib
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/R535-Developer/amd64/nvapi64.lib
    OpenGL::GL
    DXGI
)

