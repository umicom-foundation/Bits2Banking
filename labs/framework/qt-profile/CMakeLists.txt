#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/framework/qt-profile/CMakeLists.txt
#
# PURPOSE:
#   Build one Qt presentation over Framework C for desktop and explicit cross-target kits.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.26)
project(Bits2BankingQtProfile LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# C++ is required by Qt Widgets. Validation remains in the same Framework C23
# source for all targets; no copied algorithm or host archive is used here.
set(BTB_FRAMEWORK_SOURCE "" CACHE PATH "Absolute Framework source root for the portable C target")
if(BTB_FRAMEWORK_SOURCE)
    if(NOT IS_ABSOLUTE "${BTB_FRAMEWORK_SOURCE}" OR
       NOT EXISTS "${BTB_FRAMEWORK_SOURCE}/cmake/UmicomProfileName.cmake")
        message(FATAL_ERROR "BTB_FRAMEWORK_SOURCE must name an absolute Framework root containing UmicomProfileName.cmake")
    endif()
    include("${BTB_FRAMEWORK_SOURCE}/cmake/UmicomProfileName.cmake")
else()
    if(CMAKE_CROSSCOMPILING)
        message(FATAL_ERROR "Set BTB_FRAMEWORK_SOURCE for this cross-target lab; a desktop Framework SDK is not a target SDK")
    endif()
    find_package(UmicomFramework CONFIG REQUIRED COMPONENTS profile_name)
endif()
find_package(Qt6 6.5 CONFIG REQUIRED COMPONENTS Widgets)
add_library(btb-qt-profile-view STATIC profile_window.cpp)
# Android's application module links this static view, so it must be relocatable.
set_target_properties(btb-qt-profile-view PROPERTIES POSITION_INDEPENDENT_CODE YES)
target_link_libraries(btb-qt-profile-view PUBLIC Umicom::profile_name Qt6::Widgets)
# Qt selects the application type and deployment finalization for the active kit.
qt6_add_executable(btb-qt-profile main.cpp)
target_link_libraries(btb-qt-profile PRIVATE btb-qt-profile-view)
if(APPLE)
    set_target_properties(btb-qt-profile PROPERTIES MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_GUI_IDENTIFIER "org.umicom.education.profilelab")
endif()
include(CTest)
if(BUILD_TESTING AND NOT CMAKE_CROSSCOMPILING)
    find_package(Qt6 CONFIG REQUIRED COMPONENTS Test)
    qt6_add_executable(btb-qt-profile-test test_window.cpp)
    target_link_libraries(btb-qt-profile-test PRIVATE btb-qt-profile-view Qt6::Test)
    add_test(NAME btb.qt_profile.events COMMAND btb-qt-profile-test -platform offscreen)
    set_tests_properties(btb.qt_profile.events PROPERTIES TIMEOUT 20 LABELS "learning;qt;profile")
elseif(BUILD_TESTING)
    message(STATUS "Cross-target build: desktop event CTest is not registered; qualify the browser or device separately")
endif()

# The previous desktop composition is retained for review. The portable target
# replaces the security dependency; Qt application creation replaces the host-only
# executable rule while preserving the form, callback and desktop event contract.
if(FALSE)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS security)
find_package(Qt6 CONFIG REQUIRED COMPONENTS Widgets)
add_library(btb-qt-profile-view STATIC profile_window.cpp)
target_link_libraries(btb-qt-profile-view PUBLIC Umicom::security Qt6::Widgets)
add_executable(btb-qt-profile main.cpp)
target_link_libraries(btb-qt-profile PRIVATE btb-qt-profile-view)
include(CTest)
if(BUILD_TESTING)
    find_package(Qt6 CONFIG REQUIRED COMPONENTS Test)
    add_executable(btb-qt-profile-test test_window.cpp)
    target_link_libraries(btb-qt-profile-test PRIVATE btb-qt-profile-view Qt6::Test)
    add_test(NAME btb.qt_profile.events COMMAND btb-qt-profile-test -platform offscreen)
    set_tests_properties(btb.qt_profile.events PROPERTIES TIMEOUT 20 LABELS "learning;qt;profile")
endif()
endif()
