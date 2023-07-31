# CMakeLists.txt : Project logic for building all C++ source files
#

cmake_minimum_required (VERSION 3.12)

# Set compiler files
if (WIN32)
  add_definitions (-DUNICODE -D_UNICODE)
endif ()

# Start of library building
add_library (
    CONSOLE SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/Console/console.cpp
    )

add_library (
    DEVICE SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/Device/deviceIDGenerator.cpp
    )

add_library (
    MONITOR SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/Monitor/monitorInfoManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Monitor/monitorSelection.cpp
)

add_library (
    NUMBER SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/Number/integerWriter.cpp
)

add_library (
    TEXT SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/Text/textWriter.cpp
)



include_directories (
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include/Capture/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include/Console/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include/Device/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include/Monitor/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include/Number/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include/Text/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include/
    )

set_directory_properties (PROPERTIES CXX_STANDARD 20)