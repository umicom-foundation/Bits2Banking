# Umicom Bits2Banking
# File: labs/framework/message-retry/CMakeLists.txt
# PURPOSE: Build small clients of the Framework messaging SDK.
# AUTHOR AND ORGANISATION: Sammy Hegab / Umicom Foundation
# LICENCE: MIT
cmake_minimum_required(VERSION 3.26)
project(Bits2BankingMessageRetry LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS messaging)
add_executable(btb-message-retry main.c)
target_link_libraries(btb-message-retry PRIVATE Umicom::messaging)
include(CTest)
if(BUILD_TESTING)
    add_executable(btb-message-retry-test test_retry.c)
    target_link_libraries(btb-message-retry-test PRIVATE Umicom::messaging)
    add_test(NAME learning.messaging.boundaries COMMAND btb-message-retry-test)
    add_test(NAME learning.messaging.example COMMAND btb-message-retry)
    set_tests_properties(learning.messaging.example PROPERTIES PASS_REGULAR_EXPRESSION "Retry result: report prepared")
endif()
