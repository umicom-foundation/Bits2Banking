#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-project-recipes/CMakeLists.txt
#
# PURPOSE:
#   Build a memory-only application against installed Framework project recipe preparation.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(btb_project_recipes LANGUAGES C)
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
add_executable(project-recipes main.c recipe.c inputs.c preview.c)
set_target_properties(project-recipes PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
target_link_libraries(project-recipes PRIVATE Umicom::developer)
if(MSVC)
    target_compile_options(project-recipes PRIVATE /W4)
else()
    target_compile_options(project-recipes PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(WIN32)
    enable_language(RC)
endif()
umicom_apply_application_branding(TARGET project-recipes
    PRODUCT_NAME "Umicom Project Recipe Course Lab" INTERNAL_NAME "project-recipes")
include(CTest)
if(BUILD_TESTING)
    foreach(scenario catalogue variables invalid-variable request invalid-request preview late-failure duplicate aliased-root destination reserved-folder gtk-branding)
        add_test(NAME learning.project_recipes.${scenario} COMMAND project-recipes ${scenario})
        set_tests_properties(learning.project_recipes.${scenario} PROPERTIES TIMEOUT 10)
    endforeach()
endif()
