#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/graphics/raster-from-scratch/CMakeLists.txt
#
# PURPOSE:
#   Build and qualify the C, optional Assembly, and optional GTK4 raster examples.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25)
project(UmicomRasterLesson LANGUAGES C)
include(CTest)

option(UMICOM_RASTER_ASSEMBLY "Use the x86-64 span implementation" OFF)
option(UMICOM_RASTER_GTK4_BRIDGE "Build a GTK4 texture adapter without a GUI target" OFF)
set(UMICOM_FRAMEWORK_SOURCE "" CACHE PATH "Matching Framework checkout providing the branding helper")

add_library(umicom_raster STATIC raster.c)
target_include_directories(umicom_raster PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(umicom_raster PUBLIC c_std_23)
set_target_properties(umicom_raster PROPERTIES C_EXTENSIONS OFF)

if(UMICOM_RASTER_ASSEMBLY)
    # The same leaf routine handles Win64 COFF and Linux ELF entry registers.
    if(NOT CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|AMD64|amd64)$"
            OR NOT CMAKE_C_COMPILER_ID MATCHES "GNU|Clang"
            OR NOT (WIN32 OR CMAKE_SYSTEM_NAME STREQUAL "Linux"))
        message(FATAL_ERROR "The Assembly lesson requires x86-64 Windows GNU/Clang or Linux GNU/Clang")
    endif()
    enable_language(ASM)
    target_sources(umicom_raster PRIVATE span_x86_64.S)
    target_compile_definitions(umicom_raster PRIVATE UMICOM_RASTER_USE_ASM)
endif()

function(raster_enable_warnings target)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options("${target}" PRIVATE
            "$<$<COMPILE_LANGUAGE:C>:-Wall;-Wextra;-Wpedantic;-Wconversion;-Wshadow;-Werror>")
    endif()
endfunction()

add_executable(umicom-raster-example main.c)
target_link_libraries(umicom-raster-example PRIVATE umicom_raster)
set_target_properties(umicom-raster-example PROPERTIES C_EXTENSIONS OFF)
raster_enable_warnings(umicom-raster-example)
raster_enable_warnings(umicom_raster)

if(WIN32)
    # Resource packaging is shared with the other native Bits2Banking labs.
    if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
        message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE to the primary Framework checkout for Windows branding")
    endif()
    enable_language(RC)
    set(UMICOM_FRAMEWORK_RESOURCE_ROOT "${UMICOM_FRAMEWORK_SOURCE}/resources")
    include("${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
    umicom_apply_application_branding(TARGET umicom-raster-example
        PRODUCT_NAME "Umicom Raster Laboratory"
        INTERNAL_NAME "umicom-raster-example" NO_RUNTIME_DEPLOYMENT)
endif()

if(UMICOM_RASTER_GTK4_BRIDGE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)
    add_library(umicom_raster_gtk4 STATIC gtk4_texture.c)
    target_link_libraries(umicom_raster_gtk4 PUBLIC umicom_raster PkgConfig::GTK4)
    set_target_properties(umicom_raster_gtk4 PROPERTIES C_EXTENSIONS OFF)
    raster_enable_warnings(umicom_raster_gtk4)
endif()

if(BUILD_TESTING)
    add_executable(umicom-raster-test test_raster.c)
    target_link_libraries(umicom-raster-test PRIVATE umicom_raster)
    set_target_properties(umicom-raster-test PROPERTIES C_EXTENSIONS OFF)
    raster_enable_warnings(umicom-raster-test)
    add_test(NAME lesson.graphics.raster.invariants COMMAND umicom-raster-test)
    add_test(NAME lesson.graphics.raster.ppm
        COMMAND "${CMAKE_COMMAND}" "-DEXAMPLE=$<TARGET_FILE:umicom-raster-example>"
            "-DWORK=${CMAKE_CURRENT_BINARY_DIR}/test-work" -P "${CMAKE_CURRENT_SOURCE_DIR}/check_ppm.cmake")
    set_tests_properties(lesson.graphics.raster.invariants lesson.graphics.raster.ppm PROPERTIES TIMEOUT 20)
    if(UMICOM_RASTER_GTK4_BRIDGE)
        # Verify texture ownership independently of the window system.
        add_executable(umicom-raster-texture-test test_texture.c)
        target_link_libraries(umicom-raster-texture-test PRIVATE umicom_raster_gtk4)
        set_target_properties(umicom-raster-texture-test PROPERTIES C_EXTENSIONS OFF)
        raster_enable_warnings(umicom-raster-texture-test)
        add_test(NAME lesson.graphics.raster.texture-snapshot COMMAND umicom-raster-texture-test)
        set_tests_properties(lesson.graphics.raster.texture-snapshot PROPERTIES TIMEOUT 20)
    endif()
endif()
