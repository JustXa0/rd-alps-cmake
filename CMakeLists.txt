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
# set(CMAKE_Win32_COMPILER PRIVATE "G:/Visual Studio Community 2022/VC/Tools/MSVC/14.36.32532/bin/Hostx64/x86/cl.exe")

# Set compiler files
if (WIN32)
	add_definitions(-DUNICODE -D_UNICODE)
endif()

# Include Nvidia headers
# target_include_directories(alps PRIVATE ${CMAKE_SOURCE_DIR}/lib/Nvidia/Interface)


# Add Text sources
set(TEXT "src/Text/textWriter.cpp" "src/headers/Text/textWriter.h")

# Add Monitor sources
set(MONITOR "src/Monitor/monitorInfoManager.cpp" "src/headers/Monitor/monitorInfoManager.h" "src/Monitor/monitorSelection.cpp" "src/headers/Monitor/monitorSelection.h")

# Add Number sources
set(NUMBER "src/Number/integerWriter.cpp" "src/headers/Number/integerWriter.h")

# Add Device Sources
set(DEVICE "src/Device/deviceIDGenerator.cpp" "src/headers/Device/deviceIDGenerator.h")

# Add Console Sources
set(CONSOLE "src/Console/console.cpp" "src/headers/Console/console.h")

# Add Capture Sources
# set(CAPTURE "src/Capture/screenCapture.cpp" "src/headers/Capture/screenCapture.h")

# set_target_properties(${CAPTURE} PROPERTIES CUDA_SEPARABLE_COMPILATION ON CUDA_STANDARD 12 CUDA_STANDARD_REQUIRED ON CUDA_EXTENSIONS OFF)

# Add source to this project's executable.
add_executable (alps WIN32 ${CAPTURE} ${CONSOLE} ${DEVICE} ${NUMBER} ${MONITOR} ${TEXT} "src/rd-alps.cpp" "src/rd-alps.rc" "src/rd-alps.ico" "src/small.ico" "src/startup.cpp" "src/startup.h")

target_include_directories (alps PRIVATE ${CMAKE_SOURCE_DIR}/src/headers/Text ${CMAKE_SOURCE_DIR}/src/headers/Capture ${CMAKE_SOURCE_DIR}/src/headers/Encyption ${CMAKE_SOURCE_DIR}/src/headers/Monitor ${CMAKE_SOURCE_DIR}/src/headers/Number ${CMAKE_SOURCE_DIR}/src/headers/Device ${CMAKE_SOURCE_DIR}/src/headers/Console ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/lib/ffmpeg/include/libavcodec ${CMAKE_SOURCE_DIR}/lib/ffmpeg/include/libavdevice ${CMAKE_SOURCE_DIR}/lib/ffmpeg/include/libavfilter ${CMAKE_SOURCE_DIR}/lib/ffmpeg/include/libavformat ${CMAKE_SOURCE_DIR}/lib/ffmpeg/include/libavutil ${CMAKE_SOURCE_DIR}/lib/ffmpeg/include/libswresample ${CMAKE_SOURCE_DIR}/lib/ffmpeg/include/libswscale) 
# target_link_directories (alps PRIVATE "C:/Program Files (x86)/Windows Kits/10/Include/(WindowsSDKVersion)")

target_sources(alps PRIVATE "src/rd-alps.rc")

set_source_files_properties("src/rd-alps.rc" PROPERTIES WIN32_EXECUTABLE TRUE)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET alps PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
