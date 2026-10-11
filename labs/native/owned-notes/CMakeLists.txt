#-----------------------------------------------------------------------------
# Bits to Banking | Umicom Foundation
# File: labs/native/owned-notes/CMakeLists.txt
# PURPOSE: Build a freestanding Notes-model learning project (no GTK required).
# AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
# LICENCE: MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingOwnedNotes LANGUAGES C)
include(CTest)
option(BTB_ENABLE_SANITIZERS "Use AddressSanitizer and UBSan where supported" OFF)

add_library(btb_owned_notes STATIC notes.c)
add_executable(bits2banking-owned-notes main.c)
add_executable(bits2banking-owned-notes-test test_notes.c)
target_link_libraries(bits2banking-owned-notes PRIVATE btb_owned_notes)
target_link_libraries(bits2banking-owned-notes-test PRIVATE btb_owned_notes)
foreach(target IN ITEMS btb_owned_notes bits2banking-owned-notes bits2banking-owned-notes-test)
    set_target_properties(${target} PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED ON C_EXTENSIONS OFF)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    endif()
    if(BTB_ENABLE_SANITIZERS AND NOT MSVC)
        target_compile_options(${target} PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
        target_link_options(${target} PRIVATE -fsanitize=address,undefined)
    endif()
endforeach()
if(BUILD_TESTING)
    add_test(NAME bits2banking.owned_notes COMMAND bits2banking-owned-notes-test)
    set_tests_properties(bits2banking.owned_notes PROPERTIES LABELS "education;c23;ownership;notes")
endif()
