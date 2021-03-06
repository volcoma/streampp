﻿cmake_minimum_required(VERSION 3.4.3)

project(streampp)
include(CTest)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/utility")

option(BUILD_STREAMPP_SHARED "Build as a shared library." ON)
option(BUILD_STREAMPP_TESTS "Build the tests" ON)
option(BUILD_STREAMPP_WITH_CODE_STYLE_CHECKS "Build with code style checks." OFF)

if(BUILD_STREAMPP_TESTS)
	if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
	endif()
	if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
	endif()
	if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
	endif()
endif()

if(BUILD_STREAMPP_SHARED)
	set(BUILD_SHARED_LIBS ON)
endif()

if(BUILD_STREAMPP_WITH_CODE_STYLE_CHECKS)
	set(BUILD_WITH_CODE_STYLE_CHECKS ON)
endif()


add_subdirectory(3rdparty)
add_subdirectory(streampp)

if(BUILD_STREAMPP_TESTS)
	add_subdirectory(tests)
endif()
