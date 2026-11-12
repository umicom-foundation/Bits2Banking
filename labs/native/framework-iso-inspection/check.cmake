#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-iso-inspection/check.cmake
#
# PURPOSE:
#   Verify success and refusal observations from the installed SDK lesson client.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------


if(NOT DEFINED TOOL OR NOT DEFINED CASE)
    message(FATAL_ERROR "TOOL and CASE are required")
endif()
# The original six-case expectations are retained for review. The active table
# also checks prefix read counts and distinguishes historical flags on refusal.
#[=[
set(_exit 0)
set(_status 0)
set(_flags "ISO9660: 1; El Torito: 1; BIOS: 1; EFI: 0")
if(CASE STREQUAL "efi-zero" OR CASE STREQUAL "efi-one")
    set(_flags "ISO9660: 1; El Torito: 1; BIOS: 0; EFI: 1")
elseif(CASE STREQUAL "endian" OR CASE STREQUAL "bios-zero" OR CASE STREQUAL "read-failure")
    set(_exit 1)
    set(_status 9)
    if(CASE STREQUAL "read-failure")
        set(_status 8)
    endif()
    set(_flags "ISO9660: 0; El Torito: 0; BIOS: 0; EFI: 0")
elseif(NOT CASE STREQUAL "bios")
    message(FATAL_ERROR "Unknown inspection case")
endif()
]=]
set(_exit 0)
set(_status 0)
set(_reads "")
set(_flags "ISO9660: 1; El Torito: 1; BIOS: 1; EFI: 0")
if(CASE STREQUAL "efi-zero" OR CASE STREQUAL "efi-one")
    set(_flags "ISO9660: 1; El Torito: 1; BIOS: 0; EFI: 1")
elseif(CASE STREQUAL "prefix-short" OR CASE STREQUAL "prefix-unknown" OR CASE STREQUAL "retained-noniso")
    set(_flags "ISO9660: 0; El Torito: 0; BIOS: 0; EFI: 0")
    set(_reads 1)
    if(CASE STREQUAL "prefix-short")
        set(_reads 0)
    endif()
elseif(CASE STREQUAL "endian" OR CASE STREQUAL "bios-zero" OR CASE STREQUAL "read-failure"
    OR CASE STREQUAL "prefix-truncated" OR CASE STREQUAL "prefix-sector"
    OR CASE STREQUAL "prefix-read-failure" OR CASE STREQUAL "retained-error")
    set(_exit 1)
    set(_status 9)
    if(CASE STREQUAL "read-failure" OR CASE STREQUAL "prefix-read-failure")
        set(_status 8)
    endif()
    set(_flags "ISO9660: 0; El Torito: 0; BIOS: 0; EFI: 0")
    if(CASE STREQUAL "retained-error")
        set(_flags "ISO9660: 1; El Torito: 1; BIOS: 1; EFI: 0")
    endif()
    if(CASE MATCHES "^prefix-" OR CASE STREQUAL "retained-error")
        set(_reads 1)
    endif()
elseif(NOT CASE STREQUAL "bios")
    message(FATAL_ERROR "Unknown inspection case")
endif()
execute_process(COMMAND "${TOOL}" "${CASE}" RESULT_VARIABLE _result
    OUTPUT_VARIABLE _output ERROR_VARIABLE _error ENCODING UTF-8 TIMEOUT 8)
if(NOT _result STREQUAL "${_exit}")
    message(FATAL_ERROR "Unexpected exit ${_result}; expected ${_exit}\n${_output}\n${_error}")
endif()
string(REPLACE "\r\n" "\n" _output "${_output}")
# Keep the earlier loop for review. Named strings preserve semicolons in the
# complete flag line instead of relying on list expansion of diagnostic text.
#[[
foreach(_expected IN ITEMS "Status: ${_status}\n" "${_flags}\n"
    "Synthetic memory inspection only; no device, producer or boot execution.")
    string(FIND "${_output}" "${_expected}" _found)
    if(_found LESS 0)
        message(FATAL_ERROR "Missing expected observation: ${_expected}\n${_output}")
    endif()
endforeach()
]]
set(_status_line "Status: ${_status}\n")
set(_flags_line "${_flags}\n")
set(_disclaimer "Synthetic memory inspection only; no device, producer or boot execution.")
foreach(_field IN ITEMS _status_line _flags_line _disclaimer)
    string(FIND "${_output}" "${${_field}}" _found)
    if(_found LESS 0)
        message(FATAL_ERROR "Missing expected observation: ${${_field}}\n${_output}")
    endif()
endforeach()


# Count observations independently of status; a parser that skips the prefix
# must not satisfy the truncated-source case merely by returning a refusal.
if(NOT _reads STREQUAL "")
    string(FIND "${_output}" "Read callbacks: ${_reads}\n" _found)
    if(_found LESS 0)
        message(FATAL_ERROR "Unexpected callback count\n${_output}")
    endif()
endif()
if(CASE STREQUAL "retained-error")
    string(FIND "${_output}" "Flags retained from prior inspection; they do not describe the refused source." _found)
    if(_found LESS 0)
        message(FATAL_ERROR "Missing retained-observation explanation")
    endif()
endif()
