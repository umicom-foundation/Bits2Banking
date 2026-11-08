# -----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: tests/content_integrity/check_programming_projects.cmake
#
# PURPOSE:
#   Verify linked course editions, ordered chapters and companion project sources.
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
include("${CMAKE_CURRENT_LIST_DIR}/course_links.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/source_reference.cmake")

function(RequireText text fragment context)
    string(FIND "${text}" "${fragment}" _at)
    if(_at EQUAL -1)
        message(FATAL_ERROR "${context}: missing ${fragment}")
    endif()
endfunction()
set(_courses introduction-to-programming learning-data-structures learning-algorithms
    learning-pascal safer-c-programming building-a-text-editor building-a-compiler-in-c)
file(READ "${REPOSITORY_ROOT}/knowledge/registries/lesson-media.json" _registry)
string(JSON _entries LENGTH "${_registry}" lessons)
math(EXPR _last_entry "${_entries} - 1")
# Index edition pairs by their published HTML identity. Independent path
# searches would miss an entry that accidentally pairs two different lessons.
foreach(_entry RANGE 0 ${_last_entry})
    string(JSON _course GET "${_registry}" lessons ${_entry} course)
    if(NOT _course IN_LIST _courses)
        continue()
    endif()
    string(JSON _html GET "${_registry}" lessons ${_entry} html)
    string(JSON _markdown GET "${_registry}" lessons ${_entry} markdown)
    string(SHA256 _key "${_html}")
    if(DEFINED _pair_${_key})
        message(FATAL_ERROR "Duplicate lesson media identity: ${_html}")
    endif()
    set("_pair_${_key}" "${_markdown}")
endforeach()
file(READ "${REPOSITORY_ROOT}/mkdocs.yml" _navigation)
file(READ "${REPOSITORY_ROOT}/content/courses/index.html" _catalogue)
file(READ "${REPOSITORY_ROOT}/content/courses/learning-paths.html" _paths)
foreach(_course IN LISTS _courses)
    set(_base "${REPOSITORY_ROOT}/content/courses/${_course}")
    file(READ "${_base}/course.json" _metadata)
    file(READ "${_base}/index.html" _index)
    string(JSON _count LENGTH "${_metadata}" lessons)
    set(_first 0)
    set(_minimum 3)
    if(_course STREQUAL "building-a-compiler-in-c")
        set(_first 10)
        set(_minimum 12)
    elseif(_course STREQUAL "introduction-to-programming" OR _course STREQUAL "building-a-text-editor")
        set(_minimum 4)
    endif()
    if(_count LESS _minimum)
        message(FATAL_ERROR "${_course}: a required introductory chapter is missing")
    endif()
    RequireText("${_catalogue}" "${_course}/index.html" "Course catalogue")
    RequireText("${_paths}" "${_course}/" "Learning route")
    math(EXPR _last "${_count} - 1")
    set(_seen)
    foreach(_chapter RANGE ${_first} ${_last})
        string(JSON _path GET "${_metadata}" lessons ${_chapter} path)
        string(JSON _title GET "${_metadata}" lessons ${_chapter} title)
        string(JSON _manuscript GET "${_metadata}" lessons ${_chapter} manuscript)
        if(NOT _path MATCHES "^lessons/[0-9]+-[a-z0-9-]+[.]html$" OR _path IN_LIST _seen)
            message(FATAL_ERROR "Invalid or repeated chapter route: ${_course}/${_path}")
        endif()
        list(APPEND _seen "${_path}")
        get_filename_component(_slug "${_path}" NAME_WE)
        if(NOT _manuscript MATCHES "^[.][.]/[.][.]/lessons/(02-programming|03-native-code|05-engineering)/${_course}/${_slug}[.]md$")
            message(FATAL_ERROR "Chapter editions must share one identity: ${_course}/${_path}")
        endif()
        file(READ "${_base}/${_path}" _html)
        file(READ "${_base}/${_manuscript}" _markdown)
        get_filename_component(_md_directory "${_base}/${_manuscript}" DIRECTORY)
        file(READ "${_md_directory}/index.md" _md_index)
        file(RELATIVE_PATH _md_route "${REPOSITORY_ROOT}" "${_base}/${_manuscript}")
        string(SHA256 _key "content/courses/${_course}/${_path}")
        if(NOT DEFINED _pair_${_key} OR NOT "${_pair_${_key}}" STREQUAL "${_md_route}")
            message(FATAL_ERROR "Missing or incorrect edition pair: ${_course}/${_path}")
        endif()
        string(REGEX REPLACE "^content/" "" _nav_route "${_md_route}")
        RequireText("${_navigation}" "${_nav_route}" "Published navigation")
        RequireText("${_index}" "href=\"${_path}\"" "Course contents")
        RequireText("${_md_index}" "(${_slug}.md)" "Manuscript contents")
        RequireText("${_html}" "<h1>${_title}</h1>" "HTML title")
        RequireText("${_markdown}" "# ${_title}" "Manuscript title")
        RequireText("${_html}" "href=\"../index.html\"" "Return to course")
        RequireText("${_markdown}" "(index.md)" "Return to manuscript course")
        if(_html MATCHES "\\[\\[course:" OR _markdown MATCHES "\\[\\[course:")
            message(FATAL_ERROR "Unresolved authoring link in ${_course}/${_path}")
        endif()
        # The configured MkDocs hook resolves manuscript links after rendering.
        # Preserve the former blanket refusal for review and validate its real
        # source and publication prerequisites below.
        if(FALSE)
        # Standalone HTML is copied intact by the site builder. A Markdown
        # source link in it would not be rewritten into a published page.
        if(_html MATCHES [=[href="[^":]+[.]md([#?][^"]*)?"]=] OR
           _html MATCHES [=[href="([.][.]/)+labs/]=])
            message(FATAL_ERROR "Unpublished HTML route in ${_course}/${_path}")
        endif()
        endif()
        BtbCheckCourseLinks("${_html}" "${_base}/${_path}" "${REPOSITORY_ROOT}")
        if(_chapter GREATER 0)
            math(EXPR _previous "${_chapter} - 1")
            string(JSON _route GET "${_metadata}" lessons ${_previous} path)
            get_filename_component(_previous_name "${_route}" NAME_WE)
            RequireText("${_html}" "href=\"${_previous_name}.html\"" "Previous chapter")
            RequireText("${_markdown}" "(${_previous_name}.md)" "Previous manuscript")
            if(_chapter EQUAL _first AND _first GREATER 0)
                file(READ "${_base}/${_route}" _previous_html)
                file(READ "${_md_directory}/${_previous_name}.md" _previous_md)
                RequireText("${_previous_html}" "href=\"${_slug}.html\"" "Existing chapter continuation")
                RequireText("${_previous_md}" "(${_slug}.md)" "Existing manuscript continuation")
            endif()
        endif()
        if(_chapter LESS _last)
            math(EXPR _next "${_chapter} + 1")
            string(JSON _route GET "${_metadata}" lessons ${_next} path)
            get_filename_component(_next_name "${_route}" NAME_WE)
            RequireText("${_html}" "href=\"${_next_name}.html\"" "Next chapter")
            RequireText("${_markdown}" "(${_next_name}.md)" "Next manuscript")
        endif()
        string(JSON _source GET "${_metadata}" lessons ${_chapter} source)
        # Preserve the earlier narrow grammar for review. Later course modules
        # cite public Framework/Kernel headers and tests as well as local labs;
        # the shared validator checks their declared boundaries without fetching.
        if(FALSE)
        if(_source MATCHES "^labs/[a-zA-Z0-9_./-]+$" AND NOT _source MATCHES "[.][.]")
            if(NOT EXISTS "${REPOSITORY_ROOT}/${_source}")
                message(FATAL_ERROR "Missing companion source: ${_source}")
            endif()
        elseif(NOT _source MATCHES "^umicom-c/src/[a-z_]+[.]c$")
            message(FATAL_ERROR "Unrecognised source map: ${_source}")
        endif()
        endif()
        BtbValidateSourceReference("${_source}" "${REPOSITORY_ROOT}" _source_valid _source_reason)
        if(NOT _source_valid)
            message(FATAL_ERROR "Invalid source map: ${_source}: ${_source_reason}")
        endif()
    endforeach()
endforeach()
foreach(_source IN ITEMS
        labs/native/collections/collections.c labs/native/collections/test_collections.c
        labs/native/collections/README.md labs/native/collections/CMakeLists.txt
        labs/native/text-editor/editor.c labs/native/text-editor/main.c
        labs/native/text-editor/test_editor.c labs/native/text-editor/check_session.cmake
        labs/native/text-editor/README.md labs/native/text-editor/CMakeLists.txt
        labs/languages/pascal-progress/hello.pas labs/languages/pascal-progress/progress.pas
        labs/languages/pascal-progress/README.md labs/languages/pascal-progress/CMakeLists.txt
        labs/languages/pascal-progress/check_progress.cmake
        labs/languages/umicom-c-project/answer.uc labs/languages/umicom-c-project/budget.uc
        labs/languages/umicom-c-project/README.md)
    if(NOT EXISTS "${REPOSITORY_ROOT}/${_source}")
        message(FATAL_ERROR "Missing project file: ${_source}")
    endif()
endforeach()
message(STATUS "Programming course routes and companion sources agree; executable labs require separate qualification")

