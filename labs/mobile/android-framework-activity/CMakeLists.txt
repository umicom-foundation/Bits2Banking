# -----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/mobile/android-framework-activity/CMakeLists.txt
#
# PURPOSE:
#   Compile the existing C lesson model for the Android NDK target.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
# -----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(BtbAndroidActivity LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
if(NOT ANDROID)
    message(FATAL_ERROR "Use this adapter through Android Studio and its NDK toolchain")
endif()
set(UMICOM_FRAMEWORK_INCLUDE_DIR "" CACHE PATH "Framework source include directory")
if(NOT EXISTS "${UMICOM_FRAMEWORK_INCLUDE_DIR}/umicom/base/status.h")
    message(FATAL_ERROR "Set UMICOM_FRAMEWORK_INCLUDE_DIR to the Framework include directory")
endif()
# This first boundary lab uses Framework status declarations only. It does not
# link desktop SDK binaries or establish support for every Framework service.
add_library(btb_activity SHARED activity_jni.c
    ../../native/activity-adapters/bridge.c ../../native/framework-activity/activity.c)
target_include_directories(btb_activity PRIVATE "${UMICOM_FRAMEWORK_INCLUDE_DIR}")
target_compile_options(btb_activity PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)

