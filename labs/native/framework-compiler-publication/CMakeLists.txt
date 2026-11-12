#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-compiler-publication/CMakeLists.txt
#
# PURPOSE:
#   Build an installed-SDK client for coherent compiler metadata publication.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)
project(Bits2BankingCompilerPublication LANGUAGES C)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS compiler)
include(CTest)
add_executable(btb-framework-compiler-publication main.c)
target_link_libraries(btb-framework-compiler-publication PRIVATE Umicom::compiler)
set_target_properties(btb-framework-compiler-publication PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
if(MSVC)
    target_compile_options(btb-framework-compiler-publication PRIVATE /W4)
else()
    target_compile_options(btb-framework-compiler-publication PRIVATE
        -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(WIN32)
    enable_language(RC)
endif()
umicom_apply_application_branding(TARGET btb-framework-compiler-publication
    PRODUCT_NAME "Umicom Compiler Publication Learning Lab"
    INTERNAL_NAME btb-framework-compiler-publication NO_RUNTIME_DEPLOYMENT)
if(BUILD_TESTING)
    foreach(scenario keys transaction refresh policy)
        add_test(NAME bits2banking.compiler-publication.${scenario}
            COMMAND "${CMAKE_COMMAND}" "-DTOOL=$<TARGET_FILE:btb-framework-compiler-publication>"
                "-DSCENARIO=${scenario}" -P "${CMAKE_CURRENT_SOURCE_DIR}/check.cmake")
        set_tests_properties(bits2banking.compiler-publication.${scenario} PROPERTIES
            TIMEOUT 30 LABELS "education;framework;compiler;publication")
    endforeach()
endif()
