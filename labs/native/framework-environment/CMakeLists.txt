#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-environment/CMakeLists.txt
#
# PURPOSE:
#   Build the branded installed-SDK environment example.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------


cmake_minimum_required(VERSION 3.25)
project(Bits2BankingEnvironmentPlan LANGUAGES C)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS toolchain)
include(CTest)
add_executable(btb-framework-environment main.c)
target_link_libraries(btb-framework-environment PRIVATE Umicom::toolchain)
set_target_properties(btb-framework-environment PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
if(MSVC)
    target_compile_options(btb-framework-environment PRIVATE /W4)
else()
    target_compile_options(btb-framework-environment PRIVATE
        -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(WIN32)
    enable_language(RC)
endif()
umicom_apply_application_branding(TARGET btb-framework-environment
    PRODUCT_NAME "Umicom Environment Learning Lab"
    INTERNAL_NAME btb-framework-environment NO_RUNTIME_DEPLOYMENT)
if(BUILD_TESTING)
    foreach(_case IN ITEMS compose alias refusal borrow kit kit-refusal cross-partial kit-revision kit-overlap)
        add_test(NAME bits2banking.environment.${_case}
            COMMAND "${CMAKE_COMMAND}" "-DTOOL=$<TARGET_FILE:btb-framework-environment>"
                "-DCASE=${_case}" -P "${CMAKE_CURRENT_SOURCE_DIR}/check.cmake")
        set_tests_properties(bits2banking.environment.${_case} PROPERTIES
            TIMEOUT 10 LABELS "education;framework;environment;no-process")
    endforeach()
endif()
