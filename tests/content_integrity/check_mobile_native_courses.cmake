#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: tests/content_integrity/check_mobile_native_courses.cmake
#
# PURPOSE:
#   Keep beginner mobile and native-language routes paired with real sources.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.22)
if(NOT DEFINED REPOSITORY_ROOT OR NOT IS_DIRECTORY "${REPOSITORY_ROOT}/content")
    message(FATAL_ERROR "REPOSITORY_ROOT must identify the Bits2Banking checkout")
endif()

include("${CMAKE_CURRENT_LIST_DIR}/setup_section.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/source_reference.cmake")

include("${CMAKE_CURRENT_LIST_DIR}/course_links.cmake")

function(RequireText text fragment context)
    string(FIND "${text}" "${fragment}" _found)
    if(_found EQUAL -1)
        message(FATAL_ERROR "${context}: missing ${fragment}")
    endif()
endfunction()

file(READ "${REPOSITORY_ROOT}/knowledge/registries/lesson-media.json" _media)
file(READ "${REPOSITORY_ROOT}/knowledge/registries/curriculum.json" _curriculum)
file(READ "${REPOSITORY_ROOT}/mkdocs.yml" _navigation)
file(READ "${REPOSITORY_ROOT}/content/courses/index.html" _library)
# Old generated markup is retained in comments for review. Inspect only the
# active document so preservation cannot hide a visible renderer sentinel.
set(_remaining "${_library}")
set(_visible_library "")
while(TRUE)
    string(FIND "${_remaining}" "<!--" _start)
    if(_start EQUAL -1)
        string(APPEND _visible_library "${_remaining}")
        break()
    endif()
    string(SUBSTRING "${_remaining}" 0 ${_start} _prefix)
    string(APPEND _visible_library "${_prefix}")
    math(EXPR _after_start "${_start} + 4")
    string(SUBSTRING "${_remaining}" ${_after_start} -1 _comment_tail)
    string(FIND "${_comment_tail}" "-->" _end)
    if(_end EQUAL -1)
        message(FATAL_ERROR "Course library contains an unclosed HTML comment")
    endif()
    math(EXPR _after_end "${_end} + 3")
    string(SUBSTRING "${_comment_tail}" ${_after_end} -1 _remaining)
endwhile()
if(_visible_library MATCHES "(^|[^A-Za-z0-9_])undefined([^A-Za-z0-9_]|$)")
    message(FATAL_ERROR "Course library contains a visible renderer sentinel")
endif()
string(JSON _pair_count LENGTH "${_media}" lessons)
math(EXPR _pair_last "${_pair_count} - 1")
# Index the shared registry once. Parsing its complete JSON for every lesson
# would repeat work as the catalogue grows. The hash is only a variable key;
# the recorded path and manuscript still come from the reviewed registry.
if(_pair_count LESS 1)
    message(FATAL_ERROR "The lesson-media registry is empty")
endif()
foreach(_pair RANGE 0 ${_pair_last})
    string(JSON _entry GET "${_media}" lessons ${_pair})
    string(JSON _html GET "${_entry}" html)
    string(JSON _md GET "${_entry}" markdown)
    string(SHA256 _key "${_html}")
    if(NOT DEFINED _edition_count_${_key})
        set(_edition_count_${_key} 0)
    endif()
    math(EXPR _edition_count_${_key} "${_edition_count_${_key}} + 1")
    set(_edition_md_${_key} "${_md}")
endforeach()

function(RequireEdition html manuscript)
    string(SHA256 _key "${html}")
    if(NOT DEFINED _edition_count_${_key})
        message(FATAL_ERROR "No edition pair for ${html}")
    endif()
    if(NOT _edition_count_${_key} EQUAL 1)
        message(FATAL_ERROR "Expected one edition pair for ${html}")
    endif()
    if(NOT "${_edition_md_${_key}}" STREQUAL "${manuscript}")
        message(FATAL_ERROR "${html}: editions point to different lessons")
    endif()
endfunction()

# Resolve each course through its catalogue instead of assuming that creating
# files also makes them discoverable. Pair identities must be unique; neither
# a missing manuscript nor a second mapping may silently replace a lesson.
foreach(_id IN ITEMS learning-android learning-kotlin learning-flutter learning-d)
    set(_directory "${REPOSITORY_ROOT}/content/courses/${_id}")
    file(READ "${_directory}/course.json" _course)
    file(READ "${_directory}/index.html" _index)
    string(JSON _count LENGTH "${_course}" lessons)
    if(_count LESS 2)
        message(FATAL_ERROR "${_id} needs both setup and application lessons")
    endif()
    RequireText("${_curriculum}" "content/courses/${_id}/index.html" "Curriculum")
    RequireText("${_visible_library}" "${_id}/index.html" "Library")
    math(EXPR _last "${_count} - 1")
    set(_seen)
    foreach(_i RANGE 0 ${_last})
        string(JSON _path GET "${_course}" lessons ${_i} path)
        string(JSON _manuscript GET "${_course}" lessons ${_i} manuscript)
        string(JSON _source GET "${_course}" lessons ${_i} source)
        string(JSON _title GET "${_course}" lessons ${_i} title)
        if(NOT _path MATCHES "^lessons/[0-9]+-[a-z0-9-]+[.]html$" OR _path IN_LIST _seen)
            message(FATAL_ERROR "${_id}: invalid or duplicate lesson ${_path}")
        endif()
        list(APPEND _seen "${_path}")
        if(NOT _manuscript MATCHES "^[.][.]/[.][.]/lessons/[a-z0-9-]+/${_id}/[0-9]+-[a-z0-9-]+[.]md$")
            message(FATAL_ERROR "${_id}: unexpected manuscript ${_manuscript}")
        endif()
        # Nested package files are valid teaching sources. Keep the original
        # flat-file rule for review; the shared validator checks real files,
        # rejects traversal and verifies that resolved paths stay in the checkout.
        if(FALSE)
        if(NOT _source MATCHES "^labs/(mobile|languages)/[a-z0-9-]+/[A-Za-z0-9_.]+$"
                OR NOT EXISTS "${REPOSITORY_ROOT}/${_source}")
            message(FATAL_ERROR "${_id}: missing or unexpected teaching source ${_source}")
        endif()
        endif()
        BtbValidateSourceReference("${_source}" "${REPOSITORY_ROOT}" _source_valid _source_reason)
        if(NOT _source MATCHES "^labs/(mobile|languages)/[a-z0-9-]+/" OR NOT _source_valid)
            message(FATAL_ERROR "${_id}: invalid teaching source ${_source}: ${_source_reason}")
        endif()
        file(READ "${_directory}/${_path}" _page)
        file(READ "${_directory}/${_manuscript}" _written)
        RequireText("${_index}" "href=\"${_path}\"" "${_id} contents")
        RequireText("${_written}" "# ${_title}" "${_id} manuscript title")
        RequireText("${_page}" ">${_title}</h1>" "${_id} HTML title")
        # Preserve the earlier literal-heading rule for review. The shared
        # source check also accepts the existing Prepare/Before you begin
        # sections and requires actual visible guidance.
        if(FALSE)
        RequireText("${_written}" "## Setup recap" "${_id} independent setup")
        endif()
        BtbHasSetupSection("${_written}" _has_setup)
        if(NOT _has_setup)
            message(FATAL_ERROR "${_id} independent setup: missing visible preparation guidance")
        endif()
        RequireText("${_page}" "href=\"../index.html\"" "${_id} return route")
        # The configured MkDocs hook resolves manuscript links after rendering.
        # Preserve the former blanket refusal for review and validate its real
        # source and publication prerequisites below.
        if(FALSE)
        if(_page MATCHES [=[href="[^":]+[.]md([#?][^"]*)?"]=] OR
           _page MATCHES [=[href="file:]=])
            message(FATAL_ERROR "${_id}: standalone HTML must use publishable links")
        endif()
        endif()
        BtbCheckCourseLinks("${_page}" "${_directory}/${_path}" "${REPOSITORY_ROOT}")
        get_filename_component(_absolute "${_directory}/${_manuscript}" ABSOLUTE)
        file(RELATIVE_PATH _relative "${REPOSITORY_ROOT}" "${_absolute}")
        string(REGEX REPLACE "^content/" "" _site_path "${_relative}")
        RequireText("${_navigation}" "${_site_path}" "Site navigation")
        RequireEdition("content/courses/${_id}/${_path}" "${_relative}")
        # Retained for review: the initial per-lesson full-registry scan is
        # replaced by the single registry index above to bound repeated work.
        if(FALSE)
        set(_matches 0)
        foreach(_pair RANGE 0 ${_pair_last})
            string(JSON _html GET "${_media}" lessons ${_pair} html)
            if(_html STREQUAL "content/courses/${_id}/${_path}")
                string(JSON _md GET "${_media}" lessons ${_pair} markdown)
                if(NOT _md STREQUAL _relative)
                    message(FATAL_ERROR "${_id}: editions point to different lessons")
                endif()
                math(EXPR _matches "${_matches} + 1")
            endif()
        endforeach()
        if(NOT _matches EQUAL 1)
            message(FATAL_ERROR "${_id}: expected one edition pair for ${_path}; found ${_matches}")
        endif()
        endif()
    endforeach()
endforeach()

# A lab supplement belongs to its existing course, not a second beginner
# course with a different identity. Require both entry routes and setup text.
foreach(_item IN ITEMS learning-c/terminal-lab learning-c/terminal-assembly-lab
        learning-c/terminal-to-visual-studio umicom-development/sdk-practical-lab
        umicom-development/event-deadline-lab)
    get_filename_component(_id "${_item}" DIRECTORY)
    get_filename_component(_name "${_item}" NAME)
    file(READ "${REPOSITORY_ROOT}/content/courses/${_id}/index.html" _index)
    file(READ "${REPOSITORY_ROOT}/content/lessons/${_id}/index.md" _written_index)
    file(READ "${REPOSITORY_ROOT}/content/lessons/${_item}.md" _written)
    file(READ "${REPOSITORY_ROOT}/content/courses/${_item}.html" _page)
    RequireText("${_index}" "${_name}.html" "Lab HTML entry")
    RequireText("${_written_index}" "${_name}.md" "Lab manuscript entry")
    # Preserve the earlier literal-heading rule for review. The shared
    # source check also accepts the existing Prepare/Before you begin
    # sections and requires actual visible guidance.
    if(FALSE)
    RequireText("${_written}" "## Setup recap" "Lab setup")
    endif()
    BtbHasSetupSection("${_written}" _has_setup)
    if(NOT _has_setup)
        message(FATAL_ERROR "Lab setup: missing visible preparation guidance")
    endif()
    RequireText("${_navigation}" "lessons/${_item}.md" "Lab navigation")
    RequireEdition("content/courses/${_item}.html" "content/lessons/${_item}.md")
endforeach()
