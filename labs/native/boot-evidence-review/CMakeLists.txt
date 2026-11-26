#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/boot-evidence-review/CMakeLists.txt
#
# PURPOSE:
#   Build the independent C23 boot evidence learning exercise.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(BtbBootEvidenceReview LANGUAGES C)

add_executable(btb-boot-evidence-review main.c)
set_target_properties(btb-boot-evidence-review PROPERTIES
    C_STANDARD 23
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(btb-boot-evidence-review PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()

include(CTest)
if(BUILD_TESTING)
    # A lesson is easier to debug when each refusal checks the exact observable result.
    function(add_review_case name exit_code message)
        add_test(NAME "btb.boot_evidence.${name}"
            COMMAND "${CMAKE_COMMAND}"
                "-DTOOL=$<TARGET_FILE:btb-boot-evidence-review>"
                "-DCASE=${name}" "-DEXPECT_EXIT=${exit_code}" "-DEXPECT_OUTPUT=${message}"
                -P "${CMAKE_CURRENT_SOURCE_DIR}/check.cmake")
    endfunction()

    add_review_case(optical 0 "Virtual optical boot evidence complete.")
    add_review_case(virtual-usb 0 "Virtual USB boot evidence complete.")
    add_review_case(no-file-review 1 "Review the image structure before admitting a boot claim.")
    add_review_case(direct-only 1 "The capture used a different boot path.")
    add_review_case(wrong-image 1 "A boot capture refers to a different image.")
    add_review_case(wrong-firmware 1 "A capture used different firmware.")
    add_review_case(no-shutdown 1 "A launch, shutdown marker or process result is missing or unsuccessful.")
    add_review_case(process-error 1 "A launch, shutdown marker or process result is missing or unsuccessful.")
    add_review_case(repeated-log 1 "Save separate transcripts for normal and recovery.")
    add_review_case(swapped-modes 1 "Check which capture actually ran in normal or recovery mode.")
    add_review_case(malformed-pin 1 "Check the format of every SHA-256 pin.")
endif()
