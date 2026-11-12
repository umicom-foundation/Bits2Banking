#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-boot-media/CMakeLists.txt
#
# PURPOSE:
#   Compose the installed media consumer with canonical identity and isolated file tests.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)
project(Bits2BankingFrameworkBootMedia LANGUAGES C)
find_package(UmicomFramework CONFIG REQUIRED)
include(CTest)
add_executable(btb-framework-boot-media main.c)
target_link_libraries(btb-framework-boot-media PRIVATE Umicom::boot_media Umicom::platform)
set_target_properties(btb-framework-boot-media PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
if(MSVC)
    target_compile_options(btb-framework-boot-media PRIVATE /W4)
else()
    target_compile_options(btb-framework-boot-media PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(WIN32)
    enable_language(RC)
endif()
# Branding belongs to the installed SDK; no source-checkout paths or artwork copies.
umicom_apply_application_branding(TARGET btb-framework-boot-media
    PRODUCT_NAME "Umicom Boot Media Learning Lab" INTERNAL_NAME btb-framework-boot-media
    NO_RUNTIME_DEPLOYMENT)
if(BUILD_TESTING)
    set(UMICOM_MEDIA_PRACTICE_TOOL "" CACHE FILEPATH "Path to the matching Framework umicom-media-image-example")
    if(NOT EXISTS "${UMICOM_MEDIA_PRACTICE_TOOL}" OR IS_DIRECTORY "${UMICOM_MEDIA_PRACTICE_TOOL}")
        message(FATAL_ERROR "Set UMICOM_MEDIA_PRACTICE_TOOL to the built Framework practice-image executable, or select BUILD_TESTING=OFF for the client alone.")
    endif()
    # Earlier list retained for review; all original exercises remain registered.
    if(FALSE)
    foreach(_case IN ITEMS review copy exists stale confirmation tamper)
    endforeach()
    endif()
    foreach(_case IN ITEMS review copy exists stale confirmation tamper cancel-recheck cancel-write cancel-flush cancel-verify cancel-finished bad-phase)
        add_test(NAME bits2banking.framework-boot-media.${_case}
            COMMAND "${CMAKE_COMMAND}"
                "-DTOOL=$<TARGET_FILE:btb-framework-boot-media>"
                "-DPRACTICE=${UMICOM_MEDIA_PRACTICE_TOOL}"
                "-DCASE=${_case}" "-DWORK=${CMAKE_CURRENT_BINARY_DIR}/practice"
                -P "${CMAKE_CURRENT_SOURCE_DIR}/check.cmake")
        set_tests_properties(bits2banking.framework-boot-media.${_case} PROPERTIES
            TIMEOUT 60 LABELS "education;framework;media;no-devices")
    endforeach()
endif()
