#-----------------------------------------------------------------------------
# Bits2Banking
# File: labs/native/framework-task-orchestration/CMakeLists.txt
#
# PURPOSE:
#   Build an installed Framework task orchestrator consumer and register observable boundary cases.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25)
project(Bits2BankingFrameworkTaskOrchestration LANGUAGES C)
find_package(UmicomFramework CONFIG REQUIRED)
include(CTest)
add_executable(btb-framework-task-orchestration main.c)
target_link_libraries(btb-framework-task-orchestration PRIVATE Umicom::build)
set_target_properties(btb-framework-task-orchestration PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
if(MSVC)
    target_compile_options(btb-framework-task-orchestration PRIVATE /W4)
else()
    target_compile_options(btb-framework-task-orchestration PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(BUILD_TESTING)
    foreach(case selected parallel stop retry reject)
        add_test(NAME bits2banking.framework-task-orchestration.${case} COMMAND "${CMAKE_COMMAND}" "-DTOOL=$<TARGET_FILE:btb-framework-task-orchestration>" "-DCASE=${case}" -P "${CMAKE_CURRENT_SOURCE_DIR}/check.cmake")
        set_tests_properties(bits2banking.framework-task-orchestration.${case} PROPERTIES TIMEOUT 15)
    endforeach()
endif()
