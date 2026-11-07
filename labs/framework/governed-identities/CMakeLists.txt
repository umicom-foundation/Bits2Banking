#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/framework/governed-identities/CMakeLists.txt
#
# PURPOSE:
#   Build the governed identity client against the installed Framework security SDK.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.26)
project(Bits2BankingGovernedIdentities LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS security)
add_executable(btb-governed-identities main.c)
target_link_libraries(btb-governed-identities PRIVATE Umicom::security)
include(CTest)
if(BUILD_TESTING)
    add_test(NAME learning.security.governed-identities COMMAND btb-governed-identities)
    set_tests_properties(learning.security.governed-identities PROPERTIES TIMEOUT 15)
endif()
