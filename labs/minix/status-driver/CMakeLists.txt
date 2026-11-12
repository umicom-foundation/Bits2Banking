# Umicom Bits2Banking
# File: CMakeLists.txt
# PURPOSE: Check portable range logic without claiming MINIX driver execution.
# AUTHOR AND ORGANISATION: Sammy Hegab / Umicom Foundation
# LICENCE: MIT
cmake_minimum_required(VERSION 3.24)
project(MinixReadWindowModel LANGUAGES C)
add_executable(read-window-tests read_window.c read_window_tests.c)
set_target_properties(read-window-tests PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
include(CTest)
if(BUILD_TESTING)
    add_test(NAME minix.learning.read-window COMMAND read-window-tests)
endif()

# The portable callback is original lab code, not a guest grant emulator.
# C99 is intentional for the pinned MINIX source target; production Umicom
# services continue to use their own C23 build policies.
add_executable(read-reply-tests read_window.c read_reply.c read_reply_tests.c)
set_target_properties(read-reply-tests PROPERTIES
    C_STANDARD 99 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(read-reply-tests PRIVATE
        -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
if(BUILD_TESTING)
    foreach(_case IN ITEMS
        prefix tail whole eof beyond huge-position zero empty null-empty
        huge-request positive-failure negative-failure retry reuse-eof
        null-text null-copy null-reply chunked null-context)
        add_test(NAME minix.learning.read-reply.${_case}
            COMMAND read-reply-tests "${_case}")
        set_tests_properties(minix.learning.read-reply.${_case} PROPERTIES
            TIMEOUT 10 LABELS "education;minix;portable;no-devices")
    endforeach()
endif()

# Host executable identity uses the shared helper and canonical assets without
# linking Framework into this independent C lab. MINIX's Makefile is unchanged
# by these host-only resources and does not require a Framework installation.
get_filename_component(_framework_default
    "${CMAKE_CURRENT_LIST_DIR}/../../../../Umicom-Applications/framework" ABSOLUTE)
set(UMICOM_FRAMEWORK_SOURCE "${_framework_default}" CACHE PATH
    "Framework source supplying canonical host executable branding")
if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
    message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE to Framework with UmicomApplicationBranding.cmake")
endif()
include("${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
if(WIN32)
    enable_language(RC)
endif()
foreach(_target IN ITEMS read-window-tests read-reply-tests)
    umicom_apply_application_branding(TARGET "${_target}"
        PRODUCT_NAME "Umicom MINIX Read Boundary Learning Lab"
        INTERNAL_NAME "${_target}" NO_RUNTIME_DEPLOYMENT)
endforeach()
