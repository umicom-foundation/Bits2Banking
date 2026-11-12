#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-compiler-publication/check.cmake
#
# PURPOSE:
#   Compare compiler publication observations and explicit refusal results.
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
if(SCENARIO STREQUAL "keys")
    set(expected "Metadata: directory, flags and collection boundaries contribute\nMalformed request: no key\n")
elseif(SCENARIO STREQUAL "transaction")
    set(expected "Refused database update: centre and returned plan retained\n")
elseif(SCENARIO STREQUAL "refresh")
    set(expected "Repeated source: stored command refreshed without adding a row\nArgument views: each receiving owner retains its own strings\n")
elseif(SCENARIO STREQUAL "policy")
    set(expected "Policy: explicit MSVC address-sanitizer spelling\nUnsupported sanitizer and reproducible intent: prior plan retained\n")
else()
    message(FATAL_ERROR "Unknown scenario")
endif()
string(APPEND expected "Metadata observations only; no compiler or application was launched.\n")
execute_process(COMMAND "${TOOL}" "${SCENARIO}" RESULT_VARIABLE result
    OUTPUT_VARIABLE output ERROR_VARIABLE error ENCODING UTF-8 TIMEOUT 25)
string(REPLACE "\r\n" "\n" output "${output}")
if(NOT result STREQUAL "0" OR NOT output STREQUAL expected OR NOT error STREQUAL "")
    message(FATAL_ERROR "Observation mismatch (exit ${result})\nExpected:\n${expected}\nObserved:\n${output}\n${error}")
endif()
