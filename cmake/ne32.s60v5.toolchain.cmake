# Based on wut
cmake_minimum_required(VERSION 3.2)

set (CMAKE_SYSTEM_NAME Android)
set (CMAKE_SYSTEM_VERSION 1)
set (CMAKE_SYSTEM_PROCESSOR arm)
set (CMAKE_CROSSCOMPILING 1)

if (NOT GCC_BIN_PATH)
    find_program(GCC_PATH NAMES arm-none-symbianelf-gcc)
    
    if (NOT GCC_PATH)
        message(FATAL_ERROR "GCC not available")
    else ()            
        get_filename_component(GCC_BIN_PATH ${GCC_PATH} DIRECTORY)
    endif()
endif()

if (WIN32)
    set (CMAKE_C_COMPILER "${GCC_BIN_PATH}/arm-none-symbianelf-gcc.exe" CACHE PATH "" FORCE)
    set (CMAKE_CXX_COMPILER "${GCC_BIN_PATH}/arm-none-symbianelf-g++.exe" CACHE PATH "" FORCE)
else ()
    set (CMAKE_C_COMPILER "${GCC_BIN_PATH}/arm-none-symbianelf-gcc" CACHE PATH "" FORCE)
    set (CMAKE_CXX_COMPILER "${GCC_BIN_PATH}/arm-none-symbianelf-g++" CACHE PATH "" FORCE)
endif()

set (CMAKE_ASM_COMPILER     "${GCC_BIN_PATH}/arm-none-symbianelf-as"   CACHE PATH "" FORCE)
set (CMAKE_LINKER           "${GCC_BIN_PATH}/arm-none-symbianelf-ld"    CACHE PATH "" FORCE)
set (CMAKE_AR               "${GCC_BIN_PATH}/arm-none-symbianelf-ar"    CACHE PATH "" FORCE)
set (CMAKE_STRIP            "${GCC_BIN_PATH}/arm-none-symbianelf-strip" CACHE PATH "" FORCE)

if (NOT NE32_ROOT)
    if (NOT DEFINED ENV{NE32_ROOT})
        message(FATAL_ERROR "NewEpoc32 toolchain root not found!")
    endif()
endif()

set (NE32_ROOT $ENV{NE32_ROOT})

include_directories(BEFORE SYSTEM "${NE32_ROOT}/include")

set (NE32_ELF2E32 "${NE32_ROOT}/bin/elf2e32" CACHE PATH "")
set (NE32_MAKESIS "${NE32_ROOT}/bin/makesis" CACHE PATH "")
set (NE32_LIBPATH "${NE32_ROOT}/lib" CACHE PATH "")

SET_PROPERTY(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

add_definitions(-D__SYMBIAN32__)
add_definitions(-D__EPOC32__)

add_definitions(-D__MARM__)
add_definitions(-D__EABI__)

# S60V5
add_definitions(-D__S60_50__)
add_definitions(-D__MARM_ARMV5__ )
add_definitions(-D__EKA2__)

set (NE32_OS_TARGET "S60V5" CACHE STRING "")