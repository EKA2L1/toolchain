cmake_minimum_required(VERSION 3.2)
include(ExternalProject)

project (NE32)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin")

set (NE32_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

option(NE32_BUILD_TOOLS "Build tools" ON)
option(NE32_BUILD_S60V5_LIBS "Build S60V5 SDK" ON)

if (NE32_BUILD_TOOLS)
   add_subdirectory(tools)
endif()

if (NE32_BUILD_S60V5_LIBS)
    set (NE32_TOOLCHAIN ${CMAKE_CURRENT_SOURCE_DIR}/cmake/ne32.s60v5.toolchain.cmake)

    externalproject_add(libraries
         BINARY_DIR "${CMAKE_BINARY_DIR}/lib"
         SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries"
         CMAKE_GENERATOR "Ninja"
         INSTALL_DIR "${CMAKE_BINARY_DIR}/lib"
         CMAKE_CACHE_ARGS
            -DNE32_ROOT:filepath=${NE32_ROOT}
            -DCMAKE_TOOLCHAIN_FILE:filepath=${NE32_TOOLCHAIN}
            -DCMAKE_INSTALL_PREFIX:string=<INSTALL_DIR>
         BUILD_ALWAYS 1 
         INSTALL_COMMAND "")
endif()

install(DIRECTORY "${CMAKE_SOURCE_DIR}/libraries/include/epoc/"
   DESTINATION "${CMAKE_INSTALL_PREFIX}/include/epoc"
   FILES_MATCHING 
      PATTERN "*.h*")

install(DIRECTORY "${CMAKE_SOURCE_DIR}/cmake/"
   DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake")

install(DIRECTORY "${CMAKE_BINARY_DIR}/lib/"
   DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
   FILES_MATCHING 
      PATTERN "*.a"
      PATTERN "*.def"
      PATTERN "*.lib"
      PATTERN "*.dll")