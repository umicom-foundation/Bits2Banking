#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: tests/content_integrity/check_file_evidence_course.cmake
#
# PURPOSE:
#   Keep native evidence lessons paired, reachable and connected to their executable lab.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

if(NOT DEFINED REPOSITORY_ROOT)
    message(FATAL_ERROR "REPOSITORY_ROOT is required")
endif()
include("${CMAKE_CURRENT_LIST_DIR}/source_reference.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/course_links.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/setup_section.cmake")
set(_course "${REPOSITORY_ROOT}/content/courses/umicom-development")
file(READ "${_course}/course.json" _metadata)
file(READ "${_course}/index.html" _browser_contents)
file(READ "${REPOSITORY_ROOT}/content/lessons/umicom-development/index.md" _written_contents)
file(READ "${REPOSITORY_ROOT}/mkdocs.yml" _navigation)
file(READ "${REPOSITORY_ROOT}/knowledge/registries/lesson-media.json" _media)
function(RequireEvidenceRoute document fragment)
    string(FIND "${document}" "${fragment}" _at)
    if(_at LESS 0)
        message(FATAL_ERROR "Missing evidence course contract: ${fragment}")
    endif()
endfunction()
set(_slugs evidence-bytes-and-version-strings evidence-selection-before-reading
    evidence-observation-ownership evidence-file-and-total-budgets evidence-complete-json-values
    evidence-exclusive-report-files evidence-before-after-comparison evidence-runtime-and-patch-identity)
string(JSON _count LENGTH "${_metadata}" lessons)
math(EXPR _last "${_count} - 1")
set(_previous "language-support-regression-and-source-map")
foreach(_slug IN LISTS _slugs)
    set(_found 0)
    foreach(_i RANGE 0 ${_last})
        string(JSON _path GET "${_metadata}" lessons ${_i} path)
        if(_path STREQUAL "lessons/${_slug}.html")
            math(EXPR _found "${_found} + 1")
            string(JSON _source GET "${_metadata}" lessons ${_i} source)
            string(JSON _manuscript GET "${_metadata}" lessons ${_i} manuscript)
            if(NOT _source STREQUAL "labs/native/file-observation/main.c" OR
                NOT _manuscript STREQUAL "../../lessons/umicom-development/${_slug}.md")
                message(FATAL_ERROR "Wrong lab/edition identity for ${_slug}")
            endif()
            BtbValidateSourceReference("${_source}" "${REPOSITORY_ROOT}" _valid _reason)
            if(NOT _valid)
                message(FATAL_ERROR "Invalid lab source: ${_reason}")
            endif()
        endif()
    endforeach()
    if(NOT _found EQUAL 1)
        message(FATAL_ERROR "Lesson missing or duplicated: ${_slug}")
    endif()
    file(READ "${_course}/lessons/${_slug}.html" _html)
    file(READ "${REPOSITORY_ROOT}/content/lessons/umicom-development/${_slug}.md" _markdown)
    BtbHasSetupSection("${_markdown}" _prepared)
    if(NOT _prepared)
        message(FATAL_ERROR "Lesson lacks independent preparation: ${_slug}")
    endif()
    BtbCheckCourseLinks("${_html}" "${_course}/lessons/${_slug}.html" "${REPOSITORY_ROOT}")
    RequireEvidenceRoute("${_browser_contents}" "href=\"lessons/${_slug}.html\"")
    RequireEvidenceRoute("${_written_contents}" "(${_slug}.md)")
    RequireEvidenceRoute("${_navigation}" "lessons/umicom-development/${_slug}.md")
    RequireEvidenceRoute("${_media}" "content/courses/umicom-development/lessons/${_slug}.html")
    RequireEvidenceRoute("${_markdown}" "(index.md)")
    RequireEvidenceRoute("${_markdown}" "(${_previous}.md)")
    RequireEvidenceRoute("${_html}" "href=\"${_previous}.html\"")
    file(READ "${_course}/lessons/${_previous}.html" _previous_html)
    RequireEvidenceRoute("${_previous_html}" "href=\"${_slug}.html\"")
    set(_previous "${_slug}")
endforeach()
