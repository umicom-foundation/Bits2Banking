#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/framework/studio-build-evidence/check_status32.cmake
#
# PURPOSE:
#   Check exact native status views and refusals without a debugger.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25)
# Identical output is required from each supported spelling. A rejected input
# has no numeric report, and the exact exit distinguishes refusal from failure.
execute_process(COMMAND "${LAB_EXECUTABLE}" "${WORD}"
    RESULT_VARIABLE status OUTPUT_VARIABLE output ERROR_VARIABLE error)
if(EXPECT_VALID)
    if(NOT status STREQUAL "0" OR NOT output STREQUAL "${REPORT}\n" OR NOT error STREQUAL "")
        message(FATAL_ERROR "Expected the exact non-error status report.")
    endif()
elseif(NOT status STREQUAL "3" OR NOT output STREQUAL "" OR NOT error STREQUAL "invalid 32-bit status\n")
    message(FATAL_ERROR "Expected exact refusal before writing a numeric report.")
endif()
