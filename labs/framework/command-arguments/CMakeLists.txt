#-----------------------------------------------------------------------------
# Bits2Banking
# File: labs/framework/command-arguments/CMakeLists.txt
#
# PURPOSE:
#   Build an installed Framework consumer for literal command arguments.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.26)
project(Bits2BankingCommandArguments LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS developer)
add_executable(btb-command-arguments main.c)
target_link_libraries(btb-command-arguments PRIVATE Umicom::developer)
include(CTest)
if(BUILD_TESTING)
    add_test(NAME learning.build.command-arguments COMMAND btb-command-arguments)
endif()
