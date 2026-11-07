#-----------------------------------------------------------------------------
# Bits2Banking
# File: labs/native/boot-handoff/CMakeLists.txt
#
# PURPOSE:
#   Build the lesson against the real Kernel boot reader rather than a second parser.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.24)
project(UmicomBootHandoffLab LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(UMICOM_KERNEL_SOURCE "" CACHE PATH "Path to the Umicom Kernel source checkout")
if(NOT EXISTS "${UMICOM_KERNEL_SOURCE}/kernel/boot_handoff.c")
    message(FATAL_ERROR "Set UMICOM_KERNEL_SOURCE to the Kernel checkout containing kernel/boot_handoff.c")
endif()
add_executable(boot-handoff main.c "${UMICOM_KERNEL_SOURCE}/kernel/boot_handoff.c" "${UMICOM_KERNEL_SOURCE}/kernel/address.c")
target_include_directories(boot-handoff PRIVATE "${UMICOM_KERNEL_SOURCE}/include")
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(boot-handoff PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
include(CTest)
if(BUILD_TESTING)
    add_test(NAME learning.kernel.boot-handoff COMMAND boot-handoff)
endif()
