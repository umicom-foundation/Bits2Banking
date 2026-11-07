# -----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: tests/content_integrity/check_systems_practical_labs.cmake
#
# PURPOSE:
#   Keep practical lesson editions registered and navigable as standalone HTML.
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
file(READ "${REPOSITORY_ROOT}/knowledge/registries/lesson-media.json" _registry)
string(JSON _count LENGTH "${_registry}" lessons)
if(_count LESS 1)
    message(FATAL_ERROR "The media registry has no lesson editions")
endif()
set(_required
    19-length-capacity-and-terminators
    20-allocation-outputs-and-lifetimes
    37-use-a-framework-function-in-a-lab
    38-incremental-functions-and-failure-contracts
    functionality-lab-map
    03-inspect-object-code
    05-inspect-a-riscv-object
    15-test-user-memory-boundaries
    16-discover-the-native-program-contract
    byte-tokenizer-contract-lab
    sequence-split-contract-lab
    04-link-records-with-framework-hashes
    21-follow-a-rejected-call
    39-trace-an-event-to-a-framework-rule
    03-own-state-for-a-window
    04-understand-append-and-repeated-save
    04-check-a-ledger-invariant
    03-validate-records-before-saving
    04-follow-a-form-to-a-c-service
    04-test-a-layout-with-long-content
    03-separate-visible-state-from-saved-state
    03-count-text-at-the-right-boundary
    03-read-a-transaction-as-a-unit
    08-reject-an-invalid-port-before-launch
    10-read-past-a-comment-safely
    04-follow-arguments-through-a-function
    06-explain-a-word-sized-result
    04-draw-registers-before-writing-memory
    17-publish-a-contract-only-after-validation
    10-understand-why-a-process-id-is-not-ownership
    03-follow-an-exit-status-to-the-terminal
    05-read-a-parent-pin-and-a-child-checkout
    checkpoint-observation-lab
    experiment-observation-lab
    priority-queue-reading-lab
    05-define-the-bytes-before-hashing
    04-follow-a-discount-factor-and-its-failures
    03-follow-evidence-through-a-payment)
set(_found)
math(EXPR _last "${_count} - 1")
foreach(_i RANGE 0 ${_last})
    string(JSON _html GET "${_registry}" lessons ${_i} html)
    get_filename_component(_identity "${_html}" NAME_WE)
    if(NOT _identity IN_LIST _required)
        continue()
    endif()
    if(_identity IN_LIST _found)
        message(FATAL_ERROR "Duplicate practical lesson identity: ${_identity}")
    endif()
    list(APPEND _found "${_identity}")
    string(JSON _md GET "${_registry}" lessons ${_i} markdown)
    string(JSON _course GET "${_registry}" lessons ${_i} course)
    if(NOT _html STREQUAL "content/courses/${_course}/lessons/${_identity}.html" OR
       NOT _md MATCHES "^content/lessons/[a-z0-9/-]+[.]md$" OR
       NOT _md MATCHES "/${_identity}[.]md$")
        message(FATAL_ERROR "Mismatched lesson editions: ${_identity}")
    endif()
    file(READ "${REPOSITORY_ROOT}/${_md}" _markdown)
    file(READ "${REPOSITORY_ROOT}/${_html}" _page)
    file(READ "${REPOSITORY_ROOT}/content/courses/${_course}/index.html" _index)
    string(FIND "${_index}" "href=\"lessons/${_identity}.html\"" _route)
    if(_route EQUAL -1 OR NOT _page MATCHES "id=\"main\"")
        message(FATAL_ERROR "Practical lesson is unreachable: ${_identity}")
    endif()
    if(NOT _identity STREQUAL "functionality-lab-map" AND
       NOT _markdown MATCHES "## Setup recap")
        message(FATAL_ERROR "Practical lesson lacks its own setup recap: ${_identity}")
    endif()
    # Source studies carry the code identity in the edition record. Checking both
    # editions prevents an updated catalogue from silently pointing at an
    # unrelated example. Older lessons keep their existing contracts.
    string(JSON _source ERROR_VARIABLE _source_error GET "${_registry}" lessons ${_i} learningSource)
    if(NOT _source_error)
        string(JSON _title GET "${_registry}" lessons ${_i} title)
        foreach(_text IN ITEMS _markdown _page)
            string(FIND "${${_text}}" "${_source}" _source_position)
            string(FIND "${${_text}}" "${_title}" _title_position)
            if(_source_position EQUAL -1 OR _title_position EQUAL -1)
                message(FATAL_ERROR "Lesson identity differs from its edition record: ${_identity}")
            endif()
        endforeach()
        foreach(_heading IN ITEMS "Setup recap" "Understand the idea" "Work through the lab"
                "Expected result" "If the result differs" "Explain it yourself")
            string(FIND "${_markdown}" "## ${_heading}" _md_heading)
            string(FIND "${_page}" "<h2>${_heading}</h2>" _html_heading)
            if(_md_heading EQUAL -1 OR _html_heading EQUAL -1)
                message(FATAL_ERROR "Missing teaching section in ${_identity}: ${_heading}")
            endif()
        endforeach()
        string(FIND "${_page}" "<article>" _article_start)
        string(FIND "${_page}" "<h1>" _lesson_start)
        string(FIND "${_page}" "</article>" _article_end REVERSE)
        string(FIND "${_page}" "<nav aria-label=\"Lesson sequence\">" _lesson_navigation)
        if(_article_start EQUAL -1 OR _lesson_start LESS _article_start OR
           _lesson_navigation LESS _lesson_start OR _article_end LESS _lesson_navigation)
            message(FATAL_ERROR "Lesson or navigation escapes its reading container: ${_identity}")
        endif()
    endif()
    # Standalone HTML is served unchanged. A Markdown source link can work in
    # the source tree but fail in the published site, so resolve every local
    # target inside content and require the published file to exist.
    string(REGEX MATCHALL "(href|src)=\"[^\"]+\"" _links "${_page}")
    get_filename_component(_directory "${REPOSITORY_ROOT}/${_html}" DIRECTORY)
    foreach(_attribute IN LISTS _links)
        string(REGEX REPLACE "^(href|src)=\"([^\"]+)\"$" "\\2" _link "${_attribute}")
        if(_link MATCHES "^(https?://|mailto:|#)")
            continue()
        endif()
        if(_link MATCHES "[.]md([#?]|$)" OR _link MATCHES "^(/|[A-Za-z]+:)")
            message(FATAL_ERROR "Unpublished local route in ${_identity}: ${_link}")
        endif()
        string(REGEX REPLACE "[#?].*$" "" _link "${_link}")
        get_filename_component(_resolved "${_directory}/${_link}" ABSOLUTE)
        file(RELATIVE_PATH _relative "${REPOSITORY_ROOT}/content" "${_resolved}")
        if(_relative MATCHES "^[.][.](/|$)" OR NOT EXISTS "${_resolved}")
            message(FATAL_ERROR "Missing published target in ${_identity}: ${_link}")
        endif()
    endforeach()
endforeach()
foreach(_identity IN LISTS _required)
    if(NOT _identity IN_LIST _found)
        message(FATAL_ERROR "Practical lesson missing from media registry: ${_identity}")
    endif()
endforeach()
message(STATUS "Practical lesson editions and local routes are present; compiler and learner checks are separate")

