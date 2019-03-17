cmake_minimum_required(VERSION 3.2)

macro (e32_add_dll source uid deffile)
    get_target_property(TEMP ${source} LINK_FLAGS)
    if(TEMP STREQUAL "TEMP-NOTFOUND")
        SET(TEMP "") # Set to empty string
    else()
        SET(TEMP "${TEMP} ") # A space to cleanly separate from existing content
    endif()

    if (NE32_OS_TARGET STREQUAL "S60V5")
        message("Compiling ${source} with ARMv5t")
        SET (TEMP "${TEMP} -march=armv5t")
    endif()
    
    if (NE32_OS_TARGET STREQUAL "S60V3")
        message("Compiling ${source} with ARMv5t")
        SET (TEMP "${TEMP} -march=armv5t")
    endif()

    # Append our values
    SET(TEMP "${TEMP} -nostdlib -Wl,--target1-abs,--shared,--default-symver,-Tdata,0x400000,-Ttext,0x8000,--entry,_E32Dll,-u,_E32Dll,-Le32dll_stub")
    set_target_properties(${source} PROPERTIES LINK_FLAGS ${TEMP} )

    message(${TEMP})

    # This was not supposed to include the dlldata.
    add_custom_target(
        ${source}.so
        ALL
        COMMAND "${NE32_ELF2E32}" --elfinput="${CMAKE_CURRENT_BINARY_DIR}/lib${source}.so" 
            --uid1=0x10000079 --uid2=0x10 --uid3=${uid} --sid=${uid} 
            --version=10.0
            --dlldata
            --output="${CMAKE_CURRENT_BINARY_DIR}/${source}.dll" 
            --libpath="${NE32_LIBPATH}\;${CMAKE_CURRENT_BINARY_DIR}\;${CMAKE_CURRENT_BINARY_DIR}\.."
            --definput="${deffile}"
            --defoutput="${CMAKE_CURRENT_BINARY_DIR}/${source}.def"
            --targettype=DLL
            --dso="${CMAKE_CURRENT_BINARY_DIR}/lib${source}.a"
            --linkas="${source}.dll")

    add_dependencies(${source}.so ${source})

    # Copy build files
    # Including E32Images, the SO and the archive
    add_custom_command(TARGET ${source}.so
        POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy
                "${CMAKE_CURRENT_BINARY_DIR}/${source}.dll"
                "${NE32_LIBPATH}/${source}.dll")

    add_custom_command(TARGET ${source}.so
        POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy
                "${CMAKE_CURRENT_BINARY_DIR}/lib${source}.a"
                "${NE32_LIBPATH}/lib${source}.a")
                
    add_custom_command(TARGET ${source}.so
        POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy
                "$<TARGET_FILE:${source}>"
                "${NE32_LIBPATH}/$<TARGET_FILE_NAME:${source}>")
endmacro()