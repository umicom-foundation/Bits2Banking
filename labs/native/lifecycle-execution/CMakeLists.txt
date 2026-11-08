#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/lifecycle-execution/CMakeLists.txt
#
# PURPOSE:
#   Build the installed-SDK lifecycle exercise and register five controlled scenarios.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25)
project(LifecycleExecutionLab LANGUAGES C)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS developer)
add_executable(lifecycle-execution main.c)
target_link_libraries(lifecycle-execution PRIVATE Umicom::developer)
set_target_properties(lifecycle-execution PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(lifecycle-execution PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
include(CTest)
if(BUILD_TESTING)
    foreach(case preview complete fail-build missing-backend missing-message)
        add_test(NAME "lifecycle-execution.${case}" COMMAND lifecycle-execution "${case}")
        set_tests_properties("lifecycle-execution.${case}" PROPERTIES TIMEOUT 20
            PASS_REGULAR_EXPRESSION "scenario=${case} .*external-commands=0")
    endforeach()
endif()
