#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/framework/identity-lifecycle/CMakeLists.txt
#
# PURPOSE:
#   Build an SDK client that demonstrates identity and session boundaries.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.26)
project(Bits2BankingIdentityLifecycle LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS security)
add_executable(btb-identity-lifecycle main.c)
target_link_libraries(btb-identity-lifecycle PRIVATE Umicom::security)
include(CTest)
if(BUILD_TESTING)
    add_test(NAME learning.security.identity-lifecycle COMMAND btb-identity-lifecycle)
    set_tests_properties(learning.security.identity-lifecycle PROPERTIES TIMEOUT 15)
endif()
