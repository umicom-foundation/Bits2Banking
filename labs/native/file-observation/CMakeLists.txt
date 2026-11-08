#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/file-observation/CMakeLists.txt
#
# PURPOSE:
#   Build the selected-file evidence lab against an installed Framework SDK.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25)
project(FileObservationLab LANGUAGES C)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS toolchain platform)
add_executable(file-observation main.c)
set_target_properties(file-observation PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
target_link_libraries(file-observation PRIVATE Umicom::toolchain Umicom::platform)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(file-observation PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
include(CTest)
if(BUILD_TESTING)
    foreach(_case ascii empty unicode-path missing relative)
        add_test(NAME "file-observation.${_case}" COMMAND "${CMAKE_COMMAND}"
            "-DTOOL=$<TARGET_FILE:file-observation>" "-DCASE=${_case}"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/check_output.cmake")
        set_tests_properties("file-observation.${_case}" PROPERTIES TIMEOUT 30)
    endforeach()
endif()
