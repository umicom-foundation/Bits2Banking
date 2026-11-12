#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-build-history/CMakeLists.txt
#
# PURPOSE:
#   Build an installed-SDK client that observes preparation failure history.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)
project(Bits2BankingBuildHistory LANGUAGES C)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS build)
include(CTest)
add_executable(btb-framework-build-history main.c)
target_link_libraries(btb-framework-build-history PRIVATE Umicom::build)
set_target_properties(btb-framework-build-history PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
if(MSVC)
    target_compile_options(btb-framework-build-history PRIVATE /W4)
else()
    target_compile_options(btb-framework-build-history PRIVATE
        -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(WIN32)
    enable_language(RC)
endif()
umicom_apply_application_branding(TARGET btb-framework-build-history
    PRODUCT_NAME "Umicom Build History Learning Lab"
    INTERNAL_NAME btb-framework-build-history NO_RUNTIME_DEPLOYMENT)
if(BUILD_TESTING)
    foreach(scenario single rolling shared no-history invalid copy)
        add_test(NAME bits2banking.build-history.${scenario}
            COMMAND "${CMAKE_COMMAND}" "-DTOOL=$<TARGET_FILE:btb-framework-build-history>"
                "-DSCENARIO=${scenario}" -P "${CMAKE_CURRENT_SOURCE_DIR}/check.cmake")
        set_tests_properties(bits2banking.build-history.${scenario} PROPERTIES
            TIMEOUT 10 LABELS "education;framework;build;history;no-child-process")
    endforeach()
endif()
