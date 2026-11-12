#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-ui-values/CMakeLists.txt
#
# PURPOSE:
#   Build an installed-SDK client for owned UI value and reactive admission.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)
project(Bits2BankingUiValues LANGUAGES C)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS ui)
include(CTest)
add_executable(btb-framework-ui-values main.c)
target_link_libraries(btb-framework-ui-values PRIVATE Umicom::ui)
set_target_properties(btb-framework-ui-values PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
if(MSVC)
    target_compile_options(btb-framework-ui-values PRIVATE /W4)
else()
    target_compile_options(btb-framework-ui-values PRIVATE
        -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(WIN32)
    enable_language(RC)
endif()
umicom_apply_application_branding(TARGET btb-framework-ui-values
    PRODUCT_NAME "Umicom UI Value Learning Lab"
    INTERNAL_NAME btb-framework-ui-values NO_RUNTIME_DEPLOYMENT)
if(BUILD_TESTING)
    foreach(scenario alias refused-title publish invalid-value revision archive)
        add_test(NAME bits2banking.ui-values.${scenario}
            COMMAND "${CMAKE_COMMAND}" "-DTOOL=$<TARGET_FILE:btb-framework-ui-values>"
                "-DSCENARIO=${scenario}" -P "${CMAKE_CURRENT_SOURCE_DIR}/check.cmake")
        set_tests_properties(bits2banking.ui-values.${scenario} PROPERTIES
            TIMEOUT 10 LABELS "education;framework;ui;ownership")
    endforeach()
endif()
