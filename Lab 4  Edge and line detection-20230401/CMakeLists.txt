﻿# CMakeList.txt : CMake project for lab4, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

#project
project ("lab4")

# opencv
find_package(OpenCV REQUIRED)

# include
include_directories(${OpenCV_INCLUDE_DIRS})

# executables & libraries
add_executable(${PROJECT_NAME} src/lab4.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

# check
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET lab4 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
