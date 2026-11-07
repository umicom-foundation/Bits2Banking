#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: tests/content_integrity/check_community_route.cmake
#
# PURPOSE:
#   Check that every community route entry has reachable teaching editions.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.22)
if(NOT DEFINED REPOSITORY_ROOT)
    message(FATAL_ERROR "REPOSITORY_ROOT is required")
endif()
set(_community "${REPOSITORY_ROOT}/content/community")
file(READ "${_community}/route.json" _route)
string(JSON _count LENGTH "${_route}" lessons)
if(_count EQUAL 0)
    message(FATAL_ERROR "The community route has no lessons")
endif()
math(EXPR _last "${_count} - 1")
set(_identities)
foreach(_index RANGE 0 ${_last})
    string(JSON _id GET "${_route}" lessons ${_index} id)
    if(_id IN_LIST _identities)
        message(FATAL_ERROR "Duplicate lesson identity: ${_id}")
    endif()
    list(APPEND _identities "${_id}")
    foreach(_edition IN ITEMS lesson handout video message relatedCourse)
        string(JSON _path GET "${_route}" lessons ${_index} ${_edition})
        if(NOT EXISTS "${_community}/${_path}" OR IS_DIRECTORY "${_community}/${_path}")
            message(FATAL_ERROR "Missing ${_edition} for ${_id}: ${_path}")
        endif()
    endforeach()
    # Markdown and a handout must not claim the same published URL.
    string(JSON _md GET "${_route}" lessons ${_index} lesson)
    string(JSON _html GET "${_route}" lessons ${_index} handout)
    string(REGEX REPLACE "[.]md$" ".html" _md_url "${_md}")
    if(_md_url STREQUAL _html)
        message(FATAL_ERROR "Competing Markdown/HTML page output for ${_id}")
    endif()
endforeach()

# Check local destinations in all editions, including downloadable source.
# External services are not contacted by this offline navigation check.
file(GLOB_RECURSE _pages "${_community}/*.md" "${_community}/*.html")
foreach(_page IN LISTS _pages)
    file(READ "${_page}" _text)
    get_filename_component(_directory "${_page}" DIRECTORY)
    # CMake lists track square-bracket balance. Strip the Markdown delimiter
    # before collecting links so separate destinations remain separate items.
    # Retain the earlier parser for review of this list-parsing correction.
    if(FALSE)
        string(REGEX MATCHALL [=[(href|src)="[^"]+"|\]\([^
    )]+\)]=] _links "${_text}")
        foreach(_link IN LISTS _links)
            if(_link MATCHES [=[^(href|src)="([^"]+)"]=])
                set(_destination "${CMAKE_MATCH_2}")
            else()
                string(REGEX REPLACE [=[^\]\((.*)\)$]=] "\\1" _destination "${_link}")
            endif()
            endforeach()
    endif()
    string(REPLACE "](" "UMICOM_LINK(" _scan "${_text}")
    string(REGEX MATCHALL [=[(href|src)="[^"]+"|UMICOM_LINK\([^
)]+\)]=] _links "${_scan}")
    foreach(_link IN LISTS _links)
        if(_link MATCHES [=[^(href|src)="([^"]+)"]=])
            set(_destination "${CMAKE_MATCH_2}")
        else()
            string(REGEX REPLACE [=[^UMICOM_LINK\((.*)\)$]=] "\\1" _destination "${_link}")
        endif()
        if(_destination MATCHES "^[A-Za-z][A-Za-z0-9+.-]*:" OR _destination MATCHES "^#")
            continue()
        endif()
        string(REGEX REPLACE "[?#].*$" "" _destination "${_destination}")
        if(NOT EXISTS "${_directory}/${_destination}")
            message(FATAL_ERROR "Broken community link in ${_page}: ${_destination}")
        endif()
    endforeach()
endforeach()
message(STATUS "Community route: ${_count} lessons and all local edition links are reachable")
