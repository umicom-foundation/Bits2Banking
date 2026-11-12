#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/shared-editor/CMakeLists.txt
#
# PURPOSE:
#   Build installed-SDK exercises for editor text, positions and document history.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(btb_shared_editor LANGUAGES C)
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
file(REAL_PATH "${UMICOM_EXPECTED_SDK_PREFIX}" _sdk_prefix)
file(REAL_PATH "${UmicomFramework_CONFIG}" _sdk_configuration)
cmake_path(IS_PREFIX _sdk_prefix "${_sdk_configuration}" NORMALIZE _sdk_inside)
if(NOT _sdk_inside)
    message(FATAL_ERROR "The selected Framework package is outside the requested prefix")
endif()
if(NOT COMMAND umicom_require_sdk_environment)
    message(FATAL_ERROR "Reinstall Framework with its SDK environment metadata")
endif()
umicom_require_sdk_environment(2)
umicom_require_installed_sdk_layout("${UMICOM_EXPECTED_SDK_PREFIX}" _headers Umicom::document Umicom::editor)
add_executable(shared-editor main.c buffer.c document.c)
set_target_properties(shared-editor PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
target_link_libraries(shared-editor PRIVATE Umicom::document Umicom::editor)
if(MSVC)
    target_compile_options(shared-editor PRIVATE /W4)
else()
    target_compile_options(shared-editor PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(WIN32)
    enable_language(RC)
endif()
umicom_apply_application_branding(TARGET shared-editor
    PRODUCT_NAME "Umicom Shared Editor Course Lab" INTERNAL_NAME "shared-editor")
include(CTest)
if(BUILD_TESTING)
    foreach(scenario ownership positions position-refusals selection selection-refusals history redo-branch stale-plan other-tab invalid-replacement consumed-plan read-only)
        add_test(NAME learning.shared_editor.${scenario} COMMAND shared-editor ${scenario})
        set_tests_properties(learning.shared_editor.${scenario} PROPERTIES TIMEOUT 10)
    endforeach()
endif()
