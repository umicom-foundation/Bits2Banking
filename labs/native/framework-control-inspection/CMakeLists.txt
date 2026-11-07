#-----------------------------------------------------------------------------
# Bits2Banking
# File: labs/native/framework-control-inspection/CMakeLists.txt
#
# PURPOSE:
#   Build the control-inspection lesson against an installed Framework GTK4 SDK.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)
project(Bits2BankingControlInspection LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4>=4.10)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS ui_gtk4)
add_executable(btb-control-inspection main.c)
target_link_libraries(btb-control-inspection PRIVATE Umicom::ui_gtk4 PkgConfig::GTK4)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(btb-control-inspection PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
