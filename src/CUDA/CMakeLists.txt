# CMakeLists.txt : Project logic for building all CUDA source files
#

cmake_minimum_required (VERSION 3.12)

set (CMAKE_CUDA_ARCHITECTURES "80;86;87")

set_directory_properties (PROPERTIES CUDA_STANDARD 12.2)

# Start of library building
add_library (
    STARTUP SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/Startup/startup.cu
)

include_directories (
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include/CUDA/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/Nvidia/Interface/
)

target_link_libraries (
    STARTUP
    ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/Nvidia/Lib/nvcuvid.lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/Nvidia/Lib/nvencodeapi.lib
    ${CUDA_LIBRARIES}
)



