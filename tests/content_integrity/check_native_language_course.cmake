# Umicom Bits2Banking
# File: tests/content_integrity/check_native_language_course.cmake
# 
# PURPOSE:
# Verify complete native-language pack resources and their current identities.
# 
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
# 
# LICENCE:
# MIT
# 
cmake_minimum_required(VERSION 3.24)
if(NOT DEFINED REPOSITORY_ROOT)
    message(FATAL_ERROR "Supply REPOSITORY_ROOT")
endif()
file(READ "${REPOSITORY_ROOT}/learning-packs/native-language-interoperability.json" _pack)
string(JSON _count LENGTH "${_pack}" resources)
if(_count LESS 1 OR _count GREATER 256)
    message(FATAL_ERROR "Native course pack exceeds its resource contract")
endif()
math(EXPR _last "${_count} - 1")
set(_seen "")
foreach(_i RANGE 0 ${_last})
    string(JSON _path GET "${_pack}" resources ${_i} path)
    string(JSON _hash GET "${_pack}" resources ${_i} sha256)
    if(IS_ABSOLUTE "${_path}" OR _path MATCHES "(^|/)\.\.(/|$)" OR _path IN_LIST _seen)
        message(FATAL_ERROR "Duplicate or escaping course resource: ${_path}")
    endif()
    list(APPEND _seen "${_path}")
    if(NOT EXISTS "${REPOSITORY_ROOT}/${_path}")
        message(FATAL_ERROR "Missing native course resource: ${_path}")
    endif()
    file(SHA256 "${REPOSITORY_ROOT}/${_path}" _actual)
    if(NOT _actual STREQUAL _hash)
        message(FATAL_ERROR "Review and refresh the course digest: ${_path}")
    endif()
endforeach()
foreach(_required IN ITEMS
    labs/native/framework-activity/activity.c
    labs/native/activity-adapters/bridge.h
    labs/native/cpp-activity-client/main.cpp
    labs/languages/rust-activity/main.rs
    labs/languages/zig-activity/main.zig
    labs/languages/fortran-activity/main.f90
    labs/languages/d-activity/main.d
    labs/languages/odin-activity/main.odin
    labs/languages/nim-activity/main.nim
    labs/native/assembly-activity/forward.S)
    if(NOT _required IN_LIST _seen)
        message(FATAL_ERROR "Required language example omitted from pack: ${_required}")
    endif()
endforeach()
message(STATUS "Native language course: ${_count} complete resources have matching hashes")
