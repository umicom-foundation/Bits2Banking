#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: content/labs/native/c23-type-and-value/check_const_assignment.cmake
#
# PURPOSE:
#   Require a real qualifier diagnostic for the optional invalid branch.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.24)
# Status alone could also mean a missing tool. Require the expected named
# object and a qualifier diagnostic before crediting the exercise.
execute_process(COMMAND "${compiler}" -std=c23 -pedantic-errors -fsyntax-only
    "${source}"
    RESULT_VARIABLE status ERROR_VARIABLE diagnostic)
if(NOT status EQUAL 1 OR NOT diagnostic MATCHES "original" OR
   NOT diagnostic MATCHES "read-only|const-qualified")
    message(FATAL_ERROR "Expected refusal to assign to original: ${status}
${diagnostic}")
endif()
