#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: tests/content_integrity/course_links.cmake
#
# PURPOSE:
#   Validate manuscript source links against the existing publication adapter and content root.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

# Check the source side of the existing MkDocs publication adapter. This is
# deliberately not a renderer: the owner must still build and inspect the site.
# Historical HTML comments are not active links and cannot satisfy this check.
function(BtbCheckCourseLinks document source repository_root)
    set(_remaining "${document}")
    set(_active "")
    while(TRUE)
        string(FIND "${_remaining}" "<!--" _start)
        if(_start LESS 0)
            string(APPEND _active "${_remaining}")
            break()
        endif()
        string(SUBSTRING "${_remaining}" 0 ${_start} _prefix)
        string(APPEND _active "${_prefix}")
        math(EXPR _after "${_start} + 4")
        string(SUBSTRING "${_remaining}" ${_after} -1 _tail)
        string(FIND "${_tail}" "-->" _end)
        if(_end LESS 0)
            message(FATAL_ERROR "Unclosed course HTML comment: ${source}")
        endif()
        math(EXPR _after "${_end} + 3")
        string(SUBSTRING "${_tail}" ${_after} -1 _remaining)
    endwhile()
    get_filename_component(_source_directory "${source}" DIRECTORY)
    get_filename_component(_content "${repository_root}/content" ABSOLUTE)
    string(REGEX MATCHALL [=[href=["'][^"']*["']]=] _links "${_active}")
    foreach(_attribute IN LISTS _links)
        string(REGEX REPLACE [=[^href=["']|["']$]=] "" _url "${_attribute}")
        if(_url MATCHES "^file:")
            message(FATAL_ERROR "A course link exposes a local file URL: ${source}")
        endif()
        if(_url MATCHES "^[A-Za-z][A-Za-z0-9+.-]*:" OR _url MATCHES "^//")
            continue()
        endif()
        string(REGEX REPLACE "[#?].*$" "" _target "${_url}")
        # Repository lab files are not part of docs_dir. A source-reading link
        # to them must use the public repository rather than a guessed site URL.
        if(_target MATCHES "^([.][.]/)+labs/")
            message(FATAL_ERROR "Unpublished repository source link: ${source}: ${_url}")
        endif()
        if(NOT _target MATCHES "[.]md$")
            continue()
        endif()
        # The authored lesson convention uses plain relative source paths.
        # Encoded/absolute manuscript URLs need a separately reviewed route.
        if(NOT _target MATCHES "^[A-Za-z0-9_./-]+[.]md$" OR _target MATCHES "^/")
            message(FATAL_ERROR "Unsupported manuscript source URL: ${source}: ${_url}")
        endif()
        get_filename_component(_absolute "${_source_directory}/${_target}" ABSOLUTE)
        file(RELATIVE_PATH _within "${_content}" "${_absolute}")
        if(_within MATCHES "^[.][.](/|$)" OR IS_ABSOLUTE "${_within}" OR
                NOT EXISTS "${_absolute}" OR IS_DIRECTORY "${_absolute}")
            message(FATAL_ERROR "Missing or out-of-content manuscript: ${source}: ${_url}")
        endif()
        # Resolve existing files as well, so an in-tree link cannot escape
        # through a directory junction or symbolic link during publication.
        file(REAL_PATH "${_absolute}" _resolved)
        file(REAL_PATH "${_content}" _resolved_content)
        file(RELATIVE_PATH _within "${_resolved_content}" "${_resolved}")
        if(_within MATCHES "^[.][.](/|$)" OR IS_ABSOLUTE "${_within}")
            message(FATAL_ERROR "Manuscript resolves outside content: ${source}")
        endif()
        if(NOT EXISTS "${repository_root}/hooks/course_source_links.py" OR
                NOT EXISTS "${repository_root}/mkdocs.yml")
            message(FATAL_ERROR "The manuscript publication adapter is missing")
        endif()
        file(READ "${repository_root}/mkdocs.yml" _configuration)
        if(NOT _configuration MATCHES "(^|\n)hooks:[ \t]*\r?\n[ \t]+-[ \t]+hooks/course_source_links[.]py([ \t\r]*\n|$)")
            message(FATAL_ERROR "Manuscript links require the configured course_source_links hook")
        endif()
    endforeach()
endfunction()
