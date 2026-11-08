#-----------------------------------------------------------------------------
# Bits2Banking
# File: labs/native/framework-deployment/check.cmake
#
# PURPOSE:
#   Check concrete lifecycle output without mistaking a modeled success for deployment evidence.
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
set(expected "")
if(CASE STREQUAL "complete")
    set(expected "Model state: Succeeded")
elseif(CASE STREQUAL "fail")
    set(expected "Model state: Failed")
elseif(CASE STREQUAL "rollback")
    set(expected "Model state: Rolled back")
elseif(CASE STREQUAL "cancel")
    set(expected "Model state: Cancelled")
elseif(CASE STREQUAL "revise")
    set(expected "Approval after edit: 0")
else()
    message(FATAL_ERROR "Unknown scenario")
endif()
execute_process(COMMAND "${TOOL}" "${CASE}" RESULT_VARIABLE result OUTPUT_VARIABLE output ERROR_VARIABLE error TIMEOUT 10)
if(NOT result EQUAL 0)
    message(FATAL_ERROR "Model check failed: ${result} ${output} ${error}")
endif()
string(FIND "${output}" "${expected}" found)
if(found EQUAL -1)
    message(FATAL_ERROR "Missing ${expected}: ${output}")
endif()
if(CASE STREQUAL "complete" OR CASE STREQUAL "rollback" OR CASE STREQUAL "cancel")
    string(FIND "${output}" "Progress: 10000/10000" complete)
    if(complete EQUAL -1)
        message(FATAL_ERROR "Terminal phase was not fully accounted: ${output}")
    endif()
endif()
if(CASE STREQUAL "fail")
    string(FIND "${output}" "Last exit: 7" failed)
    if(failed EQUAL -1)
        message(FATAL_ERROR "Controlled failure identity was lost: ${output}")
    endif()
endif()
