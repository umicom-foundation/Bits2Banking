#-----------------------------------------------------------------------------
# Bits2Banking
# File: labs/native/framework-task-orchestration/check.cmake
#
# PURPOSE:
#   Check selected closure, parallel admission, retry and stop outcomes from the SDK consumer.
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
if(CASE STREQUAL "selected")
    set(expected "Operation: Succeeded; planned: 2; succeeded: 2; cancelled: 0; retries: 0")
elseif(CASE STREQUAL "stop")
    set(expected "Operation: Cancelled; planned: 4; succeeded: 1; cancelled: 3; retries: 0")
elseif(CASE STREQUAL "retry")
    set(expected "Operation: Succeeded; planned: 4; succeeded: 4; cancelled: 0; retries: 1")
elseif(CASE STREQUAL "parallel" OR CASE STREQUAL "reject")
    set(expected "Operation: Succeeded; planned: 4; succeeded: 4; cancelled: 0; retries: 0")
else()
    message(FATAL_ERROR "Unknown orchestration scenario")
endif()
execute_process(COMMAND "${TOOL}" "${CASE}" RESULT_VARIABLE result OUTPUT_VARIABLE output ERROR_VARIABLE error TIMEOUT 10)
if(NOT result EQUAL 0)
    message(FATAL_ERROR "Orchestration failed: ${result} ${output} ${error}")
endif()
string(FIND "${output}" "${expected}" found)
string(FIND "${output}" "No operating-system process was started by the task model." boundary)
if(found EQUAL -1 OR boundary EQUAL -1)
    message(FATAL_ERROR "Unexpected orchestration result: ${output}")
endif()
if(CASE STREQUAL "parallel")
    string(FIND "${output}" "Two active tasks; parallel limit respected." extra)
elseif(CASE STREQUAL "reject")
    string(FIND "${output}" "Rejected plan; previous operation retained." extra)
else()
    set(extra 0)
endif()
if(extra EQUAL -1)
    message(FATAL_ERROR "Missing scenario-specific observation: ${output}")
endif()
