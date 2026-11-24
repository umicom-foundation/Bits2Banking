#-----------------------------------------------------------------------------
# Bits2Banking
# File: labs/framework/boot-report-comparison/CMakeLists.txt
#
# PURPOSE:
#   Build a focused boot-report lab against the canonical Framework implementation.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.24)
project(UmicomBootReportLearning LANGUAGES C)
include(CTest)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(UMICOM_FRAMEWORK_SOURCE "" CACHE PATH "Canonical Framework source checkout")
if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/src/platform/boot_report.c")
    message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE to the Framework checkout containing boot_report.c")
endif()
add_library(boot_report_learning STATIC "${UMICOM_FRAMEWORK_SOURCE}/src/platform/boot_report.c")
target_include_directories(boot_report_learning PUBLIC "${UMICOM_FRAMEWORK_SOURCE}/include")
add_executable(boot-report-learning main.c)
target_link_libraries(boot-report-learning PRIVATE boot_report_learning)
foreach(_target IN ITEMS boot_report_learning boot-report-learning)
    if(MSVC)
        target_compile_options(${_target} PRIVATE /W4 /WX)
    else()
        target_compile_options(${_target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
    endif()
endforeach()
if(BUILD_TESTING)
    add_test(NAME learning.boot_report.comparison COMMAND boot-report-learning)
    set_tests_properties(learning.boot_report.comparison PROPERTIES TIMEOUT 10)
endif()

# Build the exact-capture practice only when requested. The original text-only
# parser lab remains usable with older Framework source checkouts.
option(UMICOM_LEARNING_BOOT_CAPTURE "Build the boot capture identity lab" OFF)
if(UMICOM_LEARNING_BOOT_CAPTURE)
    if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/src/platform/boot_report_file.c")
        message(FATAL_ERROR "The capture practice needs Framework source containing boot_report_file.c")
    endif()
    add_executable(boot-report-capture-learning capture_identity.c
        "${UMICOM_FRAMEWORK_SOURCE}/src/platform/boot_report_file.c"
        "${UMICOM_FRAMEWORK_SOURCE}/src/platform/input_file.c"
        "${UMICOM_FRAMEWORK_SOURCE}/src/platform/output_file.c"
        "${UMICOM_FRAMEWORK_SOURCE}/src/base/sha256.c")
    target_link_libraries(boot-report-capture-learning PRIVATE boot_report_learning)
    if(MSVC)
        target_compile_options(boot-report-capture-learning PRIVATE /W4 /WX)
    else()
        target_compile_options(boot-report-capture-learning PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
    endif()
    if(BUILD_TESTING)
        # Define the capture bytes independently of a contributor's Git checkout
        # line-ending policy. The portable fixture always ends in a single LF.
        set(_capture_dir "${CMAKE_CURRENT_BINARY_DIR}/capture-fixtures")
        file(MAKE_DIRECTORY "${_capture_dir}")
        configure_file(fixtures/first.txt "${_capture_dir}/first.txt" @ONLY NEWLINE_STYLE UNIX)
        configure_file(fixtures/reordered.txt "${_capture_dir}/reordered.txt" @ONLY NEWLINE_STYLE UNIX)
        add_test(NAME learning.boot_report.capture_identity COMMAND boot-report-capture-learning
            "${_capture_dir}/first.txt" "${_capture_dir}/reordered.txt")
        set_tests_properties(learning.boot_report.capture_identity PROPERTIES TIMEOUT 10)
    endif()
endif()
