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
elseif(CASE STREQUAL "trace")
    list(APPEND args --trace)
    string(APPEND expected "0 push depth=1 top=2 status=success
1 push depth=2 top=3 status=success
2 push depth=3 top=4 status=success
3 multiply depth=2 top=12 status=success
4 add depth=1 top=14 status=success
5 negate depth=1 top=-14 status=success
6 return depth=1 top=-14 status=success
Result: -14
")
elseif(CASE STREQUAL "comparison-review" OR CASE STREQUAL "comparison-execute" OR CASE STREQUAL "comparison-trace")
    list(APPEND args --comparison)
    set(expected "Instructions: 8\nPeak stack values: 3\nEncoded bytes: 80\n")
    if(CASE STREQUAL "comparison-review")
        string(APPEND expected "Ready for review; no program instructions have been executed.\n")
    elseif(CASE STREQUAL "comparison-execute")
        list(APPEND args --run)
        string(APPEND expected "Result: 1\n")
    else()
        list(APPEND args --trace)
        string(APPEND expected "0 push depth=1 top=2 status=success\n1 push depth=2 top=3 status=success\n2 add depth=1 top=5 status=success\n3 push depth=2 top=2 status=success\n4 push depth=3 top=3 status=success\n5 multiply depth=2 top=6 status=success\n6 less depth=1 top=1 status=success\n7 return depth=1 top=1 status=success\nResult: 1\n")
    endif()
elseif(CASE STREQUAL "usage")
    list(APPEND args --unknown)
    set(expected_exit 2)
    set(expected "")
    # Preserve the former usage text for review; the additive trace mode is now advertised.
    # set(expected_error "Usage: compiler-inspection [--run]\n")
    # Earlier usage retained; the profile precedes the unchanged execution mode.
    # set(expected_error "Usage: compiler-inspection [--run|--trace]\n")
    set(expected_error "Usage: compiler-inspection [--comparison] [--run|--trace]\n")
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
