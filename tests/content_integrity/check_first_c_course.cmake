# -----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: tests/content_integrity/check_first_c_course.cmake
#
# PURPOSE:
#   Check the ordered course, navigation and complete laboratory source examples.
#   Structural checks are not compiler, browser or learner qualification.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
# -----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
if(NOT DEFINED REPOSITORY_ROOT)
    get_filename_component(REPOSITORY_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
endif()
# Resolve the published Learning C course, while retaining the old location
# for review. Content, navigation and exact source-example checks remain active.
if(FALSE)
    set(_course "${REPOSITORY_ROOT}/content/courses/c-from-the-beginning")
endif()
set(_course "${REPOSITORY_ROOT}/content/courses/learning-c")
file(READ "${_course}/course.json" _registry)
file(READ "${_course}/index.html" _index)
string(JSON _count LENGTH "${_registry}" lessons)
# The original eleven lab lessons remain checked below; six reading lessons
# have their own source and navigation contract. Retain the old gate for review.
if(FALSE)
if(NOT _count EQUAL 11)
    message(FATAL_ERROR "Review the introductory syllabus and its checks when adding a lesson")
endif()
endif()
# Retain the former count gate for review. The identity catalogue below now
# checks the reordered syllabus and every module, including the boundary lab.
if(FALSE)
if(NOT _count EQUAL 17)
    message(FATAL_ERROR "Review the full Learning C syllabus and its checks when adding a lesson")
endif()
endif()
function(require_text text needle reason)
    string(FIND "${text}" "${needle}" _position)
    if(_position EQUAL -1)
        message(FATAL_ERROR "Missing ${reason}")
    endif()
endfunction()
function(require_file file)
    if(NOT EXISTS "${file}" OR IS_DIRECTORY "${file}")
        message(FATAL_ERROR "Missing learning file: ${file}")
    endif()
endfunction()
# The positional split assumed that all laboratory lessons preceded all source
# readings. Preserve it for review; the active implementation selects a lesson's
# contract by its stable identity so pedagogical reordering cannot change it.
if(FALSE)
set(_source_count 0)
foreach(_n RANGE 0 10)
    string(JSON _lesson GET "${_registry}" lessons ${_n} path)
    string(JSON _manuscript GET "${_registry}" lessons ${_n} manuscript)
    if(NOT _lesson MATCHES "^lessons/[a-z0-9-]+\\.html$" OR
       NOT _manuscript MATCHES "^\\.\\./\\.\\./lessons/learning-c/[a-z0-9-]+\\.md$")
        message(FATAL_ERROR "Unexpected course path")
    endif()
    require_file("${_course}/${_lesson}")
    require_file("${_course}/${_manuscript}")
    file(READ "${_course}/${_lesson}" _html)
    file(READ "${_course}/${_manuscript}" _md)
    require_text("${_index}" "href=\"${_lesson}\"" "lesson in contents")
    foreach(_link IN ITEMS "../index.html" "../glossary.html" "../practical-guide.html" "../../learning-paths.html")
        require_text("${_html}" "href=\"${_link}\"" "course navigation")
    endforeach()
    require_text("${_html}" "<details>" "explained self-check")
    require_text("${_html}" "id=\"main\"" "skip destination")
    if(_n GREATER 0)
        math(EXPR _previous "${_n} - 1")
        string(JSON _previous_path GET "${_registry}" lessons ${_previous} path)
        get_filename_component(_previous_name "${_previous_path}" NAME)
        require_text("${_html}" "rel=\"prev\" href=\"${_previous_name}\"" "previous lesson")
    endif()
    if(_n LESS 11)
        math(EXPR _next "${_n} + 1")
        string(JSON _next_path GET "${_registry}" lessons ${_next} path)
        get_filename_component(_next_name "${_next_path}" NAME)
        require_text("${_html}" "rel=\"next\" href=\"${_next_name}\"" "next lesson")
    endif()
    string(JSON _source ERROR_VARIABLE _source_error GET "${_registry}" lessons ${_n} source)
    if(_source_error STREQUAL "NOTFOUND")
        math(EXPR _source_count "${_source_count} + 1")
        if(NOT _source MATCHES "^labs/native/first-c-programs/[a-z_]+\\.c$")
            message(FATAL_ERROR "Unexpected displayed source path")
        endif()
        require_file("${REPOSITORY_ROOT}/${_source}")
        file(READ "${REPOSITORY_ROOT}/${_source}" _code)
        string(REPLACE "\r\n" "\n" _code "${_code}")
        string(REPLACE "\r\n" "\n" _md "${_md}")
        string(REPLACE "\r\n" "\n" _html "${_html}")
        require_text("${_md}" "${_code}" "complete current C source in manuscript")
        string(REPLACE "&" "&amp;" _encoded "${_code}")
        string(REPLACE "<" "&lt;" _encoded "${_encoded}")
        string(REPLACE ">" "&gt;" _encoded "${_encoded}")
        string(REPLACE "\"" "&quot;" _encoded "${_encoded}")
        require_text("${_html}" "<pre><code>${_encoded}</code></pre>" "complete current C source in browser lesson")
    endif()
endforeach()
if(NOT _source_count EQUAL 8)
    message(FATAL_ERROR "The eight displayed lab examples must retain their source identities")
endif()

# Later chapters are HTML source-reading lessons. They deliberately reference
# Kernel files, rather than claiming to embed a complete, buildable local lab.
# Keep that distinct contract explicit while retaining the eight lab comparisons.
set(_reading_sources
    "umicom-kernel/include/umicom/user/native_contract.h"
    "umicom-kernel/programs/support/native_contract.c"
    "umicom-kernel/kernel/console_shell.c"
    "umicom-kernel/cmake/DiskInspection.cmake"
    "umicom-kernel/kernel/console_file_range.inc"
    "umicom-kernel/kernel/console_file_range.inc")
foreach(_n RANGE 11 16)
    string(JSON _lesson GET "${_registry}" lessons ${_n} path)
    string(JSON _title GET "${_registry}" lessons ${_n} title)
    string(JSON _source GET "${_registry}" lessons ${_n} source)
    math(EXPR _reading_index "${_n} - 11")
    list(GET _reading_sources ${_reading_index} _expected_source)
    if(NOT _lesson MATCHES "^lessons/[a-z0-9-]+\\.html$" OR
       NOT _source STREQUAL _expected_source)
        message(FATAL_ERROR "Unexpected source-reading lesson identity: ${_lesson}")
    endif()
    require_file("${_course}/${_lesson}")
    file(READ "${_course}/${_lesson}" _html)
    require_text("${_index}" "href=\"${_lesson}\"" "source-reading lesson in contents")
    require_text("${_html}" "<h1>${_title}</h1>" "registered source-reading title")
    require_text("${_html}" "<details>" "explained source-reading self-check")
    require_text("${_html}" "id=\"main\"" "source-reading skip destination")
    string(REGEX REPLACE "^umicom-kernel/" "" _kernel_file "${_source}")
    require_text("${_html}"
        "href=\"https://github.com/umicom-foundation/umicom-kernel/blob/main/${_kernel_file}\""
        "published Kernel source reference")
    foreach(_link IN ITEMS "../index.html" "../glossary.html" "../practical-guide.html" "../../learning-paths.html")
        require_text("${_html}" "href=\"${_link}\"" "source-reading navigation")
    endforeach()
    math(EXPR _previous "${_n} - 1")
    string(JSON _previous_path GET "${_registry}" lessons ${_previous} path)
    get_filename_component(_previous_name "${_previous_path}" NAME)
    require_text("${_html}" "rel=\"prev\" href=\"${_previous_name}\"" "previous source-reading lesson")
    if(_n LESS 16)
        math(EXPR _next "${_n} + 1")
        string(JSON _next_path GET "${_registry}" lessons ${_next} path)
        get_filename_component(_next_name "${_next_path}" NAME)
        require_text("${_html}" "rel=\"next\" href=\"${_next_name}\"" "next source-reading lesson")
    endif()
endforeach()
endif()

set(_identities
    01-read-your-first-program
    02-build-and-run-one-step
    03-values-and-calculations
    04-decisions-and-valid-input
    05-repeat-with-a-boundary
    06-functions-with-a-contract
    07-check-results-and-errors
    09-arrays-and-valid-positions
    12-structures-and-complete-results
    10-pointers-and-borrowing
    15-headers-objects-and-linking
    11-bounded-spans-and-rejection
    13-function-pointers-and-test-doubles
    14-storage-duration-and-freestanding-code
    16-counts-offsets-and-progress
    17-bits-and-hexadecimal
    18-check-a-function-at-its-boundaries
    08-connect-to-systems-lessons
    19-length-capacity-and-terminators
    20-allocation-outputs-and-lifetimes
    21-follow-a-rejected-call)
set(_sources
    labs/native/first-c-programs/hello.c
    NONE
    labs/native/first-c-programs/values.c
    labs/native/first-c-programs/decisions.c
    labs/native/first-c-programs/repetition.c
    labs/native/first-c-programs/functions.c
    NONE
    labs/native/first-c-programs/arrays.c
    umicom-kernel/include/umicom/user/native_contract.h
    labs/native/first-c-programs/borrowing.c
    umicom-kernel/cmake/DiskInspection.cmake
    labs/native/first-c-programs/borrowed_counts.c
    umicom-kernel/programs/support/native_contract.c
    umicom-kernel/kernel/console_shell.c
    umicom-kernel/kernel/console_file_range.inc
    umicom-kernel/kernel/console_file_range.inc
    labs/native/framework-activity/activity.c
    NONE
    NONE
    NONE
    NONE)
# Extend the reviewed syllabus explicitly. These chapters reuse Framework's
# digest engine through a borrowed-stream adapter; the original eight complete
# introductory source comparisons remain unchanged below.
list(APPEND _identities
    22-open-read-and-close-a-file
    23-chunks-eof-and-read-errors
    24-status-values-and-complete-results
    25-check-file-digests-independently)
list(APPEND _sources
    labs/native/framework-checksum/main.c
    labs/native/framework-checksum/checksum.c
    labs/native/framework-checksum/checksum.h
    labs/native/framework-checksum/test_checksum.c)
list(LENGTH _identities _expected_count)
list(LENGTH _sources _expected_sources)
if(NOT _count EQUAL _expected_count OR NOT _expected_sources EQUAL _expected_count)
    message(FATAL_ERROR "Review Learning C lesson identities and source contracts with syllabus changes")
endif()
math(EXPR _last "${_count} - 1")
set(_source_count 0)
set(_ordered_paths)
foreach(_n RANGE 0 ${_last})
    list(GET _identities ${_n} _id)
    list(GET _sources ${_n} _expected_source)
    string(JSON _lesson GET "${_registry}" lessons ${_n} path)
    string(JSON _manuscript GET "${_registry}" lessons ${_n} manuscript)
    if(NOT _lesson STREQUAL "lessons/${_id}.html" OR
       NOT _manuscript STREQUAL "../../lessons/learning-c/${_id}.md")
        message(FATAL_ERROR "Learning C sequence or manuscript mismatch at ${_id}")
    endif()
    list(APPEND _ordered_paths "${_lesson}")
    require_file("${_course}/${_lesson}")
    require_file("${_course}/${_manuscript}")
    file(READ "${_course}/${_lesson}" _html)
    file(READ "${_course}/${_manuscript}" _md)
    require_text("${_index}" "href=\"${_lesson}\"" "lesson in contents: ${_id}")
    foreach(_link IN ITEMS "../index.html" "../glossary.html" "../practical-guide.html" "../../learning-paths.html")
        require_text("${_html}" "href=\"${_link}\"" "course navigation: ${_id}")
    endforeach()
    # Answers can be visible text or expandable explanations. Preserve the
    # educational requirement without tying it to one presentation widget.
    if(NOT _html MATCHES "<details>" AND
       NOT _html MATCHES "<h3>Answer</h3>" AND
       NOT _html MATCHES "<h2>Exercise and explanation</h2>")
        message(FATAL_ERROR "Missing explained self-check: ${_id}")
    endif()
    require_text("${_html}" "id=\"main\"" "skip destination: ${_id}")
    if(_n GREATER 0)
        math(EXPR _previous "${_n} - 1")
        list(GET _identities ${_previous} _previous_id)
        require_text("${_html}" "rel=\"prev\" href=\"${_previous_id}.html\"" "previous lesson: ${_id}")
        require_text("${_md}" "(${_previous_id}.md)" "previous manuscript: ${_id}")
    endif()
    if(_n LESS _last)
        math(EXPR _next "${_n} + 1")
        list(GET _identities ${_next} _next_id)
        require_text("${_html}" "rel=\"next\" href=\"${_next_id}.html\"" "next lesson: ${_id}")
        require_text("${_md}" "(${_next_id}.md)" "next manuscript: ${_id}")
    endif()
    string(JSON _source ERROR_VARIABLE _source_error GET "${_registry}" lessons ${_n} source)
    if(_expected_source STREQUAL "NONE")
        if(_source_error STREQUAL "NOTFOUND")
            message(FATAL_ERROR "Unexpected source identity for ${_id}")
        endif()
        continue()
    endif()
    if(NOT _source_error STREQUAL "NOTFOUND" OR NOT _source STREQUAL _expected_source)
        message(FATAL_ERROR "Source identity changed for ${_id}")
    endif()
    if(_source MATCHES "^labs/native/first-c-programs/")
        math(EXPR _source_count "${_source_count} + 1")
        require_file("${REPOSITORY_ROOT}/${_source}")
        file(READ "${REPOSITORY_ROOT}/${_source}" _code)
        foreach(_text IN ITEMS _code _md _html)
            string(REPLACE "\r\n" "\n" ${_text} "${${_text}}")
        endforeach()
        require_text("${_md}" "${_code}" "complete current C source: ${_id}")
        string(REPLACE "&" "&amp;" _encoded "${_code}")
        string(REPLACE "<" "&lt;" _encoded "${_encoded}")
        string(REPLACE ">" "&gt;" _encoded "${_encoded}")
        string(REPLACE "\"" "&quot;" _encoded "${_encoded}")
        require_text("${_html}" "<pre><code>${_encoded}</code></pre>" "complete browser C example: ${_id}")
    elseif(_source MATCHES "^umicom-kernel/")
        string(REGEX REPLACE "^umicom-kernel/" "" _kernel_file "${_source}")
        require_text("${_html}" "href=\"https://github.com/umicom-foundation/umicom-kernel/blob/main/${_kernel_file}\"" "published Kernel reading: ${_id}")
    elseif(_source MATCHES "^labs/native/framework-checksum/")
        require_file("${REPOSITORY_ROOT}/${_source}")
        require_text("${_html}" "${_source}" "checksum source reference")
        require_text("${_md}" "${_source}" "checksum manuscript reference")
    else()
        require_file("${REPOSITORY_ROOT}/${_source}")
        require_text("${_html}" "${_source}" "boundary example source reference")
        require_text("${_md}" "BtbActivityAdvance(1000U, &next)" "boundary exercise")
        require_text("${_html}" "UMI_STATUS_CAPACITY_EXCEEDED" "boundary result")
    endif()
endforeach()
if(NOT _source_count EQUAL 8)
    message(FATAL_ERROR "All eight complete laboratory source comparisons must remain active")
endif()

# Module order is the learning path exposed to readers. Require an exact
# partition of the flat catalogue: no missing, repeated or reordered chapters.
string(JSON _module_count LENGTH "${_registry}" modules)
if(_module_count LESS 1)
    message(FATAL_ERROR "Learning C needs at least one reading module")
endif()
math(EXPR _last_module "${_module_count} - 1")
set(_module_paths)
foreach(_module RANGE 0 ${_last_module})
    string(JSON _module_size LENGTH "${_registry}" modules ${_module} lessons)
    if(_module_size LESS 1)
        message(FATAL_ERROR "Empty Learning C module")
    endif()
    math(EXPR _last_member "${_module_size} - 1")
    foreach(_member RANGE 0 ${_last_member})
        string(JSON _path GET "${_registry}" modules ${_module} lessons ${_member})
        list(APPEND _module_paths "${_path}")
    endforeach()
endforeach()
if(NOT "${_module_paths}" STREQUAL "${_ordered_paths}")
    message(FATAL_ERROR "Learning C modules must match the complete reading order exactly once")
endif()

require_file("${_course}/glossary.html")
require_file("${_course}/practical-guide.html")
message(STATUS "Introductory C course source relationships are present; runtime and browser qualification are separate")
