#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/framework/qt-component-model/CMakeLists.txt
#
# PURPOSE:
#   Build an installed-SDK Qt model adapter and its signal contract checks.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.26)
project(Bits2BankingQtComponentModel LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)

# This native SDK exercise deliberately requires matching installed C artifacts.
# Cross-target profile lessons use their separately documented portable target.
if(CMAKE_CROSSCOMPILING)
    message(FATAL_ERROR "Use a native Qt kit and matching Framework SDK for this model lab")
endif()
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS ui_components)
find_package(Qt6 6.5 CONFIG REQUIRED COMPONENTS Core)
add_library(btb-qt-component-model STATIC component_model.cpp component_model.h)
target_link_libraries(btb-qt-component-model PUBLIC Umicom::ui_components Qt6::Core)
target_include_directories(btb-qt-component-model PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(btb-qt-component-demo main.cpp)
target_link_libraries(btb-qt-component-demo PRIVATE btb-qt-component-model)
umicom_apply_application_branding(
    TARGET btb-qt-component-demo
    PRODUCT_NAME "Umicom Component Model Laboratory"
    INTERNAL_NAME "btb-qt-component-demo"
    NO_RUNTIME_DEPLOYMENT)

include(CTest)
if(BUILD_TESTING)
    find_package(Qt6 6.5 CONFIG REQUIRED COMPONENTS Test)
    add_executable(btb-qt-component-test test_model.cpp)
    target_link_libraries(btb-qt-component-test PRIVATE btb-qt-component-model Qt6::Test)
    add_test(NAME btb.qt_component_model.contract COMMAND btb-qt-component-test)
    set_tests_properties(btb.qt_component_model.contract PROPERTIES
        TIMEOUT 30 LABELS "learning;qt;framework;model")
    umicom_apply_application_branding(
        TARGET btb-qt-component-test
        PRODUCT_NAME "Umicom Component Model Checks"
        INTERNAL_NAME "btb-qt-component-test"
        NO_RUNTIME_DEPLOYMENT)
endif()
