# Umicom Bits2Banking
# File: CMakeLists.txt
# PURPOSE: Build original treasury consumers against an installed Framework SDK.
# AUTHOR AND ORGANISATION: Sammy Hegab / Umicom Foundation
# LICENCE: MIT
cmake_minimum_required(VERSION 3.24)
project(TreasuryFrameworkBridge LANGUAGES C CXX)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS finance)
add_executable(treasury-forecast forecast.c)
set_target_properties(treasury-forecast PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
target_link_libraries(treasury-forecast PRIVATE Umicom::finance)
add_executable(treasury-forecast-cpp forecast_cpp.cpp)
set_target_properties(treasury-forecast-cpp PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)
target_link_libraries(treasury-forecast-cpp PRIVATE Umicom::finance)
include(CTest)
if(BUILD_TESTING)
    add_test(NAME treasury.bridge.contract COMMAND ${CMAKE_COMMAND}
        -DPROGRAM=$<TARGET_FILE:treasury-forecast> -P ${CMAKE_CURRENT_SOURCE_DIR}/check_contract.cmake)
    add_test(NAME treasury.bridge.cpp COMMAND treasury-forecast-cpp)
    set_tests_properties(treasury.bridge.contract treasury.bridge.cpp PROPERTIES TIMEOUT 15)
endif()
