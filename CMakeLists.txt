cmake_minimum_required (VERSION 3.20 FATAL_ERROR)

project ("alps" LANGUAGES CUDA CXX C)

find_library (NVAPI_LIBRARY NAMES nvapi64)

find_package (OpenGL REQUIRED)
find_package (CUDAToolkit REQUIRED)

if (WIN32)
    add_definitions (-DUNICODE -D_UNICODE)
endif ()

if (WIN32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        Set(CUVID_LIB ${CMAKE_CURRENT_SOURCE_DIR}/lib/NVIDIA/Video_Codec_SDK_12.1.14/Lib/x64/nvcuvid.lib)
        set(NVENCODEAPI_LIB ${CMAKE_CURRENT_SOURCE_DIR}/lib/NVIDIA/Video_Codec_SDK_12.1.14/Lib/x64/nvencodeapi.lib)
    else()
        Set(CUVID_LIB ${CMAKE_CURRENT_SOURCE_DIR}/lib/NVIDIA/Video_Codec_SDK_12.1.14/Lib/Win32/nvcuvid.lib)
        set(NVENCODEAPI_LIB ${CMAKE_CURRENT_SOURCE_DIR}/lib/NVIDIA/Video_Codec_SDK_12.1.14/Lib/Win32/nvencodeapi.lib)
    endif()
else()
    find_library(CUVID_LIB nvcuvid)
    find_library(NVENCODEAPI_LIB nvidia-encode)
endif()

set(CMAKE_CUDA_STANDARD 14)

add_executable (
    ALPS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Log/logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GPU/deviceDetection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GPU/encoding.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Load/loadLibrary.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/hello.cu
)

set_target_properties(ALPS PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
#target_compile_options(ALPS PRIVATE "/MT")

target_include_directories (
    ALPS BEFORE PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/spdlog/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/NVIDIA/Video_Codec_SDK_12.1.14/interface/
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/R535-Developer/
    ${CUDA_INCLUDE_DIRS}

    # User-made headers
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

target_link_libraries (
    ALPS
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/build/src/Debug/glfw3.lib
    CUDA::cudart
    CUDA::cuda_driver
    ${CUVID_LIB}
    ${NVENCODEAPI_LIB}
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/R535-Developer/amd64/nvapi64.lib
    OpenGL::GL
    DXGI
)

