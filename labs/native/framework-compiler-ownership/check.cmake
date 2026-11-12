#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-compiler-ownership/check.cmake
#
# PURPOSE:
#   Compare complete compiler ownership observations and refused-publication results.
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
if(SCENARIO STREQUAL "target")
    set(expected "Target: x86_64-unknown-linux-gnu\nRejected replacement: previous target retained\n")
elseif(SCENARIO STREQUAL "abi")
    set(expected "ABI identifier: client-abi\nC++ metadata: exceptions and RTTI enabled\n")
elseif(SCENARIO STREQUAL "catalogue")
    set(expected "Oversized catalogue: refused\nOwner bytes: retained\n")
elseif(SCENARIO STREQUAL "request")
    set(expected "Oversized option: previous request retained\nBorrowed option: copied into slot 2\n")
elseif(SCENARIO STREQUAL "publication")
    set(expected "Late argument failure: previous plan retained\nPrevious argument: previous\n")
elseif(SCENARIO STREQUAL "views")
    set(expected "Published view: receiving plan owns every argument\nCopied view: rebased into the copy\n")
elseif(SCENARIO STREQUAL "revision")
    set(expected "Revision exhausted: append refused\nReadable argument: retained\n")
else()
    message(FATAL_ERROR "Unknown scenario")
endif()
string(APPEND expected "Compiler metadata only; no compiler process or application launch.\n")
execute_process(COMMAND "${TOOL}" "${SCENARIO}" RESULT_VARIABLE result
    OUTPUT_VARIABLE output ERROR_VARIABLE error ENCODING UTF-8 TIMEOUT 8)
string(REPLACE "\r\n" "\n" output "${output}")
if(NOT result STREQUAL "0" OR NOT output STREQUAL expected OR NOT error STREQUAL "")
    message(FATAL_ERROR "Observation mismatch (exit ${result})\nExpected:\n${expected}\nObserved:\n${output}\n${error}")
endif()
