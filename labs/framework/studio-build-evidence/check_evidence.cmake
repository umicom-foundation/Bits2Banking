# Umicom Bits2Banking
# File: labs/framework/studio-build-evidence/check_evidence.cmake
#
# PURPOSE:
#   Check native exit codes and exact output, including an amended artifact.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT

cmake_minimum_required(VERSION 3.25)

if(NOT DEFINED LAB_EXECUTABLE OR NOT DEFINED LAB_CASE OR NOT DEFINED LAB_WORK)
    message(FATAL_ERROR "Select the executable, case, and private fixture directory")
endif()

string(SHA256 approved "reviewed classroom file")
string(SHA256 changed "changed classroom file")
set(arguments "${approved}" "${approved}")
set(expected_exit 0)
set(expected_output "evidence matches")
set(expected_error "")

if(LAB_CASE STREQUAL "different")
    set(arguments "${approved}" "${changed}")
    set(expected_exit 2)
    set(expected_output "evidence differs")
elseif(LAB_CASE STREQUAL "malformed" OR LAB_CASE STREQUAL "short")
    if(LAB_CASE STREQUAL "malformed")
        string(SUBSTRING "${approved}" 1 63 suffix)
        set(invalid "G${suffix}")
    else()
        set(invalid "abc")
    endif()
    set(arguments "${approved}" "${invalid}")
    set(expected_exit 3)
    set(expected_output "invalid digest record")
elseif(LAB_CASE STREQUAL "usage")
    set(arguments "${approved}")
    set(expected_exit 3)
    set(expected_output "")
    set(expected_error "usage: expected-sha256 observed-sha256")
elseif(LAB_CASE STREQUAL "rebuilt")
    # Use a build-local fixture so the test never alters the real executable.
    # The old receipt remains frozen while the simulated artifact changes.
    file(MAKE_DIRECTORY "${LAB_WORK}")
    set(artifact "${LAB_WORK}/rebuilt-artifact.txt")
    file(WRITE "${artifact}" "release A\n")
    file(SHA256 "${artifact}" saved)
    file(WRITE "${artifact}" "release B\n")
    file(SHA256 "${artifact}" observed)
    set(arguments "${saved}" "${observed}")
    set(expected_exit 2)
    set(expected_output "evidence differs")
elseif(NOT LAB_CASE STREQUAL "same")
    message(FATAL_ERROR "Unknown evidence case: ${LAB_CASE}")
endif()

execute_process(COMMAND "${LAB_EXECUTABLE}" ${arguments}
    RESULT_VARIABLE actual_exit OUTPUT_VARIABLE output ERROR_VARIABLE error
    OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_STRIP_TRAILING_WHITESPACE TIMEOUT 5)

# Launch errors and timeouts are also possible results from execute_process.
# Exact comparison keeps them from being mistaken for the expected refusal.
if(NOT "${actual_exit}" STREQUAL "${expected_exit}" OR
    NOT output STREQUAL expected_output OR NOT error STREQUAL expected_error)
    message(FATAL_ERROR
        "Wrong evidence result: exit=${actual_exit}, stdout=${output}, stderr=${error}")
endif()
