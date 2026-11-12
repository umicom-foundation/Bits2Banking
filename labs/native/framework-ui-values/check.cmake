#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-ui-values/check.cmake
#
# PURPOSE:
#   Compare complete UI value observations and refused-publication results.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

if(NOT DEFINED TOOL OR NOT DEFINED SCENARIO)
    message(FATAL_ERROR "TOOL and SCENARIO are required")
endif()
if(SCENARIO STREQUAL "alias")
    set(expected "Title: Umicom\n")
elseif(SCENARIO STREQUAL "refused-title")
    set(expected "Status: CAPACITY_EXCEEDED\nPrevious integer: 42\n")
elseif(SCENARIO STREQUAL "publish")
    set(expected "Caller title: Caller changed\nStored title: Accepted title\nProperties: 1\n")
elseif(SCENARIO STREQUAL "invalid-value")
    set(expected "Status: INVALID_ARGUMENT\nStored title: Accepted title\nProperties: 1\n")
elseif(SCENARIO STREQUAL "revision")
    set(expected "Status: CAPACITY_EXCEEDED\nReadable value: ready\nRevision: 18446744073709551615\n")
elseif(SCENARIO STREQUAL "archive")
    set(expected "Malformed kind: refused before output\nAccepted integer: encoded size available\n")
else()
    message(FATAL_ERROR "Unknown scenario")
endif()
string(APPEND expected "Shared value observations only; no GUI or command execution.\n")
execute_process(COMMAND "${TOOL}" "${SCENARIO}" RESULT_VARIABLE result
    OUTPUT_VARIABLE output ERROR_VARIABLE error ENCODING UTF-8 TIMEOUT 8)
string(REPLACE "\r\n" "\n" output "${output}")
if(NOT result STREQUAL "0" OR NOT output STREQUAL expected OR NOT error STREQUAL "")
    message(FATAL_ERROR "Observation mismatch (exit ${result})\nExpected:\n${expected}\nObserved:\n${output}\n${error}")
endif()
