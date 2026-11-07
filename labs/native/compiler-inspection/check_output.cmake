#-----------------------------------------------------------------------------
# Bits2Banking
# File: labs/native/compiler-inspection/check_output.cmake
#
# PURPOSE:
#   Check the complete inspection transcript, explicit execution and rejected arguments.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

if(NOT DEFINED TOOL OR NOT DEFINED CASE)
    message(FATAL_ERROR "TOOL and CASE are required")
endif()
set(args)
set(expected_exit 0)
set(expected "Instructions: 7
Peak stack values: 3
Encoded bytes: 71
")
set(expected_error "")
if(CASE STREQUAL "review")
    string(APPEND expected "Ready for review; no program instructions have been executed.
")
elseif(CASE STREQUAL "execute")
    list(APPEND args --run)
    string(APPEND expected "Result: -14
")
elseif(CASE STREQUAL "usage")
    list(APPEND args --unknown)
    set(expected_exit 2)
    set(expected "")
    set(expected_error "Usage: compiler-inspection [--run]
")
else()
    message(FATAL_ERROR "Unknown inspection case")
endif()
execute_process(COMMAND "${TOOL}" ${args} RESULT_VARIABLE result
    OUTPUT_VARIABLE output ERROR_VARIABLE error TIMEOUT 5)
string(REPLACE "\r\n" "\n" output "${output}")
string(REPLACE "\r\n" "\n" error "${error}")
if(NOT "${result}" STREQUAL "${expected_exit}")
    message(FATAL_ERROR "Inspection exit ${result}; expected ${expected_exit}: ${error}")
endif()
if(NOT "${output}" STREQUAL "${expected}" OR
   NOT "${error}" STREQUAL "${expected_error}")
    message(FATAL_ERROR "Unexpected inspection transcript: stdout=[${output}] stderr=[${error}]")
endif()
