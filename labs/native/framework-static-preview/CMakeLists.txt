#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-static-preview/CMakeLists.txt
#
# PURPOSE:
#   Build the headless static-preview client against the installed Framework web component.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.24)
project(BtbStaticPreview LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS web)
add_executable(btb-static-preview main.c)
target_link_libraries(btb-static-preview PRIVATE Umicom::web)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(btb-static-preview PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(WIN32)
    enable_language(RC)
endif()
# Installed Framework owns the artwork and Windows shell identity.
umicom_apply_application_branding(TARGET btb-static-preview
    PRODUCT_NAME "Umicom Static Preview Learning Lab" INTERNAL_NAME btb-static-preview
    NO_RUNTIME_DEPLOYMENT)
if(BUILD_TESTING)
    foreach(case get head nested missing traversal post owned-get owned-head owned-svg owned-ico legacy-svg)
        set(_fixture_root "${CMAKE_CURRENT_SOURCE_DIR}/site")
        if(case MATCHES "(svg|ico)$")
            get_filename_component(_fixture_root "${UMICOM_FRAMEWORK_RESOURCE_ROOT}/brand" ABSOLUTE)
        endif()
        add_test(NAME bits2banking.static_preview.${case} COMMAND "${CMAKE_COMMAND}"
            "-DTOOL=$<TARGET_FILE:btb-static-preview>" "-DROOT=${_fixture_root}"
            "-DCASE=${case}" -P "${CMAKE_CURRENT_SOURCE_DIR}/check.cmake")
        set_tests_properties(bits2banking.static_preview.${case} PROPERTIES TIMEOUT 20)
    endforeach()
endif()
