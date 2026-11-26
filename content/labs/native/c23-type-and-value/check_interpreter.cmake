#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: content/labs/native/c23-type-and-value/check_interpreter.cmake
#
# PURPOSE:
#   Require both the interpreter exit status and the expected program result.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.24)
# A success-looking line alone would not prove that the interpreter finished
# its work. Require success status and a clean diagnostic stream as well.
execute_process(COMMAND "${interpreter}" interpret "${source}"
    RESULT_VARIABLE status OUTPUT_VARIABLE text ERROR_VARIABLE diagnostic)
string(REPLACE "\r\n" "\n" text "${text}")
if(NOT status EQUAL 0 OR NOT diagnostic STREQUAL "" OR
   NOT text MATCHES "(^|\n)Result: 0\nInstructions: [1-9][0-9]*\n?$")
    message(FATAL_ERROR "Expected a completed interpreter result of zero: ${status}\n${text}${diagnostic}")
endif()
