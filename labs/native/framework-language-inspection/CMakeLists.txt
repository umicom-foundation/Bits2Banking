#-----------------------------------------------------------------------------
# Bits2Banking
# File: CMakeLists.txt
#
# PURPOSE:
#   Build a language-service inspection lab against an installed Framework SDK.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25)
project(LanguageInspection LANGUAGES C)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS document editor)
add_executable(language-inspection main.c)
set_target_properties(language-inspection PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
target_link_libraries(language-inspection PRIVATE Umicom::document Umicom::editor)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(language-inspection PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
include(CTest)
if(BUILD_TESTING)
    add_test(NAME language-inspection.hardware COMMAND language-inspection cpu.vhd)
    set_tests_properties(language-inspection.hardware PROPERTIES PASS_REGULAR_EXPRESSION "cpu.vhd: vhdl" TIMEOUT 10)
    add_test(NAME language-inspection.unknown COMMAND language-inspection notes.unknown)
    set_tests_properties(language-inspection.unknown PROPERTIES PASS_REGULAR_EXPRESSION "notes.unknown: plain" TIMEOUT 10)
endif()
