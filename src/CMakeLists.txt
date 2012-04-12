# setting up cmake
cmake_minimum_required(VERSION 2.6)

if(NOT WIN32)
add_definitions(-std=c++0x)
endif()

# main project name defined
project(safegi)

set(CMAKE_OSX_ARCHITECTURES "x86_64")

# output directories
if(CMAKE_GENERATOR STREQUAL "Unix Makefiles")
    #set(BIN_DIR_SUFFIX mk)
    set(MAKEFILES ON)
    set(CMAKE_VERBOSE_MAKEFILE ${BUILD_VERBOSE})
elseif(CMAKE_GENERATOR STREQUAL "Xcode")
    #set(BIN_DIR_SUFFIX xcode)
    set(XCODE ON)
elseif(CMAKE_GENERATOR STREQUAL "Visual Studio 10 Win64")
	add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(CMAKE_GENERATOR STREQUAL "Unix Makefiles")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin/${BIN_DIR_SUFFIX})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin/${BIN_DIR_SUFFIX})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin/${BIN_DIR_SUFFIX})

#include directories
include_directories(/usr/local/include)
include_directories(/usr/include)

# libraries
find_package(GLUT)
find_package(OpenGL)

if(WIN32)
    add_definitions(-DNOMINMAX)
endif()

# set default build to release
set(CMAKE_BUILD_TYPE Release)

add_subdirectory(libs/t/safegi/ lib/tsafegi)
add_subdirectory(libs/u/safegi/ lib/usafegi)
add_subdirectory(libs/t/sparser lib/sparser)
add_subdirectory(libs/gi_aux)

add_subdirectory(apps/tgl)
add_subdirectory(apps/tray)
add_subdirectory(apps/ugl)
add_subdirectory(apps/uray)