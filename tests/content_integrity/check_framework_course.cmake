#-----------------------------------------------------------------------------
# Bits2Banking
# File: tests/content_integrity/check_framework_course.cmake
#
# PURPOSE:
#   Check the Framework course catalogue, reading sources and lesson navigation.
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
set(_course "${REPOSITORY_ROOT}/content/courses/umicom-development")
set(_manuscripts "${REPOSITORY_ROOT}/content/lessons/umicom-development")
file(READ "${_course}/course.json" _catalogue)
file(READ "${_course}/index.html" _home)
file(READ "${_manuscripts}/index.md" _index)
file(READ "${REPOSITORY_ROOT}/mkdocs.yml" _site_navigation)
string(JSON _count LENGTH "${_catalogue}" lessons)
# The twelve-chapter boundary remains here for review. The current catalogue
# also requires the reader chapter and its source-backed ownership exercise.
if(FALSE)
if(_count LESS 12)
    message(FATAL_ERROR "The Framework course is missing required SDK, build, evidence, command-identity, shutdown, service-registration or copied-discovery chapters")
endif()
endif()
# Keep the earlier reader-only boundary for review; the practice chapter now
# extends the same catalogue and must remain reachable from its predecessor.
if(FALSE)
if(_count LESS 13)
    message(FATAL_ERROR "The Framework course is missing a required offline-reader chapter")
endif()
endif()
if(_count LESS 14)
    message(FATAL_ERROR "The Framework course is missing its practice-copy chapter")
endif()
function(RequireText text fragment context)
    string(FIND "${text}" "${fragment}" _found)
    if(_found EQUAL -1)
        message(FATAL_ERROR "${context}: missing ${fragment}")
    endif()
endfunction()
math(EXPR _last "${_count} - 1")
set(_seen)
set(_reading_titles)
foreach(_i RANGE 0 ${_last})
    string(JSON _path GET "${_catalogue}" lessons ${_i} path)
    string(JSON _title GET "${_catalogue}" lessons ${_i} title)
    string(JSON _manuscript GET "${_catalogue}" lessons ${_i} manuscript)
    if(NOT _path MATCHES "^lessons/[0-9]+-[a-z-]+[.]html$" OR _path IN_LIST _seen)
        message(FATAL_ERROR "Invalid or duplicated Framework lesson route: ${_path}")
    endif()
    list(APPEND _seen "${_path}")
    get_filename_component(_name "${_path}" NAME_WE)
    if(NOT _manuscript STREQUAL "../../lessons/umicom-development/${_name}.md")
        message(FATAL_ERROR "Lesson and manuscript must share their published identity: ${_path}")
    endif()
    file(READ "${_course}/${_path}" _page)
    file(READ "${_manuscripts}/${_name}.md" _markdown)
    # Standalone HTML is copied as a web asset; Markdown link rewriting does
    # not apply inside it. Source-code links must not escape docs_dir.
    if(_page MATCHES [=[href="[^":]+[.]md([#?][^"]*)?"]=] OR
       _page MATCHES [=[href="([.][.]/)+labs/]=])
        message(FATAL_ERROR "A standalone course page uses an unpublished source route: ${_path}")
    endif()
    RequireText("${_home}" "href=\"${_path}\"" "Course contents")
    RequireText("${_index}" "(${_name}.md)" "Manuscript contents")
    RequireText("${_site_navigation}" "lessons/umicom-development/${_name}.md" "Site navigation")
    RequireText("${_page}" "<h1>${_title}</h1>" "${_path}")
    RequireText("${_markdown}" "# ${_title}" "${_name}.md")
    RequireText("${_page}" "href=\"../index.html\"" "${_path} return route")
    string(JSON _kind ERROR_VARIABLE _kind_error GET "${_catalogue}" lessons ${_i} kind)
    if(_kind_error OR NOT _kind STREQUAL "source-reading")
        continue()
    endif()
    list(APPEND _reading_titles "${_title}")
    string(JSON _source GET "${_catalogue}" lessons ${_i} source)
    # Retain the Framework-only source rule for review. Application integration
    # chapters also teach the actual Studio consumer, so admit that named
    # repository explicitly while keeping arbitrary source origins excluded.
    if(FALSE)
    if(NOT _source MATCHES "^https://github[.]com/umicom-foundation/umicom-framework/blob/main/")
        message(FATAL_ERROR "A Framework reading chapter needs a published Framework source: ${_path}")
    endif()
    endif()
    if(NOT _source MATCHES "^https://github[.]com/umicom-foundation/(umicom-framework|umicom-studio-ide-module)/blob/main/[A-Za-z0-9_./-]+$")
        message(FATAL_ERROR "A reading chapter needs a published Framework or Studio source: ${_path}")
    endif()
    RequireText("${_page}" "href=\"${_source}\"" "${_path} source link")
    RequireText("${_markdown}" "(${_source})" "${_name}.md source link")
    RequireText("${_page}" "<details>" "${_path} self-check")
    RequireText("${_markdown}" "<details>" "${_name}.md self-check")
    if(_i GREATER 0)
        math(EXPR _previous "${_i} - 1")
        string(JSON _route GET "${_catalogue}" lessons ${_previous} path)
        get_filename_component(_route "${_route}" NAME)
        RequireText("${_page}" "href=\"${_route}\"" "${_path} previous route")
    endif()
    if(_i LESS _last)
        math(EXPR _next "${_i} + 1")
        string(JSON _route GET "${_catalogue}" lessons ${_next} path)
        get_filename_component(_route "${_route}" NAME)
        RequireText("${_page}" "href=\"${_route}\"" "${_path} next route")
    endif()
endforeach()
# Require named concepts, rather than accepting an arbitrary lesson count.
foreach(_required IN ITEMS "Use an installed Framework SDK" "Build only what changed" "Read build and test evidence" "Understand which program a test runs" "Close background work safely" "Register shared application services" "Inspect application services" "Build an offline learning reader" "Copy examples without overwriting your work" "Connect commands to helpful guides" "Store checkpoints on a worker" "Remember locations without inheriting trust" "Preserve structure when reading code" "Connect keyboard and button help" "Follow protocol message boundaries" "Carry image pixels from a worker to a window" "Find text with shared Framework services" "Validate a tool connection" "Search verified learning resources" "Open search results without losing your place" "Understand waiting and timeouts" "Remember projects without deleting their files" "Keep test data separate from your work" "Understand skipped tests and host coverage")
    if(NOT _required IN_LIST _reading_titles)
        message(FATAL_ERROR "Required Framework reading chapter is missing: ${_required}")
    endif()
endforeach()
file(READ "${_course}/lessons/05-introduction-to-gtk4.html" _bridge)
RequireText("${_bridge}" "href=\"06-use-an-installed-sdk.html\"" "GTK lesson continuation")
message(STATUS "Framework course catalogue and source-reading routes agree; code examples require separate qualification")
