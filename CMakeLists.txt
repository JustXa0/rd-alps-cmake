# temp.txt : CMake project for ALPS CMake, include source and define 
# project specific logic here.
#

cmake_minimum_required (VERSION 3.12)

set (CMAKE_CUDA_ARCHITECTURES "80;86;67")

project ("Project ALPS" LANGUAGES CXX C)

# Set compiler files
if (WIN32)
    add_definitions (-DUNICODE -D_UNICODE)
endif ()

# Add Text sources
add_library (TEXT          
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/Text/textWriter.cpp
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/Text/textWriter.h
            )

# Add Monitor sources
add_library (MONITOR    
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/Monitor/monitorInfoManager.cpp
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/Monitor/monitorInfoManager.h
            )

# Add Number sources
add_library (NUMBER     
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/Number/integerWriter.cpp
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/Number/integerWriter.h
)

# Add Device sources
add_library (DEVICE     
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/Device/deviceIDGenerator.cpp
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/Device/deviceIDGenerator.h
)

# Add Console sources
add_library (CONSOLE    
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/Console/console.cpp
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/Console/console.h
)

# Add Capture sources
add_library (CAPTURE    
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/Capture/screenCapture.cpp
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/Capture/screenCapture.h
)

# Set libraries to compile with C++20
# Public means that anything linking to libraries will be compiled with C++20
set_target_properties (TEXT PROPERTIES CXX_STANDARD 20)
set_target_properties (MONITOR PROPERTIES CXX_STANDARD 20)
set_target_properties (NUMBER PROPERTIES CXX_STANDARD 20)
set_target_properties (DEVICE PROPERTIES CXX_STANDARD 20)
set_target_properties (CONSOLE PROPERTIES CXX_STANDARD 20)
set_target_properties (CAPTURE PROPERTIES CXX_STANDARD 20)

# Set all CUDA files so that they compile separately from other C++ files
set_target_properties (CAPTURE PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

# Add main sources to project's executable
add_executable (alps WIN32 
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/rd-alps.cpp 
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/rd-alps.rc 
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/rd-alps.ico
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/small.ico
                )

# Link libraries to executable
target_link_libraries (alps PRIVATE TEXT MONITOR NUMBER DEVICE CONSOLE CAPTURE)

# Include User-made headers
target_include_directories (alps BEFORE PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/Text ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/Capture ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/Encyption ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/Monitor ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/Number ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/Device ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/Console ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Include Nvidia headers
target_include_directories(alps BEFORE PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/Nvidia/Interface/)

# Link Nvidia libraries
target_link_libraries (alps PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/Nvidia/Lib/nvcuvid.lib ${CMAKE_CURRENT_SOURCE_DIR}/lib/Nvidia/Lib/nvencodeapi.lib)

target_sources (alps PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/rd-alps.rc)

set_source_files_properties (${CMAKE_CURRENT_SOURCE_DIR}/src/rd-alps.rc PROPERITES WIN32_EXECUTABLE TRUE)


if (CMAKE_VERSION VERSION_GREATER 3.8)
    set_property (TARGET alps PROPERTY CXX_STANDARD 20)
endif ()

# TODO: Add test and install targets if needed