#-----------------------------------------------------------------------------
# Bits2Banking
# File: labs/native/framework-recipes/check.cmake
#
# PURPOSE:
#   Check the installed recipe consumer output and refusal semantics.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

if(NOT DEFINED TOOL OR NOT DEFINED CASE OR NOT DEFINED FIXTURES)
    message(FATAL_ERROR "TOOL, CASE and FIXTURES are required")
endif()
set(file "${FIXTURES}/recipe.json")
if(CASE STREQUAL "inspect")
    set(expected "Recipe recipe-lab: 1 inputs, 1 stages.")
elseif(CASE STREQUAL "owned")
    set(expected "Task registry remains owned after recipe destruction.")
elseif(CASE STREQUAL "identity")
    set(expected "Same recipe ID; different exact-byte digest after whitespace.")
elseif(CASE STREQUAL "refuse")
    set(file "${FIXTURES}/command-refused.json")
    set(expected "Command-bearing recipe refused; output owner unchanged.")
else()
    message(FATAL_ERROR "Unknown recipe exercise")
endif()
execute_process(COMMAND "${TOOL}" "${CASE}" "${file}" RESULT_VARIABLE result OUTPUT_VARIABLE output ERROR_VARIABLE error TIMEOUT 20)
string(FIND "${output}" "${expected}" found)
if(NOT result EQUAL 0 OR found EQUAL -1)
    message(FATAL_ERROR "Recipe exercise mismatch: ${result} ${output} ${error}")
endif()
