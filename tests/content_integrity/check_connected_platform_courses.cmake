# -----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: tests/content_integrity/check_connected_platform_courses.cmake
#
# PURPOSE:
#   Check connected platform course routes, paired editions and real source references.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
# -----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.24)
if(NOT DEFINED REPOSITORY_ROOT OR NOT IS_DIRECTORY "${REPOSITORY_ROOT}/content")
    message(FATAL_ERROR "REPOSITORY_ROOT must identify the Bits2Banking checkout")
endif()

function(RequireFragment document fragment context)
    string(FIND "${document}" "${fragment}" _position)
    if(_position LESS 0)
        message(FATAL_ERROR "${context}: missing ${fragment}")
    endif()
endfunction()

# Relative paths in a manuscript may climb to a sibling lessons directory.
# Resolve first, then require the result to remain within the content tree.
function(ReadContent relative output)
    cmake_path(ABSOLUTE_PATH relative BASE_DIRECTORY "${REPOSITORY_ROOT}"
        NORMALIZE OUTPUT_VARIABLE _absolute)
    set(_content "${REPOSITORY_ROOT}/content")
    cmake_path(NORMAL_PATH _content)
    cmake_path(IS_PREFIX _content "${_absolute}" NORMALIZE _inside)
    if(NOT _inside OR NOT EXISTS "${_absolute}" OR IS_DIRECTORY "${_absolute}")
        message(FATAL_ERROR "Invalid content path: ${relative}")
    endif()
    file(READ "${_absolute}" _text)
    set(${output} "${_text}" PARENT_SCOPE)
endfunction()

file(READ "${REPOSITORY_ROOT}/knowledge/registries/lesson-media.json" _registry)
file(READ "${REPOSITORY_ROOT}/mkdocs.yml" _navigation)
string(JSON _entry_count LENGTH "${_registry}" lessons)
if(_entry_count LESS 1)
    message(FATAL_ERROR "The lesson edition registry is empty")
endif()
math(EXPR _last_entry "${_entry_count} - 1")
foreach(_entry RANGE 0 ${_last_entry})
    string(JSON _html GET "${_registry}" lessons ${_entry} html)
    string(JSON _markdown GET "${_registry}" lessons ${_entry} markdown)
    string(SHA256 _key "${_html}")
    # A second edition mapping for one HTML route is ambiguous even if it
    # currently points to the same manuscript.
    if(DEFINED _edition_${_key})
        message(FATAL_ERROR "Duplicate edition identity: ${_html}")
    endif()
    set("_edition_${_key}" "${_markdown}")
endforeach()

foreach(_course IN ITEMS learning-hdl-vhdl learning-iphone-development
        learning-android learning-kotlin learning-flutter learning-riscv)
    ReadContent("content/courses/${_course}/course.json" _metadata)
    ReadContent("content/courses/${_course}/index.html" _index)
    string(JSON _count LENGTH "${_metadata}" lessons)
    if(_count LESS 2)
        message(FATAL_ERROR "${_course}: an ordered course needs its introductory sequence")
    endif()
    math(EXPR _last "${_count} - 1")
    set(_routes)
    foreach(_chapter RANGE 0 ${_last})
        string(JSON _path GET "${_metadata}" lessons ${_chapter} path)
        string(JSON _title GET "${_metadata}" lessons ${_chapter} title)
        string(JSON _manuscript GET "${_metadata}" lessons ${_chapter} manuscript)
        if(NOT _path MATCHES "^lessons/[0-9]+-[a-z0-9-]+[.]html$" OR _path IN_LIST _routes)
            message(FATAL_ERROR "${_course}: invalid or duplicate lesson path ${_path}")
        endif()
        list(APPEND _routes "${_path}")
        set(_html_route "content/courses/${_course}/${_path}")
        set(_md_route "content/courses/${_course}/${_manuscript}")
        cmake_path(NORMAL_PATH _md_route)
        get_filename_component(_slug "${_path}" NAME_WE)
        get_filename_component(_md_slug "${_md_route}" NAME_WE)
        if(NOT _slug STREQUAL _md_slug OR NOT _md_route MATCHES "^content/lessons/.+[.]md$")
            message(FATAL_ERROR "${_course}: edition identities differ for ${_path}")
        endif()
        ReadContent("${_html_route}" _html)
        ReadContent("${_md_route}" _markdown)
        string(SHA256 _key "${_html_route}")
        if(NOT DEFINED _edition_${_key} OR NOT "${_edition_${_key}}" STREQUAL "${_md_route}")
            message(FATAL_ERROR "Incorrect edition mapping: ${_html_route}")
        endif()
        RequireFragment("${_index}" "href=\"${_path}\"" "Course contents")
        string(REGEX REPLACE "^content/" "" _published "${_md_route}")
        RequireFragment("${_navigation}" "${_published}" "Published manuscript navigation")
        RequireFragment("${_html}" "href=\"../index.html\"" "Return to course")
        RequireFragment("${_markdown}" "(index.md)" "Return to manuscript course")
        # Earlier pages may have an id attribute on their heading.
        # Titles are text, so an HTML renderer may encode punctuation while
        # the manuscript retains the same readable characters. Compare both
        # valid spellings instead of rejecting an escaped apostrophe.
        # Retain the earlier literal-only check for source review; the active
        # comparison below also accepts the renderer's encoded spelling.
        if(FALSE)
            RequireFragment("${_html}" "${_title}</h1>" "HTML title")
        endif()
        set(_html_title "${_title}")
        string(REPLACE "&" "&amp;" _html_title "${_html_title}")
        string(REPLACE "<" "&lt;" _html_title "${_html_title}")
        string(REPLACE ">" "&gt;" _html_title "${_html_title}")
        string(REPLACE "\"" "&quot;" _html_title "${_html_title}")
        string(REPLACE "'" "&#39;" _html_title "${_html_title}")
        string(FIND "${_html}" "${_title}</h1>" _literal_title)
        if(_literal_title LESS 0)
            RequireFragment("${_html}" "${_html_title}</h1>" "HTML title")
        endif()
        RequireFragment("${_markdown}" "# ${_title}" "Manuscript title")
        if(_chapter GREATER 0)
            math(EXPR _previous "${_chapter} - 1")
            string(JSON _previous_path GET "${_metadata}" lessons ${_previous} path)
            get_filename_component(_previous_slug "${_previous_path}" NAME_WE)
            RequireFragment("${_html}" "href=\"${_previous_slug}.html\"" "Previous HTML lesson")
            RequireFragment("${_markdown}" "(${_previous_slug}.md)" "Previous manuscript")
        endif()
        if(_chapter LESS _last)
            math(EXPR _next "${_chapter} + 1")
            string(JSON _next_path GET "${_metadata}" lessons ${_next} path)
            get_filename_component(_next_slug "${_next_path}" NAME_WE)
            RequireFragment("${_html}" "href=\"${_next_slug}.html\"" "Next HTML lesson")
            RequireFragment("${_markdown}" "(${_next_slug}.md)" "Next manuscript")
        endif()
        # Lessons are public material. Local authoring paths and unresolved
        # placeholders must never become learner-facing links.
        if(_html MATCHES "C:[/\\\\](Users|umicom-mirror)" OR _markdown MATCHES "C:[/\\\\](Users|umicom-mirror)" OR
           _html MATCHES "\\[\\[course:" OR _markdown MATCHES "\\[\\[course:")
            message(FATAL_ERROR "Private or unresolved authoring reference: ${_html_route}")
        endif()
    endforeach()
endforeach()
# A module must account for every lesson exactly once. This catches an
# apparently complete course index whose later chapters were never assigned
# to a coherent reading sequence.
foreach(_course IN ITEMS learning-hdl-vhdl learning-riscv umicom-development
        umicom-kernel-from-scratch umicom-os-from-scratch safer-c-programming
        learning-data-structures introduction-to-programming building-a-compiler-in-c
        building-a-web-server-in-c learning-sql learning-pascal learning-python
        learning-kotlin learning-d)
    ReadContent("content/courses/${_course}/course.json" _metadata)
    string(JSON _lesson_count LENGTH "${_metadata}" lessons)
    string(JSON _module_count LENGTH "${_metadata}" modules)
    if(_module_count LESS 1)
        message(FATAL_ERROR "${_course}: the course has no reading modules")
    endif()
    set(_ordered_paths)
    math(EXPR _last_lesson "${_lesson_count} - 1")
    foreach(_i RANGE 0 ${_last_lesson})
        string(JSON _path GET "${_metadata}" lessons ${_i} path)
        list(APPEND _ordered_paths "${_path}")
    endforeach()
    set(_module_paths)
    math(EXPR _last_module "${_module_count} - 1")
    foreach(_i RANGE 0 ${_last_module})
        string(JSON _count LENGTH "${_metadata}" modules ${_i} lessons)
        if(_count LESS 1)
            message(FATAL_ERROR "${_course}: empty module ${_i}")
        endif()
        math(EXPR _last "${_count} - 1")
        foreach(_j RANGE 0 ${_last})
            string(JSON _path GET "${_metadata}" modules ${_i} lessons ${_j})
            if(NOT _path IN_LIST _ordered_paths OR _path IN_LIST _module_paths)
                message(FATAL_ERROR "${_course}: unknown or repeated module lesson ${_path}")
            endif()
            list(APPEND _module_paths "${_path}")
        endforeach()
    endforeach()
    if(NOT "${_module_paths}" STREQUAL "${_ordered_paths}")
        message(FATAL_ERROR "${_course}: module order differs from the lesson sequence")
    endif()
endforeach()
# Reading order is owned by course.json, including lessons placed out of
# numeric order to teach prerequisites first. Check every active relationship:
# the presence of one correct link must not conceal an older contradictory link.
function(CheckReadingRelations page previous next)
    set(_active "${page}")
    # Historical markup is retained in comments for review and must not be
    # interpreted as an active browser navigation relationship.
    while(TRUE)
        string(FIND "${_active}" "<!--" _start)
        if(_start LESS 0)
            break()
        endif()
        string(SUBSTRING "${_active}" ${_start} -1 _tail)
        string(FIND "${_tail}" "-->" _end)
        if(_end LESS 0)
            message(FATAL_ERROR "Unclosed HTML comment in course lesson")
        endif()
        math(EXPR _after "${_start} + ${_end} + 3")
        string(SUBSTRING "${_active}" 0 ${_start} _before)
        string(SUBSTRING "${_active}" ${_after} -1 _after_text)
        set(_active "${_before}${_after_text}")
    endwhile()
    string(REGEX MATCHALL "<(a|link)[ \t\r\n][^>]*>" _tags "${_active}")
    foreach(_tag IN LISTS _tags)
        if(_tag MATCHES "rel=[\"'](prev|next)[\"']")
            set(_direction "${CMAKE_MATCH_1}")
            if(_direction STREQUAL "prev")
                set(_expected "${previous}")
            else()
                set(_expected "${next}")
            endif()
            if(NOT _tag MATCHES "href=[\"']([^\"']*)[\"']")
                message(FATAL_ERROR "Reading relation has no destination: ${_tag}")
            endif()
            set(_actual "${CMAKE_MATCH_1}")
            if(NOT "${_actual}" STREQUAL "${_expected}" OR _expected STREQUAL "")
                message(FATAL_ERROR "Reading relation contradicts course order: ${_tag}; expected ${_expected}")
            endif()
        endif()
    endforeach()
endfunction()
foreach(_course IN ITEMS learning-hdl-vhdl
        learning-iphone-development
        learning-riscv
        umicom-development
        learning-android
        learning-c
        safer-c-programming
        learning-data-structures
        learning-algorithms
        learning-html
        learning-javascript
        learning-gtk4
        learning-kotlin
        learning-cpp
        learning-flutter
        learning-pascal
        learning-java
        learning-d
        building-a-text-editor
        umicom-kernel-from-scratch
        learning-rust
        learning-zig
        introduction-to-programming
        building-a-compiler-in-c
        learning-riscv-assembly
        learning-sql
        building-a-web-server-in-c
        learning-css
        learning-python
        umicom-os-from-scratch
        building-blockchain-from-scratch)
    ReadContent("content/courses/${_course}/course.json" _metadata)
    string(JSON _count LENGTH "${_metadata}" lessons)
    if(_count LESS 1)
        message(FATAL_ERROR "${_course}: no lessons")
    endif()
    math(EXPR _last "${_count} - 1")
    foreach(_i RANGE 0 ${_last})
        string(JSON _path GET "${_metadata}" lessons ${_i} path)
        ReadContent("content/courses/${_course}/${_path}" _page)
        set(_previous "")
        set(_next "")
        if(_i GREATER 0)
            math(EXPR _j "${_i} - 1")
            string(JSON _route GET "${_metadata}" lessons ${_j} path)
            get_filename_component(_previous "${_route}" NAME)
        endif()
        if(_i LESS _last)
            math(EXPR _j "${_i} + 1")
            string(JSON _route GET "${_metadata}" lessons ${_j} path)
            get_filename_component(_next "${_route}" NAME)
        endif()
        CheckReadingRelations("${_page}" "${_previous}" "${_next}")
    endforeach()
endforeach()
message(STATUS "Connected platform course editions and navigation are consistent")

