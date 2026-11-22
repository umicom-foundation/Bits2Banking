#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: apps/desktop/CMakeLists.txt
#
# PURPOSE:
#   Build the standalone desktop catalogue against one installed Umicom SDK.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#---------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)
project(UmicomBits2BankingDesktop VERSION 0.1.0 LANGUAGES C)

include(CTest)
include(GNUInstallDirs)

set(UMICOM_SDK_ROOT "" CACHE PATH "Absolute Umicom Framework SDK install prefix")
if(NOT IS_ABSOLUTE "${UMICOM_SDK_ROOT}" OR NOT IS_DIRECTORY "${UMICOM_SDK_ROOT}")
    message(FATAL_ERROR "Set UMICOM_SDK_ROOT to the absolute installed Umicom Framework SDK prefix.")
endif()

# Resolve the same SDK ownership and branding checks used by native consumers.
find_package(UmicomFramework 0.9 CONFIG REQUIRED COMPONENTS learning_catalogue_gtk4 platform
    PATHS "${UMICOM_SDK_ROOT}" NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
if(NOT COMMAND umicom_require_installed_sdk OR NOT COMMAND umicom_require_sdk_environment OR
   NOT COMMAND umicom_apply_application_branding)
    message(FATAL_ERROR "The selected SDK must provide its installed identity and branding helpers.")
endif()
umicom_require_installed_sdk("${UMICOM_SDK_ROOT}" Umicom::learning_catalogue_gtk4 Umicom::platform)
umicom_require_sdk_environment(2)

add_executable(umicom-bits2banking main.c)
target_link_libraries(umicom-bits2banking PRIVATE Umicom::learning_catalogue_gtk4 Umicom::platform)
set_target_properties(umicom-bits2banking PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
if(MSVC)
    target_compile_options(umicom-bits2banking PRIVATE /W4)
elseif(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(umicom-bits2banking PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
umicom_apply_application_branding(TARGET umicom-bits2banking
    PRODUCT_NAME "Umicom Bits2Banking" INTERNAL_NAME "umicom-bits2banking"
    APPLICATION_ID "org.umicom.bits2banking" VERSION_MAJOR 0 VERSION_MINOR 1 VERSION_PATCH 0
    DESKTOP_ENTRY NO_RUNTIME_DEPLOYMENT)
install(TARGETS umicom-bits2banking RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")

if(BUILD_TESTING)
    # Exercise argument admission before GTK registration or application launch.
    foreach(case help root-only manifest-only relative-root parent-manifest duplicate extra)
        add_test(NAME "bits2banking.desktop.arguments.${case}"
            COMMAND "${CMAKE_COMMAND}" "-DTOOL=$<TARGET_FILE:umicom-bits2banking>"
                "-DCASE=${case}" "-DROOT=${CMAKE_CURRENT_SOURCE_DIR}"
                -P "${CMAKE_CURRENT_SOURCE_DIR}/tests/check_arguments.cmake")
        set_tests_properties("bits2banking.desktop.arguments.${case}" PROPERTIES TIMEOUT 15)
    endforeach()
endif()
