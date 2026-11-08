#-----------------------------------------------------------------------------
# Bits2Banking
# File: labs/native/framework-tasks/check.cmake
#
# PURPOSE:
#   Check task refusal and ownership output from the installed SDK consumer.
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
if(CASE STREQUAL "atomic")
    set(expected "Refused directory; command and revision preserved.")
elseif(CASE STREQUAL "shape")
    set(expected "Malformed count refused before traversal.")
elseif(CASE STREQUAL "owned")
    set(expected "Registry owns the published task copy.")
elseif(CASE STREQUAL "reset")
    set(expected "Checked reset removed tasks and advanced revision.")
elseif(CASE STREQUAL "revision")
    set(expected "Exhausted revision refused without mutation.")
else()
    message(FATAL_ERROR "Unknown task scenario")
endif()
execute_process(COMMAND "${TOOL}" "${CASE}" RESULT_VARIABLE result OUTPUT_VARIABLE output ERROR_VARIABLE error TIMEOUT 10)
if(NOT result EQUAL 0)
    message(FATAL_ERROR "Task check failed: ${result} ${output} ${error}")
endif()
string(FIND "${output}" "${expected}" found)
string(FIND "${output}" "No compiler or task command was executed." boundary)
if(found EQUAL -1 OR boundary EQUAL -1)
    message(FATAL_ERROR "Task output differs from its contract: ${output}")
endif()
