#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-compiler-preview/CMakeLists.txt
#
# PURPOSE:
#   Build an installed-SDK client for compiler action planning and JSON preview.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)
project(Bits2BankingCompilerPreview LANGUAGES C)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS compiler)
include(CTest)
add_executable(btb-framework-compiler-preview main.c)
target_link_libraries(btb-framework-compiler-preview PRIVATE Umicom::compiler)
set_target_properties(btb-framework-compiler-preview PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
if(MSVC)
    target_compile_options(btb-framework-compiler-preview PRIVATE /W4)
else()
    target_compile_options(btb-framework-compiler-preview PRIVATE
        -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(WIN32)
    enable_language(RC)
endif()
umicom_apply_application_branding(TARGET btb-framework-compiler-preview
    PRODUCT_NAME "Umicom Compiler Preview Learning Lab"
    INTERNAL_NAME btb-framework-compiler-preview NO_RUNTIME_DEPLOYMENT)
if(BUILD_TESTING)
    foreach(scenario actions identity json refusal)
        add_test(NAME bits2banking.compiler-preview.${scenario}
            COMMAND "${CMAKE_COMMAND}" "-DTOOL=$<TARGET_FILE:btb-framework-compiler-preview>"
                "-DSCENARIO=${scenario}" -P "${CMAKE_CURRENT_SOURCE_DIR}/check.cmake")
        set_tests_properties(bits2banking.compiler-preview.${scenario} PROPERTIES
            TIMEOUT 10 LABELS "education;framework;compiler;preview")
    endforeach()
endif()
