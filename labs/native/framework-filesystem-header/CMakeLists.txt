#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-filesystem-header/CMakeLists.txt
#
# PURPOSE:
#   Build the memory-only teaching client against the selected installed SDK.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(btb_filesystem_header LANGUAGES C)

# Use the same installed-SDK selection and identity checks as the GPT lab.
if(NOT DEFINED UMICOM_EXPECTED_SDK_PREFIX OR
   NOT IS_ABSOLUTE "${UMICOM_EXPECTED_SDK_PREFIX}" OR
   NOT IS_DIRECTORY "${UMICOM_EXPECTED_SDK_PREFIX}")
    message(FATAL_ERROR "Supply UMICOM_EXPECTED_SDK_PREFIX as the installed SDK's absolute directory")
endif()
find_package(UmicomFramework CONFIG REQUIRED
    PATHS "${UMICOM_EXPECTED_SDK_PREFIX}" NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
if(NOT DEFINED UmicomFramework_CONFIG OR NOT EXISTS "${UmicomFramework_CONFIG}")
    message(FATAL_ERROR "The selected Framework configuration is not an existing file")
endif()
file(REAL_PATH "${UMICOM_EXPECTED_SDK_PREFIX}" sdk_prefix)
file(REAL_PATH "${UmicomFramework_CONFIG}" sdk_configuration)
cmake_path(IS_PREFIX sdk_prefix "${sdk_configuration}" NORMALIZE sdk_inside)
if(NOT sdk_inside OR NOT COMMAND umicom_require_sdk_environment)
    message(FATAL_ERROR "Select the matching installed Framework SDK with environment metadata")
endif()
umicom_require_sdk_environment(2)
umicom_require_installed_sdk_layout("${UMICOM_EXPECTED_SDK_PREFIX}" sdk_headers Umicom::gpt_image)
if(NOT EXISTS "${sdk_headers}/umicom/image_inspection/gpt_filesystem.h")
    message(FATAL_ERROR "The selected SDK must include the GPT filesystem metadata header")
endif()

add_executable(btb-filesystem-header main.c)
set_target_properties(btb-filesystem-header PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
target_link_libraries(btb-filesystem-header PRIVATE Umicom::gpt_image)
if(MSVC)
    target_compile_options(btb-filesystem-header PRIVATE /W4)
else()
    target_compile_options(btb-filesystem-header PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(WIN32)
    enable_language(RC)
endif()
umicom_apply_application_branding(TARGET btb-filesystem-header
    PRODUCT_NAME "Umicom Filesystem Header Course Lab" INTERNAL_NAME "btb-filesystem-header")

# The client checks both status and callback count. These independent
# cases make it clear when an input was refused before reading.
include(CTest)
if(BUILD_TESTING)
    foreach(scenario present partition-too-short unknown-signature volume-too-large)
        add_test(NAME learning.filesystem_header.${scenario} COMMAND btb-filesystem-header ${scenario})
        set_tests_properties(learning.filesystem_header.${scenario} PROPERTIES TIMEOUT 10)
    endforeach()
endif()
