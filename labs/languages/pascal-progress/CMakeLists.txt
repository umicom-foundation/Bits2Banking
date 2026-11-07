# -----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/languages/pascal-progress/CMakeLists.txt
#
# PURPOSE:
#   Compile the Pascal examples and register argument validation cases.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
# -----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.24)
project(BtbPascalProgress LANGUAGES NONE)
include(CTest)
find_program(FPC_EXECUTABLE NAMES fpc REQUIRED)
if(WIN32)
    set(_suffix ".exe")
else()
    set(_suffix "")
endif()
# The original two-program list remains documented here; the additional
# programs teach records through the same unit and preserve existing targets.
# foreach(_name IN ITEMS hello progress)
# The four-program composition remains here for source-history exercises.
# foreach(_name IN ITEMS hello progress progress_records progress_checks)
# The course notebook composes the same progress unit instead of copying it.
foreach(_name IN ITEMS hello progress progress_records progress_checks coursebook_demo coursebook_checks)
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/units/${_name}")
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${_name}${_suffix}"
        COMMAND "${FPC_EXECUTABLE}" -Mobjfpc -Cr -Co
            "-FE${CMAKE_CURRENT_BINARY_DIR}"
            "-FU${CMAKE_CURRENT_BINARY_DIR}/units/${_name}"
            "-Fu${CMAKE_CURRENT_SOURCE_DIR}"
            "-o${CMAKE_CURRENT_BINARY_DIR}/${_name}${_suffix}"
            "${CMAKE_CURRENT_SOURCE_DIR}/${_name}.pas"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${_name}.pas"
            "${CMAKE_CURRENT_SOURCE_DIR}/lessonprogress.pas"
            "${CMAKE_CURRENT_SOURCE_DIR}/coursebook.pas" VERBATIM)
    add_custom_target(btb-pascal-${_name} ALL
        DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${_name}${_suffix}")
endforeach()
# Previously every program used -FU${CMAKE_CURRENT_BINARY_DIR}. Separate
# unit output directories now prevent parallel compilers writing the same
# LessonProgress object and unit files. The old output choice is retained
# in this explanation for the build-engineering exercise.
if(BUILD_TESTING)
    add_test(NAME bits2banking.pascal.coursebook
        COMMAND "${CMAKE_CURRENT_BINARY_DIR}/coursebook_checks${_suffix}")
    add_test(NAME bits2banking.pascal.coursebook_demo
        COMMAND "${CMAKE_CURRENT_BINARY_DIR}/coursebook_demo${_suffix}")
    set_tests_properties(bits2banking.pascal.coursebook bits2banking.pascal.coursebook_demo
        PROPERTIES TIMEOUT 15)
    set_tests_properties(bits2banking.pascal.coursebook_demo PROPERTIES
        PASS_REGULAR_EXPRESSION "Introduction to RISC-V: 3 remaining")
    add_test(NAME bits2banking.pascal.arguments
        COMMAND "${CMAKE_COMMAND}" "-DPROGRAM=${CMAKE_CURRENT_BINARY_DIR}/progress${_suffix}"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/check_progress.cmake")
    set_tests_properties(bits2banking.pascal.arguments PROPERTIES TIMEOUT 45)
    add_test(NAME bits2banking.pascal.records
        COMMAND "${CMAKE_CURRENT_BINARY_DIR}/progress_checks${_suffix}")
    add_test(NAME bits2banking.pascal.record_demo
        COMMAND "${CMAKE_CURRENT_BINARY_DIR}/progress_records${_suffix}")
    set_tests_properties(bits2banking.pascal.record_demo PROPERTIES
        PASS_REGULAR_EXPRESSION "Course 2: 3 lessons remaining")
    set_tests_properties(bits2banking.pascal.records bits2banking.pascal.record_demo
        PROPERTIES TIMEOUT 15)
endif()
