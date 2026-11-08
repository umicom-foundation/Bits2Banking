#-----------------------------------------------------------------------------
# Bits2Banking
# File: labs/native/framework-task-graph/CMakeLists.txt
#
# PURPOSE:
#   Build an installed Framework task graph consumer and register observable boundary cases.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25)
project(Bits2BankingFrameworkTaskGraph LANGUAGES C)
find_package(UmicomFramework CONFIG REQUIRED)
include(CTest)
add_executable(btb-framework-task-graph main.c)
target_link_libraries(btb-framework-task-graph PRIVATE Umicom::build)
set_target_properties(btb-framework-task-graph PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
if(MSVC)
    target_compile_options(btb-framework-task-graph PRIVATE /W4)
else()
    target_compile_options(btb-framework-task-graph PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(BUILD_TESTING)
    foreach(case complete fail retry cancel reject)
        add_test(NAME bits2banking.framework-task-graph.${case} COMMAND "${CMAKE_COMMAND}" "-DTOOL=$<TARGET_FILE:btb-framework-task-graph>" "-DCASE=${case}" -P "${CMAKE_CURRENT_SOURCE_DIR}/check.cmake")
        set_tests_properties(bits2banking.framework-task-graph.${case} PROPERTIES TIMEOUT 15)
    endforeach()
endif()
