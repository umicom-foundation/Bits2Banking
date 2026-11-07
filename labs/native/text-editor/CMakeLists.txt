# -----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/text-editor/CMakeLists.txt
#
# PURPOSE:
#   Build a self-contained teaching lab with boundary checks.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
# -----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(Btbeditor LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)
add_library(btb-editor STATIC editor.c)
target_include_directories(btb-editor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(btb-text-editor main.c)
target_link_libraries(btb-text-editor PRIVATE btb-editor)
set(_targets btb-editor btb-text-editor)
if(BUILD_TESTING)
    add_executable(btb-text-editor-tests test_editor.c)
    target_link_libraries(btb-text-editor-tests PRIVATE btb-editor)
    list(APPEND _targets btb-text-editor-tests)
    add_test(NAME bits2banking.text-editor.boundaries COMMAND btb-text-editor-tests)
    set_tests_properties(bits2banking.text-editor.boundaries PROPERTIES TIMEOUT 10)
endif()
foreach(_target IN LISTS _targets)
    if(MSVC)
        target_compile_options(${_target} PRIVATE /W4)
    else()
        target_compile_options(${_target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    endif()
endforeach()

if(BUILD_TESTING)
    add_test(NAME bits2banking.text-editor.session
        COMMAND "${CMAKE_COMMAND}" "-DPROGRAM=$<TARGET_FILE:btb-text-editor>"
            "-DWORK_ROOT=${CMAKE_CURRENT_BINARY_DIR}/sessions"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/check_session.cmake")
    set_tests_properties(bits2banking.text-editor.session PROPERTIES TIMEOUT 30)
endif()

if(BUILD_TESTING)
    # File fixtures belong in this target's binary tree, not a user's document
    # directory. A separate executable isolates loading from editing checks.
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/load-fixtures")
    add_executable(btb-text-editor-load-tests test_load.c)
    target_link_libraries(btb-text-editor-load-tests PRIVATE btb-editor)
    if(MSVC)
        target_compile_options(btb-text-editor-load-tests PRIVATE /W4)
    else()
        target_compile_options(btb-text-editor-load-tests PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    endif()
    add_test(NAME bits2banking.text-editor.load
        COMMAND btb-text-editor-load-tests "${CMAKE_CURRENT_BINARY_DIR}/load-fixtures")
    set_tests_properties(bits2banking.text-editor.load PROPERTIES TIMEOUT 10)
endif()
