# -----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/microdevices/pico-activity/CMakeLists.txt
#
# PURPOSE:
#   Build the shared C activity example for a non-wireless Raspberry Pi Pico.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
# -----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.24)
# Import the board toolchain before project() selects a host compiler.
set(PICO_SDK_PATH "" CACHE PATH "Directory containing the Pico SDK")
set(UMICOM_FRAMEWORK_ROOT "" CACHE PATH "Framework source checkout")
if(NOT EXISTS "${PICO_SDK_PATH}/external/pico_sdk_import.cmake")
    message(FATAL_ERROR "Set PICO_SDK_PATH to an existing Pico SDK checkout")
endif()
if(NOT EXISTS "${UMICOM_FRAMEWORK_ROOT}/include/umicom/base/status.h")
    message(FATAL_ERROR "Set UMICOM_FRAMEWORK_ROOT to the Framework source checkout")
endif()
if(NOT DEFINED PICO_BOARD)
    set(PICO_BOARD pico CACHE STRING "Board for this lesson")
endif()
if(NOT PICO_BOARD STREQUAL "pico")
    message(FATAL_ERROR "This wiring lesson targets the non-wireless RP2040 Pico")
endif()
include("${PICO_SDK_PATH}/external/pico_sdk_import.cmake")
project(BtbPicoActivity LANGUAGES C CXX ASM)
pico_sdk_init()
add_executable(btb-pico-activity main.c
    ../../native/activity-adapters/button.c
    ../../native/framework-activity/activity.c)
# The SDK can contain C++ support; the authored application/model are C23.
set_target_properties(btb-pico-activity PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED ON C_EXTENSIONS OFF)
target_include_directories(btb-pico-activity PRIVATE "${UMICOM_FRAMEWORK_ROOT}/include")
target_link_libraries(btb-pico-activity PRIVATE pico_stdlib)
pico_add_extra_outputs(btb-pico-activity)

