# Umicom Bits2Banking
# File: labs/framework/studio-build-evidence/CMakeLists.txt
#
# PURPOSE:
#   Build a native C23 producer and client, then check saved evidence in CTest.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT

cmake_minimum_required(VERSION 3.25)
project(UmicomBuildEvidence LANGUAGES C)
include(CTest)

add_library(umicom_lab_evidence STATIC evidence.c)
target_include_directories(umicom_lab_evidence PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(umicom-lab-evidence main.c)

# Keep the header visible even during the intentional link exercise. In the
# normal project the provider owns both the declaration path and the definition.
target_include_directories(umicom-lab-evidence PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
option(UMICOM_LAB_OMIT_PROVIDER "Demonstrate an unresolved symbol in a disposable build" OFF)
if(NOT UMICOM_LAB_OMIT_PROVIDER)
    target_link_libraries(umicom-lab-evidence PRIVATE umicom_lab_evidence)
endif()

foreach(target IN ITEMS umicom_lab_evidence umicom-lab-evidence)
    set_target_properties(${target} PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
    endif()
endforeach()

if(BUILD_TESTING AND NOT UMICOM_LAB_OMIT_PROVIDER)
    # Test the exact exit status and result rather than accepting any failure.
    foreach(case IN ITEMS same different malformed short usage rebuilt)
        add_test(NAME bits.studio.evidence.${case} COMMAND "${CMAKE_COMMAND}"
            "-DLAB_EXECUTABLE=$<TARGET_FILE:umicom-lab-evidence>"
            "-DLAB_CASE=${case}" "-DLAB_WORK=${CMAKE_CURRENT_BINARY_DIR}/fixtures"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/check_evidence.cmake")
        set_tests_properties(bits.studio.evidence.${case} PROPERTIES TIMEOUT 10)
    endforeach()
endif()


# The numeric status exercise is independent of the archive-link lesson. It
# reads text and never selects or starts an external debugger.
add_executable(umicom-lab-status32 status32.c)
set_target_properties(umicom-lab-status32 PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
if(MSVC)
    target_compile_options(umicom-lab-status32 PRIVATE /W4)
else()
    target_compile_options(umicom-lab-status32 PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Werror)
endif()

if(BUILD_TESTING)
    function(add_status_case case word valid report)
        add_test(NAME bits.studio.status32.${case} COMMAND "${CMAKE_COMMAND}"
            "-DLAB_EXECUTABLE=$<TARGET_FILE:umicom-lab-status32>" "-DWORD=${word}"
            "-DEXPECT_VALID=${valid}" "-DREPORT=${report}"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/check_status32.cmake")
        set_tests_properties(bits.studio.status32.${case} PROPERTIES TIMEOUT 10)
    endfunction()
    set(loader_word "hex=0xc0000135 unsigned=3221225781 signed=-1073741515")
    add_status_case(hex 0xc0000135 YES "${loader_word}")
    add_status_case(unsigned 3221225781 YES "${loader_word}")
    add_status_case(signed -1073741515 YES "${loader_word}")
    add_status_case(zero 0 YES "hex=0x00000000 unsigned=0 signed=0")
    add_status_case(overflow 4294967296 NO "")
    add_status_case(negative-overflow -2147483649 NO "")
    add_status_case(malformed 0xc0000135z NO "")
endif()
