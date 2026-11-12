#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-toolchain-selection/CMakeLists.txt
#
# PURPOSE:
#   Build an installed-SDK client for coherent toolchain and child-environment selection.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)
project(Bits2BankingToolchainSelection LANGUAGES C)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS compiler toolchain)
include(CTest)
add_executable(btb-framework-toolchain-selection main.c)
target_link_libraries(btb-framework-toolchain-selection PRIVATE Umicom::compiler Umicom::toolchain)
set_target_properties(btb-framework-toolchain-selection PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
if(MSVC)
    target_compile_options(btb-framework-toolchain-selection PRIVATE /W4)
else()
    target_compile_options(btb-framework-toolchain-selection PRIVATE
        -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(WIN32)
    enable_language(RC)
endif()
umicom_apply_application_branding(TARGET btb-framework-toolchain-selection
    PRODUCT_NAME "Umicom Toolchain Selection Learning Lab"
    INTERNAL_NAME btb-framework-toolchain-selection NO_RUNTIME_DEPLOYMENT)
if(BUILD_TESTING)
    foreach(scenario storage selection compiler pic)
        add_test(NAME bits2banking.toolchain-selection.${scenario}
            COMMAND "${CMAKE_COMMAND}" "-DTOOL=$<TARGET_FILE:btb-framework-toolchain-selection>"
                "-DSCENARIO=${scenario}" -P "${CMAKE_CURRENT_SOURCE_DIR}/check.cmake")
        set_tests_properties(bits2banking.toolchain-selection.${scenario} PROPERTIES
            TIMEOUT 30 LABELS "education;framework;toolchain;ownership")
    endforeach()
endif()
