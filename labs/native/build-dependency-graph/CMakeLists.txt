#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/build-dependency-graph/CMakeLists.txt
#
# PURPOSE:
#   Expose dependency relationships while reusing the existing bounded Notes implementation.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.26)
project(BitsDependencyGraph LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)
option(LESSON_SHOW_HEADING "Print a heading before the note" ON)
# The build directory owns this generated header. Targets consume its path;
# they do not each declare a separate writer or write into the source tree.
configure_file(lesson_config.h.in generated/lesson_config.h @ONLY)
add_library(lesson-notes STATIC ../safe-notes/notes.c)
target_include_directories(lesson-notes PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../safe-notes")
add_executable(lesson-note-preview preview.c)
target_link_libraries(lesson-note-preview PRIVATE lesson-notes)
target_include_directories(lesson-note-preview PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/generated")
add_executable(lesson-note-capacity capacity.c)
target_link_libraries(lesson-note-capacity PRIVATE lesson-notes)
set(lesson_targets lesson-notes lesson-note-preview lesson-note-capacity)
if(BUILD_TESTING)
    add_executable(lesson-note-boundaries ../safe-notes/test_notes.c)
    target_link_libraries(lesson-note-boundaries PRIVATE lesson-notes)
    list(APPEND lesson_targets lesson-note-boundaries)
    add_test(NAME bits.build-graph.notes-boundaries COMMAND lesson-note-boundaries)
    add_test(NAME bits.build-graph.preview-output COMMAND "${CMAKE_COMMAND}"
        "-DPROGRAM=$<TARGET_FILE:lesson-note-preview>"
        "-DSHOW_HEADING=${LESSON_SHOW_HEADING}"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/check_preview.cmake")
    set_tests_properties(bits.build-graph.notes-boundaries bits.build-graph.preview-output
        PROPERTIES TIMEOUT 10 LABELS "build-graph;notes")
endif()
foreach(target IN LISTS lesson_targets)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    endif()
endforeach()
