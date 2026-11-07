# -----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/collections/CMakeLists.txt
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
project(Btbcollections LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)
add_library(btb-collections-model STATIC collections.c)
target_include_directories(btb-collections-model PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(btb-collections main.c)
target_link_libraries(btb-collections PRIVATE btb-collections-model)
set(_targets btb-collections-model btb-collections)
if(BUILD_TESTING)
    add_executable(btb-collections-tests test_collections.c)
    target_link_libraries(btb-collections-tests PRIVATE btb-collections-model)
    list(APPEND _targets btb-collections-tests)
    add_test(NAME bits2banking.collections.boundaries COMMAND btb-collections-tests)
    set_tests_properties(bits2banking.collections.boundaries PROPERTIES TIMEOUT 10)
endif()
foreach(_target IN LISTS _targets)
    if(MSVC)
        target_compile_options(${_target} PRIVATE /W4)
    else()
        target_compile_options(${_target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    endif()
endforeach()

# Workflow drivers reuse the model while exposing the caller's failure policy.
foreach(_workflow queue_pipeline undo_trace search_trace sort_records)
    add_executable(btb-${_workflow} ${_workflow}.c)
    target_link_libraries(btb-${_workflow} PRIVATE btb-collections-model)
    if(MSVC)
        target_compile_options(btb-${_workflow} PRIVATE /W4)
    else()
        target_compile_options(btb-${_workflow} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    endif()
    if(BUILD_TESTING)
        add_test(NAME bits2banking.collections.${_workflow} COMMAND btb-${_workflow})
        set_tests_properties(bits2banking.collections.${_workflow} PROPERTIES TIMEOUT 10)
    endif()
endforeach()
