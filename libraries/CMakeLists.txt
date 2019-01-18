cmake_minimum_required(VERSION 3.2)

set (NE32_ROOT "${CMAKE_BINARY_DIR}/.." CACHE STRING "")
set (ENV{NE32_ROOT} ${NE32_ROOT})

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/ne32.s60v5.toolchain.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/ne32.cmake)

project(libraries C)

# Common
add_library(e32common
	include/epoc/common.h
	include/epoc/descriptor.h
	src/common.c
	src/descriptor.c)

target_include_directories(e32common PUBLIC include)

# Kern
add_library(e32kern
	SHARED
	include/epoc/kernel.h
	src/kernel.c)

target_include_directories(e32kern PUBLIC include)
target_link_libraries(e32kern PRIVATE e32common)

e32_add_dll(e32kern 0x80001001 "${CMAKE_CURRENT_SOURCE_DIR}/defs/e32kern.def")