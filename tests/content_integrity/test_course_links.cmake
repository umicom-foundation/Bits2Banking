#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: tests/content_integrity/test_course_links.cmake
#
# PURPOSE:
#   Exercise valid published manuscript sources and refuse missing, private or unconfigured routes.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.22)
include("${CMAKE_CURRENT_LIST_DIR}/course_links.cmake")
if(CHILD)
    file(READ "${PAGE}" _document)
    BtbCheckCourseLinks("${_document}" "${PAGE}" "${REPOSITORY_ROOT}")
    return()
endif()
if(NOT DEFINED FIXTURE_ROOT OR NOT IS_ABSOLUTE "${FIXTURE_ROOT}")
    message(FATAL_ERROR "A caller-owned absolute FIXTURE_ROOT is required")
endif()
# Keep every invocation's diagnostic files separate. No cleanup command may
# remove another run's data; CTest's binary directory owns these small fixtures.
string(RANDOM LENGTH 24 ALPHABET 0123456789abcdef _nonce)
set(_root "${FIXTURE_ROOT}/${CASE}-${_nonce}")
if(EXISTS "${_root}")
    message(FATAL_ERROR "Fixture path already exists")
endif()
file(MAKE_DIRECTORY "${_root}/content/courses/sample/lessons" "${_root}/content/lessons" "${_root}/hooks" "${_root}/labs")
file(WRITE "${_root}/content/lessons/known.md" "# Known source\n")
file(WRITE "${_root}/outside.md" "# Outside docs_dir\n")
file(WRITE "${_root}/labs/example.c" "int example(void) { return 0; }\n")
file(WRITE "${_root}/hooks/course_source_links.py" "# Presence fixture only; this test does not execute the MkDocs hook.\n")
file(WRITE "${_root}/mkdocs.yml" "hooks:\n  - hooks/course_source_links.py\n")
set(_success TRUE)
set(_document "<a href=\"../../../lessons/known.md\">Read lesson</a>")
if(CASE STREQUAL "markdown")
elseif(CASE STREQUAL "fragment")
    set(_document "<a href=\"../../../lessons/known.md#goal\">Read goal</a>")
elseif(CASE STREQUAL "query")
    set(_document "<a href=\"../../../lessons/known.md?mode=read#goal\">Read goal</a>")
elseif(CASE STREQUAL "single-quote")
    set(_document "<a href='../../../lessons/known.md'>Read lesson</a>")
elseif(CASE STREQUAL "external")
    set(_document "<a href=\"https://example.org/source.md\">External source</a>")
elseif(CASE STREQUAL "commented")
    set(_document "<!-- <a href=\"../../../../outside.md\">Preserved old route</a> -->")
elseif(CASE STREQUAL "missing-manuscript")
    set(_document "<a href=\"../../../lessons/missing.md\">Missing</a>")
    set(_success FALSE)
elseif(CASE STREQUAL "outside-content")
    set(_document "<a href=\"../../../../outside.md\">Outside</a>")
    set(_success FALSE)
elseif(CASE STREQUAL "missing-adapter")
    # Use a different root with no adapter; preserve the original fixture.
    set(_root "${_root}/missing-adapter")
    file(MAKE_DIRECTORY "${_root}/content/courses/sample/lessons" "${_root}/content/lessons")
    file(WRITE "${_root}/content/lessons/known.md" "# Known source\n")
    file(WRITE "${_root}/mkdocs.yml" "hooks:\n  - hooks/course_source_links.py\n")
    set(_success FALSE)
elseif(CASE STREQUAL "unconfigured-adapter")
    file(WRITE "${_root}/mkdocs.yml" "# hooks:\n#  - hooks/course_source_links.py\n")
    set(_success FALSE)
elseif(CASE STREQUAL "lab-source")
    set(_document "<a href=\"../../../../labs/example.c\">Unpublished source</a>")
    set(_success FALSE)
elseif(CASE STREQUAL "local-file")
    set(_document "<a href=\"file:///private/source.md\">Local file</a>")
    set(_success FALSE)
elseif(CASE STREQUAL "unclosed-comment")
    set(_document "<!-- preserved link")
    set(_success FALSE)
else()
    message(FATAL_ERROR "Unknown course link case: ${CASE}")
endif()
set(_page "${_root}/content/courses/sample/lessons/example.html")
file(WRITE "${_page}" "${_document}")
execute_process(COMMAND "${CMAKE_COMMAND}" -DCHILD=ON "-DPAGE=${_page}"
    "-DREPOSITORY_ROOT=${_root}" -P "${CMAKE_CURRENT_LIST_FILE}"
    RESULT_VARIABLE _result OUTPUT_VARIABLE _output ERROR_VARIABLE _errors
    TIMEOUT 5)
file(WRITE "${_root}/check-output.txt" "${_output}\n${_errors}")
if(_success AND NOT _result STREQUAL "0")
    message(FATAL_ERROR "Expected acceptance for ${CASE}: ${_result}: ${_errors}")
elseif(NOT _success AND _result STREQUAL "0")
    message(FATAL_ERROR "Expected refusal for ${CASE}")
elseif(NOT _success AND NOT _result MATCHES "^[1-9][0-9]*$")
    message(FATAL_ERROR "A process timeout or launch failure is not a source refusal: ${_result}")
endif()
