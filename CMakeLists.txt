# CMakeList.txt : CMake project for Project ALPS, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)


# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Set compiler files
if (WIN32)
  add_definitions (-DUNICODE -D_UNICODE)
endif ()

# set (CMAKE_CUDA_ARCHITECTURES "80;86;87")

project ("ALPS" LANGUAGES C CXX)

# Add C++ source files
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/src/C++/)

# Add CUDA source files
# add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/src/CUDA)

add_executable (
  ALPS WIN32
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rd-alps.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rd-alps.rc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/rd-alps.ico
  ${CMAKE_CURRENT_SOURCE_DIR}/src/small.ico
  ${CMAKE_CURRENT_SOURCE_DIR}/src/startup.cpp
)

# Include user-made headers
target_include_directories (ALPS BEFORE PRIVATE 
  ${CMAKE_CURRENT_SOURCE_DIR}/include/Capture
  ${CMAKE_CURRENT_SOURCE_DIR}/include/Console
  ${CMAKE_CURRENT_SOURCE_DIR}/include/Number
  ${CMAKE_CURRENT_SOURCE_DIR}/include/Device
  ${CMAKE_CURRENT_SOURCE_DIR}/include/Monitor
  ${CMAKE_CURRENT_SOURCE_DIR}/include/Text
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources (ALPS PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/rd-alps.rc)

set_source_files_properties (${CMAKE_CURRENT_SOURCE_DIR}/src/rc-alps.rc PROPERTIES WIN32_EXECUTABLE TRUE)