# -----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/c-build-stages/CMakeLists.txt
#
# PURPOSE:
#   Build a small installed-SDK consumer for studying native C build stages.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
# -----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.26)
project(Bits2BankingBuildStages LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
find_package(UmicomC CONFIG REQUIRED)
add_library(btb-stage-runner STATIC runner.c)
target_include_directories(btb-stage-runner PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(btb-stage-runner PUBLIC UmicomC::Compiler)
add_executable(btb-build-stages main.c)
target_link_libraries(btb-build-stages PRIVATE btb-stage-runner)
include(CTest)
if(BUILD_TESTING)
    add_executable(btb-stage-test test_runner.c)
    target_link_libraries(btb-stage-test PRIVATE btb-stage-runner)
    add_test(NAME bits2banking.c-build-stages.boundaries COMMAND btb-stage-test)
    set_tests_properties(bits2banking.c-build-stages.boundaries PROPERTIES TIMEOUT 10)
endif()
