#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: content/labs/native/multikernel-memory-owner/CMakeLists.txt
#
# PURPOSE:
#   Build a C23 exercise for checking ranges against a recorded memory owner.
#
# AUTHOR AND ORGANISATION:
#   Sammy Hegab
#   Umicom Foundation
#
# LICENCE:
#   MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(UmicomMultikernelMemoryOwnerLab LANGUAGES C)
include(CTest)

# This exercise runs on an ordinary host and performs no physical memory access.
add_executable(multikernel-memory-owner main.c)
set_target_properties(multikernel-memory-owner PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(multikernel-memory-owner PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()

# Keep different refusals visible as separate test results.
if(BUILD_TESTING)
    foreach(case inside last-byte starts-at-end crosses-end starts-before wrong-owner empty wrapped-request wrapped-authority)
        add_test(NAME "multikernel.memory-owner.${case}" COMMAND multikernel-memory-owner "${case}")
        set_tests_properties("multikernel.memory-owner.${case}" PROPERTIES TIMEOUT 10 LABELS "education;multikernel")
    endforeach()
endif()
