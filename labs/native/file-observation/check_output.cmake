#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/file-observation/check_output.cmake
#
# PURPOSE:
#   Check observation JSON against known bytes and refusal cases.
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
string(RANDOM LENGTH 16 ALPHABET 0123456789abcdef _id)
set(_directory "${CMAKE_CURRENT_BINARY_DIR}/observation-${CASE}-${_id}")
if(EXISTS "${_directory}")
    message(FATAL_ERROR "Fixture directory already exists")
endif()
file(MAKE_DIRECTORY "${_directory}")
set(_path "${_directory}/input.bin")
set(_contents "abc")
set(_expected 0)
if(CASE STREQUAL "empty")
    set(_contents "")
elseif(CASE STREQUAL "unicode-path")
    set(_path "${_directory}/café input.bin")
elseif(CASE STREQUAL "missing" OR CASE STREQUAL "relative")
    set(_expected 1)
elseif(NOT CASE STREQUAL "ascii")
    message(FATAL_ERROR "Unknown case")
endif()
if(NOT CASE STREQUAL "missing")
    file(WRITE "${_path}" "${_contents}")
endif()
if(CASE STREQUAL "relative")
    set(_argument "input.bin")
else()
    set(_argument "${_path}")
endif()
execute_process(COMMAND "${TOOL}" "${_argument}" WORKING_DIRECTORY "${_directory}"
    RESULT_VARIABLE _status OUTPUT_VARIABLE _json ERROR_VARIABLE _diagnostic TIMEOUT 15)
if(NOT "${_status}" STREQUAL "${_expected}")
    message(FATAL_ERROR "Unexpected status ${_status}: ${_diagnostic}")
endif()
if(_expected EQUAL 0)
    string(SHA256 _expected_hash "${_contents}")
    string(LENGTH "${_contents}" _expected_length)
    string(JSON _hash GET "${_json}" files 0 sha256)
    string(JSON _length GET "${_json}" files 0 bytes)
    string(JSON _reported_path GET "${_json}" files 0 path)
    string(JSON _qualified GET "${_json}" qualificationPassed)
    if(NOT _hash STREQUAL _expected_hash OR NOT _length EQUAL _expected_length OR
        NOT _reported_path STREQUAL _path OR _qualified OR NOT _diagnostic STREQUAL "")
        message(FATAL_ERROR "Observation does not match the fixed input")
    endif()
else()
    if(NOT _json STREQUAL "" OR _diagnostic STREQUAL "")
        message(FATAL_ERROR "Refusal must report a diagnostic without partial JSON")
    endif()
endif()
if(EXISTS "${_path}")
    file(READ "${_path}" _after)
    if(NOT _after STREQUAL _contents)
        message(FATAL_ERROR "Selected source was modified")
    endif()
endif()
