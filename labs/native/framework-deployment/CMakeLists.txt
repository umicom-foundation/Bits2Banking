#-----------------------------------------------------------------------------
# Bits2Banking
# File: labs/native/framework-deployment/CMakeLists.txt
#
# PURPOSE:
#   Build an installed Framework deployment-model consumer and register five observable scenarios.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25)
project(Bits2BankingFrameworkDeployment LANGUAGES C)
find_package(UmicomFramework CONFIG REQUIRED)
include(CTest)
add_executable(btb-framework-deployment main.c)
target_link_libraries(btb-framework-deployment PRIVATE Umicom::build)
set_target_properties(btb-framework-deployment PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
if(MSVC)
    target_compile_options(btb-framework-deployment PRIVATE /W4)
else()
    target_compile_options(btb-framework-deployment PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(BUILD_TESTING)
    foreach(case complete fail rollback cancel revise)
        add_test(NAME bits2banking.framework-deployment.${case} COMMAND "${CMAKE_COMMAND}"
            "-DTOOL=$<TARGET_FILE:btb-framework-deployment>" "-DCASE=${case}"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/check.cmake")
        set_tests_properties(bits2banking.framework-deployment.${case} PROPERTIES TIMEOUT 15)
    endforeach()
endif()
