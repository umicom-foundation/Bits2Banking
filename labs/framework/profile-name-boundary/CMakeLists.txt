# Umicom Bits2Banking
# File: labs/framework/profile-name-boundary/CMakeLists.txt
# PURPOSE: Build a consumer of Framework's exact-length profile-name contract.
# AUTHOR AND ORGANISATION: Sammy Hegab / Umicom Foundation
# LICENCE: MIT
cmake_minimum_required(VERSION 3.26)
project(Bits2BankingProfileName LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS security)
add_executable(btb-profile-name main.c)
target_link_libraries(btb-profile-name PRIVATE Umicom::security)
include(CTest)
if(BUILD_TESTING)
    add_executable(btb-profile-name-test test_name.c)
    target_link_libraries(btb-profile-name-test PRIVATE Umicom::security)
    add_test(NAME btb.profile_name.boundaries COMMAND btb-profile-name-test)
    add_test(NAME btb.profile_name.example COMMAND btb-profile-name)
    set_tests_properties(btb.profile_name.example PROPERTIES PASS_REGULAR_EXPRESSION "Canonical name: alice_7")
endif()
