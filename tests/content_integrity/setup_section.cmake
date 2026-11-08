#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: tests/content_integrity/setup_section.cmake
#
# PURPOSE:
#   Recognise visible, nonempty setup guidance across existing lesson headings.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

# A heading spelling is presentation, not the preparation contract. Accept
# the existing lesson vocabulary, but require visible prose before the next
# heading. Ignore comments and fenced examples so preserved text cannot pass.
function(BtbHasSetupSection document output)
    string(REPLACE "\r\n" "\n" _remaining "${document}")
    set(_active "")
    while(TRUE)
        string(FIND "${_remaining}" "<!--" _start)
        if(_start LESS 0)
            string(APPEND _active "${_remaining}")
            break()
        endif()
        string(SUBSTRING "${_remaining}" 0 ${_start} _prefix)
        string(APPEND _active "${_prefix}")
        math(EXPR _tail_start "${_start} + 4")
        string(SUBSTRING "${_remaining}" ${_tail_start} -1 _tail)
        string(FIND "${_tail}" "-->" _end)
        if(_end LESS 0)
            set(${output} FALSE PARENT_SCOPE)
            return()
        endif()
        math(EXPR _after "${_end} + 3")
        string(SUBSTRING "${_tail}" ${_after} -1 _remaining)
    endwhile()
    set(_remaining "${_active}")
    set(_fence "")
    set(_setup FALSE)
    while(NOT _remaining STREQUAL "")
        string(FIND "${_remaining}" "\n" _newline)
        if(_newline LESS 0)
            set(_line "${_remaining}")
            set(_remaining "")
        else()
            string(SUBSTRING "${_remaining}" 0 ${_newline} _line)
            math(EXPR _after "${_newline} + 1")
            string(SUBSTRING "${_remaining}" ${_after} -1 _remaining)
        endif()
        # A four-space indentation is a code block in Markdown. This small
        # source contract deliberately accepts only unindented ATX headings.
        if(_line MATCHES "^    " OR _line MATCHES "^\t")
            continue()
        endif()
        if(_line MATCHES "^ ? ? ?(```+|~~~+)")
            set(_marker "${CMAKE_MATCH_1}")
            string(SUBSTRING "${_marker}" 0 1 _character)
            string(LENGTH "${_marker}" _length)
            if(_fence STREQUAL "")
                set(_fence "${_character}")
                set(_fence_length ${_length})
            elseif(_character STREQUAL _fence AND _length GREATER_EQUAL _fence_length
                    AND _line MATCHES "^[ ]*(`+|~+)[ \t]*$")
                set(_fence "")
            endif()
            continue()
        endif()
        if(NOT _fence STREQUAL "")
            continue()
        endif()
        if(_line MATCHES "^#+[ \t]")
            if(_setup)
                set(${output} FALSE PARENT_SCOPE)
                return()
            endif()
            if(_line MATCHES "^## (Setup recap(: .*)?|Prepare( .*)?|Before you begin|Set up)[ \t]*$")
                set(_setup TRUE)
            endif()
            continue()
        endif()
        string(STRIP "${_line}" _prose)
        if(_setup AND NOT _prose STREQUAL "")
            set(${output} TRUE PARENT_SCOPE)
            return()
        endif()
    endwhile()
    set(${output} FALSE PARENT_SCOPE)
endfunction()
