
add_library(ne32fs
	SHARED
	${NE32_INCLUDE_DIR}/epoc/filesystem/filesystem.h
	filesystem.c)

target_include_directories(ne32fs PUBLIC ${NE32_INCLUDE_DIR})
target_link_libraries(ne32fs PRIVATE ne32kern ne32common)

e32_add_dll(ne32fs 0x80001002 "${NE32_DEFS_DIR}/ne32fs.def")
