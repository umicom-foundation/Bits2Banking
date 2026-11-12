#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-gpt-inspection/CMakeLists.txt
#
# PURPOSE:
#   Build a memory-only application against installed Framework GPT inspection.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(btb_gpt_inspection LANGUAGES C)
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
umicom_require_installed_sdk_layout("${UMICOM_EXPECTED_SDK_PREFIX}" _headers Umicom::gpt_image)
add_executable(gpt-inspection main.c image.c port.c)
set_target_properties(gpt-inspection PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
target_link_libraries(gpt-inspection PRIVATE Umicom::gpt_image)
if(MSVC)
    target_compile_options(gpt-inspection PRIVATE /W4)
else()
    target_compile_options(gpt-inspection PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(WIN32)
    enable_language(RC)
endif()
umicom_apply_application_branding(TARGET gpt-inspection
    PRODUCT_NAME "Umicom GPT Inspection Course Lab" INTERNAL_NAME "gpt-inspection")
include(CTest)
if(BUILD_TESTING)
    foreach(scenario valid-512 valid-4096 reservation stride overlap backup read-failure retry)
        add_test(NAME learning.gpt_inspection.${scenario} COMMAND gpt-inspection ${scenario})
        set_tests_properties(learning.gpt_inspection.${scenario} PROPERTIES TIMEOUT 10)
    endforeach()
endif()
