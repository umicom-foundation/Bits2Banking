#-----------------------------------------------------------------------------
# Bits2Banking
# File: labs/native/boot-handoff/CMakeLists.txt
#
# PURPOSE:
#   Build the lesson against the real Kernel boot reader rather than a second parser.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.24)
project(UmicomBootHandoffLab LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(UMICOM_KERNEL_SOURCE "" CACHE PATH "Path to the Umicom Kernel source checkout")
if(NOT EXISTS "${UMICOM_KERNEL_SOURCE}/kernel/boot_handoff.c")
    message(FATAL_ERROR "Set UMICOM_KERNEL_SOURCE to the Kernel checkout containing kernel/boot_handoff.c")
endif()
add_executable(boot-handoff main.c "${UMICOM_KERNEL_SOURCE}/kernel/boot_handoff.c" "${UMICOM_KERNEL_SOURCE}/kernel/address.c")
target_include_directories(boot-handoff PRIVATE "${UMICOM_KERNEL_SOURCE}/include")
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(boot-handoff PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
include(CTest)
if(BUILD_TESTING)
    add_test(NAME learning.kernel.boot-handoff COMMAND boot-handoff)
endif()

# The original byte-construction exercise remains useful for learning the wire
# format. The producer client delegates encoding and admission to Kernel source.
if(NOT EXISTS "${UMICOM_KERNEL_SOURCE}/kernel/boot_handoff_write.c")
    message(FATAL_ERROR "The writer exercise needs kernel/boot_handoff_write.c in UMICOM_KERNEL_SOURCE")
endif()
add_executable(boot-handoff-write write.c
    "${UMICOM_KERNEL_SOURCE}/kernel/boot_handoff_write.c"
    "${UMICOM_KERNEL_SOURCE}/kernel/boot_handoff.c"
    "${UMICOM_KERNEL_SOURCE}/kernel/address.c")
target_include_directories(boot-handoff-write PRIVATE "${UMICOM_KERNEL_SOURCE}/include")
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(boot-handoff-write PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()

# Hosted tools use Framework's single branding helper. The freestanding Kernel
# receives no Framework library, GTK dependency or Windows resource.
get_filename_component(_framework_default
    "${CMAKE_CURRENT_LIST_DIR}/../../../../Umicom-Applications/framework" ABSOLUTE)
set(UMICOM_FRAMEWORK_SOURCE "${_framework_default}" CACHE PATH "Framework source supplying canonical SVG/ICO branding")
if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
    message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE to the Framework checkout with UmicomApplicationBranding.cmake")
endif()
include("${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
if(WIN32)
    enable_language(RC)
endif()
foreach(_tool IN ITEMS boot-handoff boot-handoff-write)
    umicom_apply_application_branding(TARGET "${_tool}"
        PRODUCT_NAME "Umicom Kernel Boot Handoff Learning Lab"
        INTERNAL_NAME "${_tool}" NO_RUNTIME_DEPLOYMENT)
endforeach()
if(BUILD_TESTING)
    foreach(_case IN ITEMS roundtrip small unreserved bad-text)
        add_test(NAME learning.kernel.boot-handoff-write.${_case}
            COMMAND boot-handoff-write "${_case}")
        set_tests_properties(learning.kernel.boot-handoff-write.${_case}
            PROPERTIES TIMEOUT 10 LABELS "education;kernel;host;no-devices")
    endforeach()
endif()
