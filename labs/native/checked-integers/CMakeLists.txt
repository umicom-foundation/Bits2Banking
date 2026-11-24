#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/checked-integers/CMakeLists.txt
#
# PURPOSE:
#   Build the independent C23 checked-integer practice cases.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.24)
project(Bits2BankingCheckedIntegers LANGUAGES C)
include(CTest)

# Keep the cases independent so one failing operation is easy to diagnose.
foreach(example IN ITEMS add subtract multiply record fallback)
    add_executable(checked-integers-${example} ${example}.c)
    set_target_properties(checked-integers-${example} PROPERTIES
        C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(checked-integers-${example} PRIVATE
            -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
    endif()
    if(BUILD_TESTING)
        add_test(NAME lesson.checked-integers.${example}
                 COMMAND checked-integers-${example})
    endif()
endforeach()
