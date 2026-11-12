#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-compiler-ownership/CMakeLists.txt
#
# PURPOSE:
#   Build an installed-SDK client for compiler record and argument-plan ownership.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)
project(Bits2BankingCompilerOwnership LANGUAGES C)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS compiler)
include(CTest)
add_executable(btb-framework-compiler-ownership main.c)
target_link_libraries(btb-framework-compiler-ownership PRIVATE Umicom::compiler)
set_target_properties(btb-framework-compiler-ownership PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
if(MSVC)
    target_compile_options(btb-framework-compiler-ownership PRIVATE /W4)
else()
    target_compile_options(btb-framework-compiler-ownership PRIVATE
        -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(WIN32)
    enable_language(RC)
endif()
umicom_apply_application_branding(TARGET btb-framework-compiler-ownership
    PRODUCT_NAME "Umicom Compiler Ownership Learning Lab"
    INTERNAL_NAME btb-framework-compiler-ownership NO_RUNTIME_DEPLOYMENT)
if(BUILD_TESTING)
    foreach(scenario target abi catalogue request publication views revision)
        add_test(NAME bits2banking.compiler-ownership.${scenario}
            COMMAND "${CMAKE_COMMAND}" "-DTOOL=$<TARGET_FILE:btb-framework-compiler-ownership>"
                "-DSCENARIO=${scenario}" -P "${CMAKE_CURRENT_SOURCE_DIR}/check.cmake")
        set_tests_properties(bits2banking.compiler-ownership.${scenario} PROPERTIES
            TIMEOUT 10 LABELS "education;framework;compiler;ownership")
    endforeach()
endif()
