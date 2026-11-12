#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: tests/content_integrity/check_studio_learning_collection.cmake
#
# PURPOSE:
#   Keep the reviewed Studio collection and its exact resource digests together.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#---------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.22)
if(NOT DEFINED REPOSITORY_ROOT)
    get_filename_component(REPOSITORY_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
endif()
set(_root "${REPOSITORY_ROOT}/content/courses/framework-and-finance")
file(READ "${_root}/collection.json" _collection)
file(READ "${_root}/learning-pack.json" _manifest)

# Studio selects this nested collection, independently of learning-packs/*.json.
# Check the committed edition here as well as at Framework admission. This test
# never rewrites a manifest or approves content as a side effect of a build.
foreach(_key IN ITEMS version id title product locale revision compatibility)
    string(JSON _declared GET "${_collection}" ${_key})
    string(JSON _published GET "${_manifest}" ${_key})
    if(NOT _declared STREQUAL _published)
        message(FATAL_ERROR "Studio collection metadata differs: ${_key}")
    endif()
endforeach()
string(JSON _count LENGTH "${_collection}" resources)
string(JSON _published_count LENGTH "${_manifest}" resources)
if(NOT _count EQUAL _published_count OR _count LESS 1 OR _count GREATER 256)
    message(FATAL_ERROR "Studio collection resource count differs or exceeds native bounds")
endif()
set(_mismatches "")
math(EXPR _last "${_count} - 1")
foreach(_index RANGE 0 ${_last})
    foreach(_key IN ITEMS id title topic kind path)
        string(JSON _declared GET "${_collection}" resources ${_index} ${_key})
        string(JSON _published GET "${_manifest}" resources ${_index} ${_key})
        if(NOT _declared STREQUAL _published)
            message(FATAL_ERROR "Studio resource ${_index} metadata differs: ${_key}")
        endif()
    endforeach()
    string(JSON _path GET "${_manifest}" resources ${_index} path)
    string(JSON _expected GET "${_manifest}" resources ${_index} sha256)
    if(IS_ABSOLUTE "${_path}" OR _path MATCHES [=[(^|/)[.][.]?(/|$)|[\\:;]]=])
        message(FATAL_ERROR "Non-relative Studio resource: ${_path}")
    endif()
    file(SHA256 "${_root}/${_path}" _actual)
    if(NOT _actual STREQUAL _expected)
        list(APPEND _mismatches "${_path}")
    endif()
endforeach()
if(_mismatches)
    list(JOIN _mismatches "\n  " _details)
    message(FATAL_ERROR
        "Studio collection digests are stale:\n  ${_details}\n"
        "Review the changed resources and deliver their matching manifest together.")
endif()
message(STATUS "Studio collection metadata and ${_count} exact resource digests match")
