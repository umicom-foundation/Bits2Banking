#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-build-history/check.cmake
#
# PURPOSE:
#   Compare exact operation identities and retained-history observations.
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
set(attempts 1)
set(count 1)
set(first 1)
set(extra "")
if(SCENARIO STREQUAL "rolling")
    set(attempts 3)
    set(count 2)
    set(first 2)
elseif(SCENARIO STREQUAL "shared")
    set(attempts 2)
    set(count 2)
elseif(SCENARIO STREQUAL "no-history")
    set(count 0)
elseif(SCENARIO STREQUAL "invalid")
    set(attempts 0)
    set(count 0)
    set(extra "Invalid call: no admitted operation; caller output unchanged.\n")
elseif(SCENARIO STREQUAL "copy")
    set(extra "Caller reuse: retained observation unchanged.\n")
elseif(NOT SCENARIO STREQUAL "single")
    message(FATAL_ERROR "Unknown scenario")
endif()
set(expected "Scenario: ${SCENARIO}\n")
if(attempts GREATER 0)
    foreach(operation RANGE 1 ${attempts})
        string(APPEND expected "Operation: ${operation}; status: INVALID_STATE; exit: -1\n")
    endforeach()
endif()
string(APPEND expected "${extra}Retained records: ${count}\n")
if(count GREATER 0)
    math(EXPR last "${count} - 1")
    foreach(index RANGE 0 ${last})
        math(EXPR operation "${first} + ${index}")
        string(APPEND expected "History[${index}]: ${operation}\n")
    endforeach()
endif()
string(APPEND expected "Preparation observations only; no compiler, test runner or application launched.\n")
execute_process(COMMAND "${TOOL}" "${SCENARIO}" RESULT_VARIABLE result
    OUTPUT_VARIABLE output ERROR_VARIABLE error ENCODING UTF-8 TIMEOUT 8)
string(REPLACE "\r\n" "\n" output "${output}")
if(NOT result STREQUAL "0" OR NOT output STREQUAL expected OR NOT error STREQUAL "")
    message(FATAL_ERROR "Observation mismatch (exit ${result})\nExpected:\n${expected}\nObserved:\n${output}\n${error}")
endif()
