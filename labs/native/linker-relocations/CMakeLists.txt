#-----------------------------------------------------------------------------
# Bits2Banking learning laboratory
# File: labs/native/linker-relocations/CMakeLists.txt
# PURPOSE: Build a public C23 API and ABI-matched Assembly implementation.
# AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
# LICENCE: MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingLinkerRelocations LANGUAGES C ASM)
include(CTest)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(_assembly_source "")
if(CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|AMD64|amd64)$" AND NOT APPLE)
    set(_assembly_source "asm/add_x86_64.S")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(riscv64|riscv64gc)$")
    set(_assembly_source "asm/add_riscv64.S")
else()
    message(STATUS "No matching Assembly ABI lesson. Use portable C fallback.")
    set(_assembly_source "src/add_portable.c")
endif()
add_library(btb_course_totals STATIC src/course_totals.c "${_assembly_source}")
target_include_directories(btb_course_totals PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>")

add_executable(btb-linker-relocations src/main.c)
target_link_libraries(btb-linker-relocations PRIVATE btb_course_totals)

if(NOT MSVC)
    foreach(target IN ITEMS btb_course_totals btb-linker-relocations)
        target_compile_options(${target} PRIVATE
            $<$<COMPILE_LANGUAGE:C>:-Wall;-Wextra;-Wpedantic;-Wconversion;-Wshadow>)
    endforeach()
endif()

if(BUILD_TESTING)
    add_executable(btb-linker-relocations-test tests/test_course_totals.c)
    target_link_libraries(btb-linker-relocations-test PRIVATE btb_course_totals)
    if(NOT MSVC)
        target_compile_options(btb-linker-relocations-test PRIVATE
            -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    endif()
    add_test(NAME bits2banking.linker.relocations COMMAND btb-linker-relocations-test)
    add_test(NAME bits2banking.linker.demo COMMAND btb-linker-relocations)
    set_tests_properties(bits2banking.linker.demo PROPERTIES
        PASS_REGULAR_EXPRESSION "Bits2Banking learning path: 21 lessons")
endif()
install(TARGETS btb_course_totals btb-linker-relocations
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin)
install(FILES include/btb/course_totals.h DESTINATION include/btb)
