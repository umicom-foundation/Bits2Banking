#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-filesystem-clients/CMakeLists.txt
#
# PURPOSE:
#   Build installed-SDK filesystem ownership exercises with isolated retained native fixtures.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(btb_filesystem_clients LANGUAGES C)
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
umicom_require_installed_sdk_layout("${UMICOM_EXPECTED_SDK_PREFIX}" _headers Umicom::developer)
add_executable(filesystem-clients main.c fixture.c names.c files.c projects.c)
set_target_properties(filesystem-clients PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
target_link_libraries(filesystem-clients PRIVATE Umicom::developer)
if(MSVC)
    target_compile_options(filesystem-clients PRIVATE /W4)
else()
    target_compile_options(filesystem-clients PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(WIN32)
    enable_language(RC)
endif()
umicom_apply_application_branding(TARGET filesystem-clients
    PRODUCT_NAME "Umicom Filesystem Client Course Lab" INTERNAL_NAME "filesystem-clients")
include(CTest)
if(BUILD_TESTING)
    foreach(scenario path-admission path-relations invalid-path directory-chain exclusive-directory new-file existing-file empty-file invalid-directory project-preview project-create project-collision service-create service-refusal profile-preview)
        file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/qualification/${scenario}")
        add_test(NAME learning.filesystem_clients.${scenario} COMMAND filesystem-clients ${scenario}
            "${CMAKE_CURRENT_BINARY_DIR}/qualification/${scenario}")
        set_tests_properties(learning.filesystem_clients.${scenario} PROPERTIES TIMEOUT 30)
    endforeach()
endif()
