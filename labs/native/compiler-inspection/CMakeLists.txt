#-----------------------------------------------------------------------------
# Bits2Banking
# File: labs/native/compiler-inspection/CMakeLists.txt
#
# PURPOSE:
#   Build a small hosted consumer of the shared Umicom C inspection API.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.26)
project(CompilerInspectionLesson LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)
set(UMICOM_C_SOURCE "${CMAKE_CURRENT_LIST_DIR}/../../../../umicom-c" CACHE PATH "Umicom C source checkout")
if(NOT EXISTS "${UMICOM_C_SOURCE}/include/umicom_c/umicom_c.h")
    message(FATAL_ERROR "Set UMICOM_C_SOURCE to the Umicom C checkout")
endif()
set(UMICOM_C_BUILD_TOOLS OFF)
set(UMICOM_C_BUILD_TESTS OFF)
add_subdirectory("${UMICOM_C_SOURCE}" "umicom-c" EXCLUDE_FROM_ALL)
add_executable(compiler-inspection main.c)
target_link_libraries(compiler-inspection PRIVATE UmicomC::Compiler)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(compiler-inspection PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
# The earlier substring checks remain for comparison. Exact output and exit
# checks below distinguish review from execution and reject command misuse.
if(FALSE)
if(BUILD_TESTING)
    add_test(NAME bits.compiler-inspection.review COMMAND compiler-inspection)
    set_tests_properties(bits.compiler-inspection.review PROPERTIES
        PASS_REGULAR_EXPRESSION "Ready for review; no program instructions have been executed."
        LABELS "learning;compiler" TIMEOUT 10)
    add_test(NAME bits.compiler-inspection.execute COMMAND compiler-inspection --run)
    set_tests_properties(bits.compiler-inspection.execute PROPERTIES
        PASS_REGULAR_EXPRESSION "Result: -14" LABELS "learning;compiler" TIMEOUT 10)
endif()
endif()
if(BUILD_TESTING)
    # Retain the earlier workflow list; trace now has its own exact transcript.
    # foreach(case IN ITEMS review execute usage)
    # Preserve the former list; the same executable now has a comparison profile.
    # foreach(case IN ITEMS review execute trace usage)
    foreach(case IN ITEMS review execute trace usage comparison-review comparison-execute comparison-trace)
        add_test(NAME bits.compiler-inspection.${case}
            COMMAND "${CMAKE_COMMAND}" "-DTOOL=$<TARGET_FILE:compiler-inspection>"
                "-DCASE=${case}" -P "${CMAKE_CURRENT_SOURCE_DIR}/check_output.cmake")
        set_tests_properties(bits.compiler-inspection.${case} PROPERTIES
            LABELS "learning;compiler" TIMEOUT 10)
    endforeach()
endif()
