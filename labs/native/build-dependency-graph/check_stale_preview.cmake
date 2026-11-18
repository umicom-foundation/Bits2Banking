#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/build-dependency-graph/check_stale_preview.cmake
#
# PURPOSE:
#   Observe a retained executable after a deliberate failed rebuild in a fresh child directory.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.26)
foreach(_required SOURCE WORK COMPILER MAKE_PROGRAM GENERATOR CTEST_PROGRAM)
    if(NOT DEFINED ${_required} OR "${${_required}}" STREQUAL "")
        message(FATAL_ERROR "Missing exercise input: ${_required}")
    endif()
endforeach()
# CMake produces executables under configuration directories for multi-config
# generators. This exercise deliberately supports the documented Ninja path.
if(NOT GENERATOR STREQUAL "Ninja")
    message(FATAL_ERROR "The stale-preview exercise requires the Ninja generator")
endif()
string(RANDOM LENGTH 16 ALPHABET 0123456789abcdef _identity)
set(_build "${WORK}/attempt-${_identity}")
file(MAKE_DIRECTORY "${_build}")
execute_process(COMMAND "${CMAKE_COMMAND}" -S "${SOURCE}" -B "${_build}" -G Ninja
    "-DCMAKE_C_COMPILER=${COMPILER}" "-DCMAKE_MAKE_PROGRAM=${MAKE_PROGRAM}"
    -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON -DLESSON_REFUSE_PREVIEW_BUILD=OFF
    RESULT_VARIABLE _configured OUTPUT_VARIABLE _out ERROR_VARIABLE _err)
file(WRITE "${_build}/configure.log" "${_out}${_err}")
if(NOT _configured EQUAL 0)
    message(FATAL_ERROR "Initial configuration failed: ${_build}/configure.log")
endif()
execute_process(COMMAND "${CMAKE_COMMAND}" --build "${_build}" --target lesson-note-preview
    RESULT_VARIABLE _built OUTPUT_VARIABLE _out ERROR_VARIABLE _err)
file(WRITE "${_build}/initial-build.log" "${_out}${_err}")
if(NOT _built EQUAL 0)
    message(FATAL_ERROR "Initial build failed: ${_build}/initial-build.log")
endif()
set(_program "${_build}/lesson-note-preview${EXECUTABLE_SUFFIX}")
file(SHA256 "${_program}" _before)
execute_process(COMMAND "${CTEST_PROGRAM}" --test-dir "${_build}"
    -R "^bits[.]build-graph[.]preview-output$" --output-on-failure
    RESULT_VARIABLE _baseline OUTPUT_VARIABLE _out ERROR_VARIABLE _err)
file(WRITE "${_build}/initial-test.log" "${_out}${_err}")
if(NOT _baseline EQUAL 0)
    message(FATAL_ERROR "Initial preview check failed")
endif()
execute_process(COMMAND "${CMAKE_COMMAND}" -S "${SOURCE}" -B "${_build}"
    -DLESSON_REFUSE_PREVIEW_BUILD=ON
    RESULT_VARIABLE _configured OUTPUT_VARIABLE _out ERROR_VARIABLE _err)
file(WRITE "${_build}/refusal-configure.log" "${_out}${_err}")
if(NOT _configured EQUAL 0)
    message(FATAL_ERROR "Refusal configuration failed before the intended compile phase")
endif()
execute_process(COMMAND "${CMAKE_COMMAND}" --build "${_build}" --target lesson-note-preview
    RESULT_VARIABLE _refused OUTPUT_VARIABLE _out ERROR_VARIABLE _err)
file(WRITE "${_build}/expected-build-refusal.log" "${_out}${_err}")
if(_refused EQUAL 0 OR NOT "${_out}${_err}" MATCHES "Deliberate preview compilation refusal")
    message(FATAL_ERROR "The intended compiler refusal was not observed")
endif()
file(SHA256 "${_program}" _after)
if(NOT _before STREQUAL _after)
    message(FATAL_ERROR "The executable changed despite the failed rebuild")
endif()
# Deliberately run ONLY the harmless old preview check to demonstrate the trap.
# This is controlled observation, not qualification of the refused source.
# Never copy this unconditional continuation into a release/build workflow.
execute_process(COMMAND "${CTEST_PROGRAM}" --test-dir "${_build}"
    -R "^bits[.]build-graph[.]preview-output$" --output-on-failure
    RESULT_VARIABLE _stale_result OUTPUT_VARIABLE _out ERROR_VARIABLE _err)
file(WRITE "${_build}/retained-executable-test.log" "${_out}${_err}")
if(NOT _stale_result EQUAL 0)
    message(FATAL_ERROR "The retained executable observation did not reproduce")
endif()
# The normal decision gate derives admission from the build result, not from
# file existence or the retained executable's apparently passing test result.
if(_refused EQUAL 0)
    message(FATAL_ERROR "A failed build was incorrectly admitted")
endif()
message(STATUS "Expected build refusal observed; retained executable hash unchanged")
message(STATUS "Old preview check passed, but current-source qualification is refused")
message(STATUS "Preserved isolated evidence: ${_build}")
