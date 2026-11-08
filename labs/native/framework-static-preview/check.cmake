#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-static-preview/check.cmake
#
# PURPOSE:
#   Check observed status, representation size and HEAD serialization in the real SDK lab.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

if(NOT DEFINED TOOL OR NOT DEFINED ROOT OR NOT DEFINED CASE)
    message(FATAL_ERROR "TOOL, ROOT and CASE are required")
endif()
set(method GET)
set(url /message.txt)
set(expected 200)
if(CASE STREQUAL "head")
    set(method HEAD)
elseif(CASE STREQUAL "nested")
    set(url /nested/note.txt)
elseif(CASE STREQUAL "missing")
    set(url /absent.txt)
    set(expected 404)
elseif(CASE STREQUAL "traversal")
    set(url /%2e%2e/message.txt)
    set(expected 403)
elseif(CASE STREQUAL "post")
    set(method POST)
    set(expected 405)
elseif(NOT CASE STREQUAL "get")
    message(FATAL_ERROR "Unknown case")
endif()
execute_process(COMMAND "${TOOL}" "${ROOT}" "${method}" "${url}"
    RESULT_VARIABLE result OUTPUT_VARIABLE output ERROR_VARIABLE error TIMEOUT 10)
if(NOT "${result}" STREQUAL "0" OR NOT output MATCHES "HTTP ${expected}")
    message(FATAL_ERROR "Expected HTTP ${expected}: exit=${result}, ${output} ${error}")
endif()
if(CASE STREQUAL "get" OR CASE STREQUAL "head")
    if(NOT output MATCHES "representation-bytes: 14" OR NOT output MATCHES "48 65 6c 6c 6f")
        message(FATAL_ERROR "Wrong complete representation: ${output}")
    endif()
endif()
if(CASE STREQUAL "head")
    if(NOT output MATCHES "body-sent: no")
        message(FATAL_ERROR "HEAD unexpectedly includes a body")
    endif()
else()
    if(NOT output MATCHES "body-sent: yes")
        message(FATAL_ERROR "Non-HEAD response lost its body")
    endif()
endif()
