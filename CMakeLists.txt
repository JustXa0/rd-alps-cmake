# CMakeList.txt : CMake project for Project ALPS CMake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Project ALPS CMake" VERSION 0.0.1 LANGUAGES CXX C DESCRIPTION "My Project Description")

# Set the path to the Win32 compiler (cl.exe)
set(CMAKE_Win32_COMPILER PRIVATE "G:/Visual Studio Community 2022/VC/Tools/MSVC/14.36.32532/bin/Hostx64/x86/cl.exe")

# Set compiler files
if (WIN32)
	add_definitions(-DUNICODE -D_UNICODE)
endif()

project ("Project ALPS CMake")


# Add source to this project's executable.
add_executable (CMakeTarget WIN32 "src/rd-alps.cpp" "src/Text/textWriter.cpp" "src/Monitor/monitorInfoManager.cpp" "src/Capture/screenCapture.cpp" "src/Number/integerWriter.cpp" "src/Device/deviceIDGenerator.cpp" "src/Monitor/monitorSelection.cpp" "src/Device/deviceIDGenerator.cpp" "src/rd-alps.rc" "src/rd-alps.ico" "src/small.ico" "src/startup.cpp" "src/Console/console.cpp")

# Find ffmpeg libraries and header files in local workspace
find_path(FFMPEG_INCLUDE_DIRS libavcodec/avcodec.h PATHS ${CMAKE_SOURCE_DIR}/lib/ffmpeg/include)
find_library(FFMPEG_LIBRARIES avcodec avformat avutil swscale PATHS ${CMAKE_SOURCE_DIR}/lib/ffmkpeg/debug/lib)

# Check if FFMPEG was found
# if(NOT FFMPEG_INCLUDE_DIRS OR NOT FFMPEG_LIBRARIES)
#    message(FATAL_ERROR "FFMPEG library not found. Make sure you have placed the ffmpeg headers and libraries in the correct location.")
# endif()

target_include_directories (CMakeTarget PRIVATE ${CMAKE_SOURCE_DIR}/src/headers/Text ${CMAKE_SOURCE_DIR}/src/headers/Capture ${CMAKE_SOURCE_DIR}/src/headers/Encyption ${CMAKE_SOURCE_DIR}/src/headers/Monitor ${CMAKE_SOURCE_DIR}/src/headers/Number ${CMAKE_SOURCE_DIR}/src/headers/Device ${CMAKE_SOURCE_DIR}/src/headers/Console ${CMAKE_SOURCE_DIR}/src ${FFMPEG_INCLUDE_DIRS})
target_link_directories (CMakeTarget PRIVATE "C:/Program Files (x86)/Windows Kits/10/Include/(WindowsSDKVersion)")

target_sources(CMakeTarget PRIVATE "src/rd-alps.rc")

set_source_files_properties("src/rd-alps.rc" PROPERTIES WIN32_EXECUTABLE TRUE)

set_target_properties(CMakeTarget PROPERTIES OUTPUT_NAME "Project ALPS")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
