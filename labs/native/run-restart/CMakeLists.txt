#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/run-restart/CMakeLists.txt
#
# PURPOSE:
#   Build a portable installed-SDK restart lifecycle exercise.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25)
project(RunRestartLab LANGUAGES C)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS build platform)
add_executable(run-restart main.c)
set_target_properties(run-restart PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
target_link_libraries(run-restart PRIVATE Umicom::build Umicom::platform)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(run-restart PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
include(CTest)
if(BUILD_TESTING)
    foreach(case restart handover stop revoke)
        add_test(NAME "run-restart.${case}" COMMAND run-restart "$<TARGET_FILE:run-restart>" "${case}")
        set_tests_properties("run-restart.${case}" PROPERTIES TIMEOUT 30
            PASS_REGULAR_EXPRESSION "scenario=${case} old-results=1 executor-calls=[12] child-processes=0")
    endforeach()
endif()
