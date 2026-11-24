# Umicom Bits2Banking
# File: content/labs/native/automated-testing-preview/CMakeLists.txt
#
# PURPOSE:
#   Build the callback-free teaching example against one selected Framework SDK.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT

cmake_minimum_required(VERSION 3.24)
project(UmicomTestingPreviewLesson LANGUAGES C)

# Select the same installed SDK for all imported testing and platform targets.
if(NOT IS_ABSOLUTE "${UMICOM_SDK_PREFIX}" OR NOT IS_DIRECTORY "${UMICOM_SDK_PREFIX}")
    message(FATAL_ERROR "Set UMICOM_SDK_PREFIX to an absolute installed Framework SDK directory")
endif()
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS testing
    PATHS "${UMICOM_SDK_PREFIX}" NO_DEFAULT_PATH)
umicom_require_installed_sdk("${UMICOM_SDK_PREFIX}" Umicom::testing Umicom::platform)

add_executable(umicom-testing-preview main.c)
target_link_libraries(umicom-testing-preview PRIVATE Umicom::testing)
set_target_properties(umicom-testing-preview PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
