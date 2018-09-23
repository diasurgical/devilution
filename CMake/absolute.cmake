set(ORIGINAL_EXE "${CMAKE_SOURCE_DIR}/Diablo.exe")

if(EXISTS "${ORIGINAL_EXE}")
    message(STATUS "Using EXE at ${ORIGINAL_EXE}")

    file(MD5 ${ORIGINAL_EXE} MD5SUM)
    if(NOT MD5SUM STREQUAL "da62d5cd8bd71a0b66e6d4ef7a111233")
        message(FATAL_ERROR "MD5 of EXE is not correct (${MD5SUM})")
    endif()

    find_program(ASM NAMES nasm yasm)

    set(HARNESS_OBJECT "${CMAKE_BINARY_DIR}/harness.o")
    set(HARNESS_ASM "${CMAKE_SOURCE_DIR}/Absolute/harness.asm")

    add_library(harness OBJECT ${HARNESS_OBJECT})
    target_compile_options(harness PUBLIC -no-pie)
    target_compile_definitions(harness INTERFACE -DNO_GLOBALS)
    # For some reason, HARNESS_OBJECT needs to be added here even though it's in the sources above
    target_link_libraries(harness INTERFACE
        ${HARNESS_OBJECT}
        -L${CMAKE_SOURCE_DIR}/Absolute -Tdefault.ld
    )

    add_custom_command(
            COMMENT Assembling
            OUTPUT ${HARNESS_OBJECT}
            MAIN_DEPENDENCY ${HARNESS_ASM}
            COMMAND ${ASM}
            -f elf -DEXE=\\"${ORIGINAL_EXE}\\"
            -o ${HARNESS_OBJECT}
            ${HARNESS_ASM}
    )
else()
    message(STATUS "Original .exe not found at ${ORIGINAL_EXE}")
endif()
