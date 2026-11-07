# Umicom Bits2Banking
# File: labs/framework/boot-report/CMakeLists.txt
# PURPOSE: Build a client of the canonical installed platform service.
# AUTHOR AND ORGANISATION: Sammy Hegab / Umicom Foundation
# LICENCE: MIT
cmake_minimum_required(VERSION 3.26)
project(Bits2BankingBootReport LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS platform)
add_executable(btb-boot-report main.c)
target_link_libraries(btb-boot-report PRIVATE Umicom::platform)
include(CTest)
if(BUILD_TESTING)
    add_executable(btb-boot-report-test test_report.c)
    target_link_libraries(btb-boot-report-test PRIVATE Umicom::platform)
    add_test(NAME bits2banking.boot-report.contract COMMAND btb-boot-report-test)
    add_test(NAME bits2banking.boot-report.ready COMMAND btb-boot-report "${CMAKE_CURRENT_SOURCE_DIR}/fixtures/ready.report")
    add_test(NAME bits2banking.boot-report.recovery COMMAND btb-boot-report "${CMAKE_CURRENT_SOURCE_DIR}/fixtures/recovery.report")
    add_test(NAME bits2banking.boot-report.invalid COMMAND btb-boot-report "${CMAKE_CURRENT_SOURCE_DIR}/fixtures/invalid.report")
    set_tests_properties(bits2banking.boot-report.invalid PROPERTIES WILL_FAIL TRUE)
    set_tests_properties(bits2banking.boot-report.contract bits2banking.boot-report.ready
        bits2banking.boot-report.recovery bits2banking.boot-report.invalid PROPERTIES TIMEOUT 10)
endif()
