# -----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/activity-adapters/CMakeLists.txt
#
# PURPOSE:
#   Build host checks for adapters sharing the existing activity implementation.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
# -----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(BtbActivityAdapters LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS base)
add_library(btb-activity-adapters STATIC
    ../framework-activity/activity.c bridge.c button.c)
target_include_directories(btb-activity-adapters PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(btb-activity-adapters PUBLIC Umicom::base)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(btb-activity-adapters PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(BUILD_TESTING)
    foreach(_part IN ITEMS bridge button)
        add_executable("btb-activity-${_part}-test" "test_${_part}.c")
        target_link_libraries("btb-activity-${_part}-test" PRIVATE btb-activity-adapters)
        add_test(NAME "bits2banking.activity_adapter.${_part}" COMMAND "btb-activity-${_part}-test")
        set_tests_properties("bits2banking.activity_adapter.${_part}" PROPERTIES TIMEOUT 10)
    endforeach()
endif()

