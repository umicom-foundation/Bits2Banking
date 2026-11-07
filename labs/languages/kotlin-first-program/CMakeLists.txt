# -----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/languages/kotlin-first-program/CMakeLists.txt
#
# PURPOSE:
#   Compile the Kotlin exercises and register separate entry points.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
# -----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.24)
project(BtbKotlinInput LANGUAGES NONE)
include(CTest)
find_package(Java REQUIRED COMPONENTS Runtime)
find_program(KOTLINC_EXECUTABLE NAMES kotlinc kotlinc.bat REQUIRED)
set(_jar "${CMAKE_CURRENT_BINARY_DIR}/progress-input.jar")
add_custom_command(OUTPUT "${_jar}"
    COMMAND "${KOTLINC_EXECUTABLE}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Progress.kt"
        "${CMAKE_CURRENT_SOURCE_DIR}/Input.kt"
        "${CMAKE_CURRENT_SOURCE_DIR}/InputChecks.kt"
        -include-runtime -d "${_jar}"
    DEPENDS Progress.kt Input.kt InputChecks.kt VERBATIM)
add_custom_target(btb-kotlin-input ALL DEPENDS "${_jar}")
if(BUILD_TESTING)
    add_test(NAME bits2banking.kotlin.progress
        COMMAND "${Java_JAVA_EXECUTABLE}" -cp "${_jar}" ProgressKt)
    add_test(NAME bits2banking.kotlin.arguments
        COMMAND "${Java_JAVA_EXECUTABLE}" -cp "${_jar}" InputChecksKt)
    add_test(NAME bits2banking.kotlin.cli
        COMMAND "${Java_JAVA_EXECUTABLE}" -cp "${_jar}" InputKt 4 1)
    set_tests_properties(bits2banking.kotlin.cli PROPERTIES
        PASS_REGULAR_EXPRESSION "Remaining lessons: 3")
    add_test(NAME bits2banking.kotlin.invalid_cli
        COMMAND "${Java_JAVA_EXECUTABLE}" -cp "${_jar}" InputKt 4 invalid)
    set_tests_properties(bits2banking.kotlin.invalid_cli PROPERTIES WILL_FAIL TRUE)
    set_tests_properties(bits2banking.kotlin.progress bits2banking.kotlin.arguments
        bits2banking.kotlin.cli bits2banking.kotlin.invalid_cli PROPERTIES TIMEOUT 20)
endif()
