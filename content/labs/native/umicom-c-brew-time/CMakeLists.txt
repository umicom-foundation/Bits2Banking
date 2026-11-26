# Umicom Bits2Banking
# File: content/labs/native/umicom-c-brew-time/CMakeLists.txt
#
# PURPOSE:
# Build and test the Umicom C developer workshop against an explicit source tree.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT

cmake_minimum_required(VERSION 3.24)
project(UmicomCBrewTime LANGUAGES C)

set(UMICOM_C_SOURCE "" CACHE PATH "Source checkout for the Umicom C compiler and runtime")
if(NOT EXISTS "${UMICOM_C_SOURCE}/include/umicom_c/umicom_c.h")
    message(FATAL_ERROR "Set UMICOM_C_SOURCE to the root of a matching Umicom C checkout.")
endif()

# Use local source targets so the tool and libraries come from the same source.
# Keep Umicom C's own qualification separate from this small teaching suite.
set(UMICOM_C_BUILD_TESTS OFF)
set(UMICOM_C_BUILD_TOOLS ON)
add_subdirectory("${UMICOM_C_SOURCE}" "${CMAKE_CURRENT_BINARY_DIR}/umicom-c")

add_executable(brew-time-sdk brew-time-sdk.c)
set_target_properties(brew-time-sdk PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
target_link_libraries(brew-time-sdk PRIVATE UmicomC::Compiler UmicomC::Runtime)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(brew-time-sdk PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

enable_testing()
add_test(NAME brew.sdk COMMAND brew-time-sdk)
foreach(case IN ITEMS source artifact input preview block rollback regions)
    add_test(NAME "brew.${case}" COMMAND "${CMAKE_COMMAND}"
        "-DTOOL=$<TARGET_FILE:umicom-c>"
        "-DSOURCE=${CMAKE_CURRENT_SOURCE_DIR}"
        "-DWORK=${CMAKE_CURRENT_BINARY_DIR}/check-${case}"
        "-DCASE=${case}"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/check-brew-time.cmake")
endforeach()
