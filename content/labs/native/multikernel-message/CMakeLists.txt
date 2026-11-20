#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: content/labs/native/multikernel-message/CMakeLists.txt
#
# PURPOSE:
#   Build and check a standalone C23 exercise for a copied domain message.
#
# AUTHOR AND ORGANISATION:
#   Sammy Hegab
#   Umicom Foundation
#
# LICENCE:
#   MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(UmicomMultikernelMessageLab LANGUAGES C)
include(CTest)

# This host exercise uses the same byte fixture on each supported compiler.
add_executable(multikernel-message main.c)
set_target_properties(multikernel-message PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(multikernel-message PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()

# Give each validation rule an independent, named outcome in CTest.
if(BUILD_TESTING)
    foreach(case complete wrong-revision stale-peer truncated trailing oversized missing-request)
        add_test(NAME "multikernel.message.${case}" COMMAND multikernel-message "${case}")
        set_tests_properties("multikernel.message.${case}" PROPERTIES TIMEOUT 10 LABELS "education;multikernel")
    endforeach()
endif()
