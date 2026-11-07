#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: content/community/examples/notes-word-count/CMakeLists.txt
#
# PURPOSE:
#   Build one reusable teaching component and exercise its callers.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.22)
project(umicom_notes_word_count LANGUAGES C)
include(CTest)
add_library(notes-words STATIC src/note_words.c)
target_include_directories(notes-words PUBLIC include)
target_compile_features(notes-words PUBLIC c_std_23)
add_executable(notes-word-count src/main.c)
target_link_libraries(notes-word-count PRIVATE notes-words)
if(BUILD_TESTING)
    add_executable(notes-word-count-test tests/test_note_words.c)
    target_link_libraries(notes-word-count-test PRIVATE notes-words)
    add_test(NAME notes.word_count COMMAND notes-word-count-test)
    add_test(NAME notes.console COMMAND notes-word-count)
    set_tests_properties(notes.console PROPERTIES PASS_REGULAR_EXPRESSION "Words: 4")
endif()
foreach(_target IN ITEMS notes-words notes-word-count notes-word-count-test)
    if(TARGET ${_target})
        if(MSVC)
            target_compile_options(${_target} PRIVATE /W4)
        else()
            target_compile_options(${_target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
        endif()
    endif()
endforeach()
