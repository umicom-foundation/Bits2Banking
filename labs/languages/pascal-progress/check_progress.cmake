# -----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/languages/pascal-progress/check_progress.cmake
#
# PURPOSE:
#   Check successful and rejected Pascal input without reading invalid values.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
# -----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.24)
foreach(_case IN ITEMS 2 5 -1 6 abc "")
    execute_process(COMMAND "${PROGRAM}" "${_case}" RESULT_VARIABLE _result
        OUTPUT_VARIABLE _text ERROR_VARIABLE _error TIMEOUT 5)
    if(_case STREQUAL "2")
        if(NOT _result STREQUAL "0" OR NOT _text MATCHES "Remaining: 3"
            OR NOT _text MATCHES "Practice item 3")
            message(FATAL_ERROR "Valid progress failed: ${_result} ${_text} ${_error}")
        endif()
    elseif(_case STREQUAL "5")
        if(NOT _result STREQUAL "0" OR NOT _text MATCHES "Remaining: 0"
            OR _text MATCHES "Practice item")
            message(FATAL_ERROR "Empty loop failed: ${_result} ${_text}")
        endif()
    elseif(NOT _result STREQUAL "1")
        message(FATAL_ERROR "Expected explicit rejection of '${_case}': ${_result} ${_text}")
    endif()
endforeach()
execute_process(COMMAND "${PROGRAM}" RESULT_VARIABLE _result
    OUTPUT_VARIABLE _text ERROR_VARIABLE _error TIMEOUT 5)
if(NOT _result STREQUAL "1" OR NOT _text MATCHES "Usage: progress")
    message(FATAL_ERROR "Missing argument did not show usage: ${_result} ${_text}")
endif()
