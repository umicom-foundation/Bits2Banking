# -----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/compiler-experiments/CMakeLists.txt
#
# PURPOSE:
#   Build educational consumers of the existing Umicom C compiler and runtime.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
# -----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingCompilerExperiments LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(UMICOM_C_SOURCE_DIR "" CACHE PATH "Existing Umicom C source checkout")
if(NOT EXISTS "${UMICOM_C_SOURCE_DIR}/include/umicom_c/umicom_c.h")
    message(FATAL_ERROR "Set UMICOM_C_SOURCE_DIR to the existing Umicom C checkout.")
endif()
# Reuse the production compiler targets; only these educational consumers run here.
set(UMICOM_C_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(UMICOM_C_BUILD_TOOLS OFF CACHE BOOL "" FORCE)
add_subdirectory("${UMICOM_C_SOURCE_DIR}" umicom-c EXCLUDE_FROM_ALL)
include(CTest)
add_executable(btb-compiler-inspect inspect.c)
target_link_libraries(btb-compiler-inspect PRIVATE UmicomC::Compiler)
if(BUILD_TESTING)
    foreach(_case IN ITEMS grammar arithmetic validation)
        add_executable("btb-compiler-${_case}" "test_${_case}.c")
        target_link_libraries("btb-compiler-${_case}" PRIVATE UmicomC::Compiler)
        add_test(NAME "bits2banking.compiler.${_case}" COMMAND "btb-compiler-${_case}")
        set_tests_properties("bits2banking.compiler.${_case}" PROPERTIES TIMEOUT 10)
    endforeach()
endif()

