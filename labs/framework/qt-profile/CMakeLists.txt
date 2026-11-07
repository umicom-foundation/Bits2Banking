# Umicom Bits2Banking
# File: labs/framework/qt-profile/CMakeLists.txt
# PURPOSE: Build a Qt-only presentation layer over the installed C Framework.
# AUTHOR AND ORGANISATION: Sammy Hegab / Umicom Foundation
# LICENCE: MIT
cmake_minimum_required(VERSION 3.26)
project(Bits2BankingQtProfile LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
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
