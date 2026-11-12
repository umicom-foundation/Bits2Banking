#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-iso-inspection/CMakeLists.txt
#
# PURPOSE:
#   Build a branded installed-SDK ISO inspection example.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------


cmake_minimum_required(VERSION 3.25)
project(Bits2BankingIsoInspection LANGUAGES C)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS iso_image)
include(CTest)
add_executable(btb-framework-iso-inspection main.c)
target_link_libraries(btb-framework-iso-inspection PRIVATE Umicom::iso_image)
set_target_properties(btb-framework-iso-inspection PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
if(MSVC)
    target_compile_options(btb-framework-iso-inspection PRIVATE /W4)
else()
    target_compile_options(btb-framework-iso-inspection PRIVATE
        -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(WIN32)
    enable_language(RC)
endif()
umicom_apply_application_branding(TARGET btb-framework-iso-inspection
    PRODUCT_NAME "Umicom ISO Inspection Learning Lab"
    INTERNAL_NAME btb-framework-iso-inspection NO_RUNTIME_DEPLOYMENT)
if(BUILD_TESTING)
    foreach(_case IN ITEMS bios efi-zero efi-one endian bios-zero read-failure
        prefix-short prefix-unknown prefix-truncated prefix-sector prefix-read-failure retained-error retained-noniso)
        add_test(NAME bits2banking.iso-inspection.${_case}
            COMMAND "${CMAKE_COMMAND}"
                "-DTOOL=$<TARGET_FILE:btb-framework-iso-inspection>"
                "-DCASE=${_case}"
                -P "${CMAKE_CURRENT_SOURCE_DIR}/check.cmake")
        set_tests_properties(bits2banking.iso-inspection.${_case} PROPERTIES
            TIMEOUT 10 LABELS "education;framework;iso;no-devices")
    endforeach()
endif()
