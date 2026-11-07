# -----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/text-editor/check_session.cmake
#
# PURPOSE:
#   Check real command input, exclusive saving and unchanged existing files.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
# -----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.24)
if(NOT DEFINED PROGRAM OR NOT DEFINED WORK_ROOT)
    message(FATAL_ERROR "PROGRAM and WORK_ROOT are required")
endif()
# Each run owns a fresh evidence directory; never erase a previous run.
string(RANDOM LENGTH 20 ALPHABET 0123456789abcdef _id)
set(_work "${WORK_ROOT}/${_id}")
if(EXISTS "${_work}")
    message(FATAL_ERROR "Evidence directory already exists; retry")
endif()
file(MAKE_DIRECTORY "${_work}")
set(_output "${_work}/my note.txt")
file(WRITE "${_work}/session.txt"
    "append ac\ninsert 1 b\nerase 1 1\nundo\nshow\nsave ${_output}\nquit\n")
execute_process(COMMAND "${PROGRAM}" INPUT_FILE "${_work}/session.txt"
    RESULT_VARIABLE _result OUTPUT_VARIABLE _stdout ERROR_VARIABLE _stderr TIMEOUT 5)
if(NOT _result STREQUAL "0" OR NOT _stdout MATCHES "TEXT: abc" OR NOT EXISTS "${_output}")
    message(FATAL_ERROR "Editor session failed: ${_result}\n${_stdout}\n${_stderr}")
endif()
file(READ "${_output}" _saved)
if(NOT _saved STREQUAL "abc")
    message(FATAL_ERROR "Saved text differs")
endif()
file(WRITE "${_work}/refusal.txt" "append replacement\nsave ${_output}\ndiscard\n")
execute_process(COMMAND "${PROGRAM}" INPUT_FILE "${_work}/refusal.txt"
    RESULT_VARIABLE _result OUTPUT_VARIABLE _stdout ERROR_VARIABLE _stderr TIMEOUT 5)
file(READ "${_output}" _saved)
if(NOT _result STREQUAL "1" OR NOT _saved STREQUAL "abc" OR NOT _stdout MATCHES "ERROR")
    message(FATAL_ERROR "Existing-file preservation failed: ${_result}\n${_stdout}")
endif()
file(WRITE "${_work}/invalid.txt" "append abc\nerase -1 1\nshow\ndiscard\n")
execute_process(COMMAND "${PROGRAM}" INPUT_FILE "${_work}/invalid.txt"
    RESULT_VARIABLE _result OUTPUT_VARIABLE _stdout ERROR_VARIABLE _stderr TIMEOUT 5)
if(NOT _result STREQUAL "1" OR NOT _stdout MATCHES "TEXT: abc")
    message(FATAL_ERROR "Invalid command changed the document: ${_result}\n${_stdout}")
endif()
# Reject overflowing numbers and a whole oversized line, then resume at the
# next command. The saved oracle proves neither rejected prefix was applied.
string(REPEAT "x" 2200 _long)
file(WRITE "${_work}/boundaries.txt"
    "append abc\ninsert 999999999999999999999999999999999999999 x\nerase 0 1junk\nappend ${_long}\nshow\nsave ${_work}/bounded.txt\nquit\n")
execute_process(COMMAND "${PROGRAM}" INPUT_FILE "${_work}/boundaries.txt"
    RESULT_VARIABLE _result OUTPUT_VARIABLE _stdout ERROR_VARIABLE _stderr TIMEOUT 5)
if(NOT _result STREQUAL "1" OR NOT EXISTS "${_work}/bounded.txt")
    message(FATAL_ERROR "Command boundary rejection failed: ${_result}\n${_stdout}\n${_stderr}")
endif()
file(READ "${_work}/bounded.txt" _saved)
if(NOT _saved STREQUAL "abc")
    message(FATAL_ERROR "Rejected input changed saved content")
endif()
