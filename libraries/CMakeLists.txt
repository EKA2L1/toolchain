cmake_minimum_required(VERSION 3.2)

set (NE32_ROOT "${CMAKE_INSTALL_PREFIX}/.." CACHE STRING "")
set (ENV{NE32_ROOT} ${NE32_ROOT})

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/ne32.s60v5.toolchain.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/ne32.cmake)

project(libraries C)

set (NE32_DEFS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/defs)
set (NE32_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(src)