
# Common
add_library(ne32common
	${NE32_INCLUDE_DIR}/epoc/common.h
	${NE32_INCLUDE_DIR}/epoc/descriptor.h
	common.c
	descriptor.c)

target_include_directories(ne32common PUBLIC ${NE32_INCLUDE_DIR})

add_library(ne32dll_stub
	entry.c)

add_library(ne32exe_stub
	exe.c)

target_link_libraries(ne32dll_stub PUBLIC ne32common)
target_link_libraries(ne32exe_stub PUBLIC ne32common)

# Kern
add_library(ne32kern
	SHARED
	${NE32_INCLUDE_DIR}/epoc/kernel.h
	${NE32_INCLUDE_DIR}/epoc/std.h
	kernel.c
	std.c)

target_include_directories(ne32kern PUBLIC ${NE32_INCLUDE_DIR})
target_link_libraries(ne32kern PRIVATE ne32common)

e32_add_dll(ne32kern 0x80001001 "${NE32_DEFS_DIR}/ne32kern.def")

# Add subdirectories
add_subdirectory(filesystem)