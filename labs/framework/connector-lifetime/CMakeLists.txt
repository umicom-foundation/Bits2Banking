# Umicom Bits2Banking
# File: labs/framework/connector-lifetime/CMakeLists.txt
# PURPOSE: Build a small client of the Framework data connector SDK.
# AUTHOR AND ORGANISATION: Sammy Hegab / Umicom Foundation
# LICENCE: MIT
cmake_minimum_required(VERSION 3.26)
project(Bits2BankingConnectorLifetime LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS data)
add_executable(btb-connector-lifetime main.c)
target_link_libraries(btb-connector-lifetime PRIVATE Umicom::data)
include(CTest)
if(BUILD_TESTING)
    add_test(NAME learning.data.connector-lifetime COMMAND btb-connector-lifetime)
    set_tests_properties(learning.data.connector-lifetime PROPERTIES TIMEOUT 10)
endif()
