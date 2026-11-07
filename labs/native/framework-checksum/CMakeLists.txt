# -----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-checksum/CMakeLists.txt
#
# PURPOSE:
#   Build a small Framework consumer and its stream adapter checks.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
# -----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(BtbFrameworkChecksum LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS base)
add_library(btb-checksum-model STATIC checksum.c)
target_include_directories(btb-checksum-model PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(btb-checksum-model PUBLIC Umicom::base)
add_executable(btb-checksum main.c)
target_link_libraries(btb-checksum PRIVATE btb-checksum-model)
set(_targets btb-checksum-model btb-checksum)
if(BUILD_TESTING)
    add_executable(btb-checksum-test test_checksum.c)
    target_link_libraries(btb-checksum-test PRIVATE btb-checksum-model)
    list(APPEND _targets btb-checksum-test)
    add_test(NAME bits2banking.framework_checksum.streams COMMAND btb-checksum-test)
    add_test(NAME bits2banking.framework_checksum.arguments COMMAND btb-checksum)
    set_tests_properties(bits2banking.framework_checksum.arguments PROPERTIES WILL_FAIL TRUE)
    set_tests_properties(bits2banking.framework_checksum.streams
        bits2banking.framework_checksum.arguments PROPERTIES TIMEOUT 10)
endif()
foreach(_target IN LISTS _targets)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${_target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    endif()
endforeach()

