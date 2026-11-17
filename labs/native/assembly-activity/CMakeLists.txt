# Umicom Bits2Banking
# File: labs/native/assembly-activity/CMakeLists.txt
# 
# PURPOSE:
# Build a C caller and GNU-style x86-64 assembly wrapper against the installed Framework SDK.
# 
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
# 
# LICENCE:
# MIT
# 
cmake_minimum_required(VERSION 3.24)
project(BtbAssemblyActivity LANGUAGES C ASM)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)
if(NOT CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|AMD64|amd64)$" OR NOT CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    message(FATAL_ERROR "This lab requires GNU-style assembly on x86-64 Windows or Linux")
endif()
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS base)
add_executable(btb-assembly-activity main.c forward.S ../activity-adapters/bridge.c ../framework-activity/activity.c)
target_link_libraries(btb-assembly-activity PRIVATE Umicom::base)
if(BUILD_TESTING)
    add_test(NAME bits2banking.assembly.c_boundary COMMAND btb-assembly-activity)
    set_tests_properties(bits2banking.assembly.c_boundary PROPERTIES TIMEOUT 10)
endif()
