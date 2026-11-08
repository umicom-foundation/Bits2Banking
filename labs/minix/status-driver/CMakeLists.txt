# Umicom Bits2Banking
# File: CMakeLists.txt
# PURPOSE: Check portable range logic without claiming MINIX driver execution.
# AUTHOR AND ORGANISATION: Sammy Hegab / Umicom Foundation
# LICENCE: MIT
cmake_minimum_required(VERSION 3.24)
project(MinixReadWindowModel LANGUAGES C)
add_executable(read-window-tests read_window.c read_window_tests.c)
set_target_properties(read-window-tests PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
include(CTest)
if(BUILD_TESTING)
    add_test(NAME minix.learning.read-window COMMAND read-window-tests)
endif()
