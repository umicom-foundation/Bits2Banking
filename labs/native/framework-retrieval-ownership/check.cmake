#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-retrieval-ownership/check.cmake
#
# PURPOSE:
#   Compare complete retrieval observations and refused-publication results.
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
if(SCENARIO STREQUAL "chunk")
    set(expected "Chunk: guide:7 at bytes 10..15\nOverflow refusal: previous chunk retained\n")
elseif(SCENARIO STREQUAL "geometry")
    set(expected "Cosine: aligned 1, orthogonal 0, opposite -1\nInvalid component: previous embedding retained\n")
elseif(SCENARIO STREQUAL "lexical")
    set(expected "Lexical order: guide:1, guide:0\nMalformed late chunk: output retained\n")
elseif(SCENARIO STREQUAL "store")
    set(expected "Oversized store: refused\nEntry and output bytes: retained\n")
elseif(SCENARIO STREQUAL "top")
    set(expected "Top matches: 0, 3, 1\nTied scores: insertion order retained\n")
elseif(SCENARIO STREQUAL "hybrid")
    set(expected "Combined candidate: score 1\nOverflowing blend: output retained\n")
elseif(SCENARIO STREQUAL "rerank")
    set(expected "Late callback refusal: 2 calls, output retained\nFinite reranking: scores -1, -2\n")
else()
    message(FATAL_ERROR "Unknown scenario")
endif()
string(APPEND expected "Local retrieval only; no model training or network request.\n")
execute_process(COMMAND "${TOOL}" "${SCENARIO}" RESULT_VARIABLE result
    OUTPUT_VARIABLE output ERROR_VARIABLE error ENCODING UTF-8 TIMEOUT 8)
string(REPLACE "\r\n" "\n" output "${output}")
if(NOT result STREQUAL "0" OR NOT output STREQUAL expected OR NOT error STREQUAL "")
    message(FATAL_ERROR "Observation mismatch (exit ${result})\nExpected:\n${expected}\nObserved:\n${output}\n${error}")
endif()
