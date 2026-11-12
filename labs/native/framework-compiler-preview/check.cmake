#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-compiler-preview/check.cmake
#
# PURPOSE:
#   Compare complete compiler preview observations and JSON refusal results.
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
if(SCENARIO STREQUAL "actions")
    set(expected "Check: syntax-only arguments\nCompile: object arguments\nArchive: refused; previous plan retained\n")
elseif(SCENARIO STREQUAL "identity")
    set(expected "Overlong driver: invalid provider\nNonempty driver: declared, not verified\n")
elseif(SCENARIO STREQUAL "json")
    set(expected "JSON: ordered argument strings\nEscaping: quotes and backslashes preserved\nExecution evidence: false\n")
elseif(SCENARIO STREQUAL "refusal")
    set(expected "Short buffer: previous bytes retained\nInvalid UTF-8: previous bytes retained\n")
else()
    message(FATAL_ERROR "Unknown scenario")
endif()
string(APPEND expected "Preview metadata only; no compiler process was started.\n")
execute_process(COMMAND "${TOOL}" "${SCENARIO}" RESULT_VARIABLE result
    OUTPUT_VARIABLE output ERROR_VARIABLE error ENCODING UTF-8 TIMEOUT 8)
string(REPLACE "\r\n" "\n" output "${output}")
if(NOT result STREQUAL "0" OR NOT output STREQUAL expected OR NOT error STREQUAL "")
    message(FATAL_ERROR "Observation mismatch (exit ${result})\nExpected:\n${expected}\nObserved:\n${output}\n${error}")
endif()
