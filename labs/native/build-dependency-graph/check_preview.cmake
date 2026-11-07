#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/build-dependency-graph/check_preview.cmake
#
# PURPOSE:
#   Check the visible preview result for both configured heading modes.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
if(NOT DEFINED PROGRAM OR NOT DEFINED SHOW_HEADING)
    message(FATAL_ERROR "PROGRAM and SHOW_HEADING are required")
endif()
execute_process(COMMAND "${PROGRAM}" RESULT_VARIABLE result OUTPUT_VARIABLE actual
    ERROR_VARIABLE diagnostic TIMEOUT 5)
if(NOT result STREQUAL "0")
    message(FATAL_ERROR "Preview failed (${result}): ${diagnostic}")
endif()
string(REPLACE "\r\n" "\n" actual "${actual}")
set(expected "Trace a build dependency\n")
if(SHOW_HEADING)
    string(PREPEND expected "Umicom Notes preview\n")
endif()
if(NOT actual STREQUAL expected)
    message(FATAL_ERROR "Unexpected preview output. Expected [${expected}] but read [${actual}]")
endif()
