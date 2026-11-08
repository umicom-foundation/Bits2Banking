#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: tests/content_integrity/source_reference.cmake
#
# PURPOSE:
#   Validate declared source routes without confusing external references with local laboratory files.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

include_guard(GLOBAL)
function(BtbValidateSourceReference source repository_root result reason)
    set(_local FALSE)
    set(_path "")
    if(source MATCHES "^labs/(.+)$")
        set(_local TRUE)
        set(_path "labs/${CMAKE_MATCH_1}")
    elseif(source MATCHES "^https://github[.]com/umicom-foundation/(umicom-c|umicom-kernel|umicom-framework|umicom-studio-ide-module|umicom-os)/blob/main/(.+)$")
        set(_path "${CMAKE_MATCH_2}")
    elseif(source MATCHES "^([.][.]/)?(umicom-c|umicom-kernel)/(.+)$")
        set(_path "${CMAKE_MATCH_3}")
    elseif(source MATCHES "^[.][.]/Umicom-Applications/framework/(.+)$")
        set(_path "${CMAKE_MATCH_1}")
    else()
        set(${result} FALSE PARENT_SCOPE)
        set(${reason} "unrecognised source repository or route" PARENT_SCOPE)
        return()
    endif()
    # These are source identities, not arbitrary URLs or filesystem expressions.
    # External references are grammar-checked only; no network claim is made.
    if(NOT _path MATCHES "^[A-Za-z0-9_./-]+$" OR _path MATCHES "^/|/$|//|(^|/)[.][.]?(/|$)")
        set(${result} FALSE PARENT_SCOPE)
        set(${reason} "unsafe or ambiguous source path" PARENT_SCOPE)
        return()
    endif()
    if(_local)
        set(_candidate "${repository_root}/${_path}")
        if(NOT EXISTS "${_candidate}" OR IS_DIRECTORY "${_candidate}")
            set(${result} FALSE PARENT_SCOPE)
            set(${reason} "local laboratory source is missing or is a directory" PARENT_SCOPE)
            return()
        endif()
        file(REAL_PATH "${repository_root}" _root)
        file(REAL_PATH "${_candidate}" _resolved)
        file(RELATIVE_PATH _within "${_root}" "${_resolved}")
        if(_within MATCHES "^[.][.](/|$)" OR IS_ABSOLUTE "${_within}")
            set(${result} FALSE PARENT_SCOPE)
            set(${reason} "local laboratory source resolves outside the checkout" PARENT_SCOPE)
            return()
        endif()
    endif()
    set(${result} TRUE PARENT_SCOPE)
    set(${reason} "" PARENT_SCOPE)
endfunction()
