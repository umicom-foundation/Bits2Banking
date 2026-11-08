#-----------------------------------------------------------------------------
# Bits2Banking
# File: labs/native/framework-task-graph/check.cmake
#
# PURPOSE:
#   Compare dependency-graph state output from five installed SDK scenarios.
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
if(CASE STREQUAL "complete" OR CASE STREQUAL "retry")
    set(expected "Succeeded: 3; failed: 0; blocked: 0; cancelled: 0")
elseif(CASE STREQUAL "fail")
    set(expected "Succeeded: 0; failed: 1; blocked: 2; cancelled: 0")
elseif(CASE STREQUAL "cancel")
    set(expected "Succeeded: 1; failed: 0; blocked: 0; cancelled: 2")
elseif(CASE STREQUAL "reject")
    set(expected "Rejected replacement; running graph preserved.")
else()
    message(FATAL_ERROR "Unknown graph scenario")
endif()
execute_process(COMMAND "${TOOL}" "${CASE}" RESULT_VARIABLE result OUTPUT_VARIABLE output ERROR_VARIABLE error TIMEOUT 10)
if(NOT result EQUAL 0)
    message(FATAL_ERROR "Graph scenario failed: ${result} ${output} ${error}")
endif()
string(FIND "${output}" "${expected}" found)
string(FIND "${output}" "Only task state was modeled; no build command ran." boundary)
if(found EQUAL -1 OR boundary EQUAL -1)
    message(FATAL_ERROR "Unexpected graph output: ${output}")
endif()
