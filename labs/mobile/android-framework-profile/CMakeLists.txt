#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/mobile/android-framework-profile/CMakeLists.txt
#
# PURPOSE:
#   Build the mobile JNI laboratory from the existing portable Framework sources.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.26)
project(BtbAndroidProfile LANGUAGES C)
if(NOT ANDROID)
    message(FATAL_ERROR "Build this library through Gradle and the Android NDK")
endif()
set(BTB_FRAMEWORK_SOURCE "" CACHE PATH "Absolute primary Framework source root")
if(NOT IS_ABSOLUTE "${BTB_FRAMEWORK_SOURCE}" OR
   NOT EXISTS "${BTB_FRAMEWORK_SOURCE}/cmake/UmicomAndroidProfileName.cmake")
    message(FATAL_ERROR "Set BTB_FRAMEWORK_SOURCE to the Framework root containing the Android profile adapter")
endif()
include("${BTB_FRAMEWORK_SOURCE}/cmake/UmicomAndroidProfileName.cmake")
add_library(btb_profile SHARED profile_jni.c)
set_target_properties(btb_profile PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
target_link_libraries(btb_profile PRIVATE Umicom::android_profile_name)
target_compile_options(btb_profile PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
# Device tests belong to Android's instrumented runner. No host CTest entry
# pretends to execute this target's shared library.
