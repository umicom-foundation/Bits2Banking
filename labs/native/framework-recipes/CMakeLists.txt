#-----------------------------------------------------------------------------
# Bits2Banking
# File: labs/native/framework-recipes/CMakeLists.txt
#
# PURPOSE:
#   Build the installed Framework recipe consumer and register four distinct ownership scenarios.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25)
project(Bits2BankingFrameworkRecipes LANGUAGES C)
find_package(UmicomFramework CONFIG REQUIRED)
include(CTest)
add_executable(btb-framework-recipes main.c)
target_link_libraries(btb-framework-recipes PRIVATE Umicom::developer Umicom::build)
set_target_properties(btb-framework-recipes PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
if(MSVC)
    target_compile_options(btb-framework-recipes PRIVATE /W4)
else()
    target_compile_options(btb-framework-recipes PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(BUILD_TESTING)
    foreach(case inspect owned identity refuse)
        add_test(NAME bits2banking.framework-recipes.${case} COMMAND "${CMAKE_COMMAND}" "-DTOOL=$<TARGET_FILE:btb-framework-recipes>" "-DCASE=${case}" "-DFIXTURES=${CMAKE_CURRENT_SOURCE_DIR}" -P "${CMAKE_CURRENT_SOURCE_DIR}/check.cmake")
        set_tests_properties(bits2banking.framework-recipes.${case} PROPERTIES TIMEOUT 30)
    endforeach()
endif()
