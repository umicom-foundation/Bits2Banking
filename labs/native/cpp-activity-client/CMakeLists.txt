# -----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/cpp-activity-client/CMakeLists.txt
#
# PURPOSE:
#   Keep the model compiled as C while building a C++ caller.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
# -----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.24)
project(BtbCppActivity LANGUAGES C CXX)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
include(CTest)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS base)
add_library(btb-c-activity STATIC
    ../framework-activity/activity.c ../activity-adapters/bridge.c)
target_link_libraries(btb-c-activity PUBLIC Umicom::base)
add_executable(btb-cpp-activity main.cpp)
target_link_libraries(btb-cpp-activity PRIVATE btb-c-activity)
if(BUILD_TESTING)
    add_executable(btb-cpp-activity-test test_client.cpp)
    target_link_libraries(btb-cpp-activity-test PRIVATE btb-c-activity)
    add_test(NAME bits2banking.cpp.c_boundary COMMAND btb-cpp-activity-test)
    set_tests_properties(bits2banking.cpp.c_boundary PROPERTIES TIMEOUT 10)
endif()
