#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/local-ai-routing/check.cmake
#
# PURPOSE:
#   Check offline observations without invoking a model server.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
if(SCENARIO STREQUAL "invalid-port")
    execute_process(COMMAND "${TOOL}" local --send-reviewed-prompt 70000 fixture "Hello"
        RESULT_VARIABLE result OUTPUT_VARIABLE output ERROR_VARIABLE error)
    string(REPLACE "\r\n" "\n" error "${error}")
    if(NOT result EQUAL 2 OR NOT output STREQUAL "" OR
       NOT error STREQUAL "Invalid port, model ID or prompt capacity.\n")
        message(FATAL_ERROR "Invalid port admission mismatch: ${result};${output};${error}")
    endif()
    return()
endif()
if(SCENARIO STREQUAL "selection")
    set(expected "Selected lab.small; remote candidate excluded.\n")
elseif(SCENARIO STREQUAL "capability")
    set(expected "No embedding runtime; no chat fallback.\n")
elseif(SCENARIO STREQUAL "context")
    set(expected "No runtime fits 9000 tokens.\n")
elseif(SCENARIO STREQUAL "health")
    set(expected "Unavailable small runtime excluded; selected lab.large.\n")
elseif(SCENARIO STREQUAL "dispatch")
    set(expected "Fixture answer; no model executed.\n")
elseif(SCENARIO STREQUAL "policy")
    set(expected "Remote request denied before callback.\n")
else()
    message(FATAL_ERROR "Unknown offline case")
endif()
execute_process(COMMAND "${TOOL}" offline "${SCENARIO}"
    RESULT_VARIABLE result OUTPUT_VARIABLE output ERROR_VARIABLE error)
# Only Windows text-mode newline normalization is permitted.
string(REPLACE "\r\n" "\n" output "${output}")
if(NOT result EQUAL 0 OR NOT output STREQUAL expected OR NOT error STREQUAL "")
    message(FATAL_ERROR "Observation mismatch: ${result};${output};${error}")
endif()
