#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/framework/fastcgi-head-review/CMakeLists.txt
#
# PURPOSE:
#   Build the offline HEAD representation and wire-byte exercise.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.24)
project(BitsFastCgiHeadReview LANGUAGES C)
include(CTest)

# Use a separate review module so learners can connect contract and fixture
# without needing a running service or a system FastCGI implementation.
if(BUILD_TESTING)
    add_executable(bits-fastcgi-head-check head_review.c test_head_review.c)
    target_compile_features(bits-fastcgi-head-check PRIVATE c_std_23)
    set_target_properties(bits-fastcgi-head-check PROPERTIES C_EXTENSIONS OFF)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(bits-fastcgi-head-check PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
    endif()

    foreach(case known known-zero unknown discard-document length-limit short-output)
        add_test(NAME "bits2banking.fastcgi-head.${case}" COMMAND bits-fastcgi-head-check "${case}")
        set_tests_properties("bits2banking.fastcgi-head.${case}" PROPERTIES TIMEOUT 15)
    endforeach()
endif()

