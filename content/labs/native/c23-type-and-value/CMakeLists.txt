#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: content/labs/native/c23-type-and-value/CMakeLists.txt
#
# PURPOSE:
#   Build and test the C23 examples with a hosted compiler and an optional Umicom C interpreter.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.24)
project(UmicomBitsC23TypeAndValue LANGUAGES C)
include(CTest)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(UMICOM_LESSON_INTERPRETER "" CACHE FILEPATH "Optional local Umicom C interpreter for the two scalar examples")

# Keep each source independently runnable so learners can practice one rule.
foreach(example IN ITEMS empty_scalar empty_record named_type expression_type bit_width)
    add_executable("btb-c23-${example}" "${example}.c")
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options("btb-c23-${example}" PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
    if(BUILD_TESTING)
        add_test(NAME "btb.education.c23.${example}" COMMAND "btb-c23-${example}")
    endif()
endforeach()

# Verify the qualifier diagnosis without producing an executable for the
# deliberately invalid teaching branch.
if(BUILD_TESTING AND CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    add_test(NAME btb.education.c23.const_assignment
        COMMAND "${CMAKE_COMMAND}" "-Dcompiler=${CMAKE_C_COMPILER}"
            "-Dsource=${CMAKE_CURRENT_SOURCE_DIR}/const_assignment.c"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/check_const_assignment.cmake")
endif()

# Use only a caller-selected built interpreter. The other examples require
# hosted C23 capabilities outside the checked scalar interpreter.
if(BUILD_TESTING AND UMICOM_LESSON_INTERPRETER)
    foreach(example IN ITEMS empty_scalar named_type)
        add_test(NAME "btb.education.c23.interpret.${example}"
            COMMAND "${CMAKE_COMMAND}" "-Dinterpreter=${UMICOM_LESSON_INTERPRETER}"
                "-Dsource=${CMAKE_CURRENT_SOURCE_DIR}/${example}.c"
                -P "${CMAKE_CURRENT_SOURCE_DIR}/check_interpreter.cmake")
    endforeach()
endif()
