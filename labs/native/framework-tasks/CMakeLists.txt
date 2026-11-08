#-----------------------------------------------------------------------------
# Bits2Banking
# File: labs/native/framework-tasks/CMakeLists.txt
#
# PURPOSE:
#   Build an installed Framework task consumer and register observable boundary cases.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25)
project(Bits2BankingFrameworkTasks LANGUAGES C)
find_package(UmicomFramework CONFIG REQUIRED)
include(CTest)
add_executable(btb-framework-tasks main.c)
target_link_libraries(btb-framework-tasks PRIVATE Umicom::build)
set_target_properties(btb-framework-tasks PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
if(MSVC)
    target_compile_options(btb-framework-tasks PRIVATE /W4)
else()
    target_compile_options(btb-framework-tasks PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(BUILD_TESTING)
    foreach(case atomic shape owned reset revision)
        add_test(NAME bits2banking.framework-tasks.${case} COMMAND "${CMAKE_COMMAND}" "-DTOOL=$<TARGET_FILE:btb-framework-tasks>" "-DCASE=${case}" -P "${CMAKE_CURRENT_SOURCE_DIR}/check.cmake")
        set_tests_properties(bits2banking.framework-tasks.${case} PROPERTIES TIMEOUT 15)
    endforeach()
endif()
