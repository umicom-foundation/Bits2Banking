# Bits to Banking — Safer C notes lab
# Author: Sammy Hegab | Umicom Foundation | MIT
cmake_minimum_required(VERSION 3.24)
project(BitsSafeNotes LANGUAGES C)
include(CTest)

add_library(bits_safe_notes STATIC notes.c)
set_target_properties(bits_safe_notes PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
target_include_directories(bits_safe_notes PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(bits-notes main.c)
target_link_libraries(bits-notes PRIVATE bits_safe_notes)
if(BUILD_TESTING)
    add_executable(bits-notes-test test_notes.c)
    target_link_libraries(bits-notes-test PRIVATE bits_safe_notes)
    add_test(NAME bits.notes.safe_updates COMMAND bits-notes-test)
endif()

foreach(target IN ITEMS bits_safe_notes bits-notes)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    endif()
endforeach()
