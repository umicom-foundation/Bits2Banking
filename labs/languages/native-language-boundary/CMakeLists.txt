#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/languages/native-language-boundary/CMakeLists.txt
#
# PURPOSE:
#   Test the C boundary independently of optional language compilers.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)
project(NativeLanguageBoundary LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
include(CTest)
add_library(lesson_boundary STATIC boundary.c)
target_include_directories(lesson_boundary PUBLIC .)
add_executable(test_boundary test_boundary.c)
target_link_libraries(test_boundary PRIVATE lesson_boundary)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(lesson_boundary PRIVATE -Wall -Wextra -Wpedantic -Werror)
    target_compile_options(test_boundary PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
add_test(NAME lessons.native_language_boundary.contract COMMAND test_boundary)

add_executable(test_callbacks test_callbacks.c)
target_link_libraries(test_callbacks PRIVATE lesson_boundary)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(test_callbacks PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
add_test(NAME lessons.native_language_boundary.callbacks COMMAND test_callbacks)

# Optional source qualification for the bytecode lessons; no language compiler
# or generated translation is substituted for the real C runtime owner.
set(UMICOM_C_SOURCE "" CACHE PATH "Optional Umicom C checkout for the literal wire exercise")
set(UMICOM_FRAMEWORK_SOURCE "" CACHE PATH "Framework branding resources for the optional native exercise")
if(UMICOM_C_SOURCE)
    if(NOT UMICOM_FRAMEWORK_SOURCE)
        message(FATAL_ERROR "Provide UMICOM_FRAMEWORK_SOURCE for approved exercise branding.")
    endif()
    include("${UMICOM_C_SOURCE}/cmake/UmicomCRuntime.cmake")
    umicom_c_add_runtime(lesson_umicom_c_runtime)
    add_executable(check_umc_fixture check_umc_fixture.c)
    target_link_libraries(check_umc_fixture PRIVATE lesson_umicom_c_runtime)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(check_umc_fixture PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
    endif()
    if(WIN32)
        enable_language(RC)
    endif()
    include("${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
    set(UMICOM_FRAMEWORK_RESOURCE_ROOT "${UMICOM_FRAMEWORK_SOURCE}/resources")
    umicom_apply_application_branding(TARGET check_umc_fixture
        PRODUCT_NAME "Umicom Native Language Bytecode Laboratory"
        INTERNAL_NAME "check_umc_fixture" NO_RUNTIME_DEPLOYMENT)
    add_test(NAME lessons.native_language_boundary.umicom-bytecode COMMAND check_umc_fixture)
    set_tests_properties(lessons.native_language_boundary.umicom-bytecode PROPERTIES TIMEOUT 20 LABELS "lesson;native;bytecode")
endif()

# The optional teaching executable uses the shared brand helper. Requiring its
# existing source avoids inventing an icon or downloading dependencies.
option(UMICOM_BUILD_TAGGED_NUMBER_LAB "Build the branded C tagged-number lesson" OFF)
if(UMICOM_BUILD_TAGGED_NUMBER_LAB)
    if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
        message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE for the tagged-number laboratory branding.")
    endif()
    add_executable(umicom-tagged-number tagged_number.c)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(umicom-tagged-number PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
    endif()
    if(WIN32)
        enable_language(RC)
    endif()
    include("${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
    set(UMICOM_FRAMEWORK_RESOURCE_ROOT "${UMICOM_FRAMEWORK_SOURCE}/resources")
    umicom_apply_application_branding(TARGET umicom-tagged-number
        PRODUCT_NAME "Umicom Tagged Number Laboratory"
        INTERNAL_NAME "umicom-tagged-number" NO_RUNTIME_DEPLOYMENT)
    add_test(NAME lessons.native_language_boundary.tagged-number COMMAND umicom-tagged-number)
    set_tests_properties(lessons.native_language_boundary.tagged-number PROPERTIES TIMEOUT 20 LABELS "lesson;native;union;ownership")
endif()

option(UMICOM_BUILD_CONDITIONAL_SELECTION_LAB "Build the branded C evaluation-order lesson" OFF)
if(UMICOM_BUILD_CONDITIONAL_SELECTION_LAB)
    if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
        message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE for the conditional-selection laboratory branding.")
    endif()
    add_executable(umicom-conditional-selection conditional_selection.c)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(umicom-conditional-selection PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
    endif()
    if(WIN32)
        enable_language(RC)
    endif()
    include("${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
    set(UMICOM_FRAMEWORK_RESOURCE_ROOT "${UMICOM_FRAMEWORK_SOURCE}/resources")
    umicom_apply_application_branding(TARGET umicom-conditional-selection
        PRODUCT_NAME "Umicom Conditional Selection Laboratory"
        INTERNAL_NAME "umicom-conditional-selection" NO_RUNTIME_DEPLOYMENT)
    add_test(NAME lessons.native_language_boundary.conditional-selection COMMAND umicom-conditional-selection)
    set_tests_properties(lessons.native_language_boundary.conditional-selection PROPERTIES TIMEOUT 20 LABELS "lesson;native;expressions;evaluation")
endif()

option(UMICOM_BUILD_LOCAL_STORAGE_LAB "Build the branded C storage-lifetime lesson" OFF)
if(UMICOM_BUILD_LOCAL_STORAGE_LAB)
    if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
        message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE for the local-storage laboratory branding.")
    endif()
    add_executable(umicom-local-storage local_storage.c)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(umicom-local-storage PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
    endif()
    if(WIN32)
        enable_language(RC)
    endif()
    include("${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
    set(UMICOM_FRAMEWORK_RESOURCE_ROOT "${UMICOM_FRAMEWORK_SOURCE}/resources")
    umicom_apply_application_branding(TARGET umicom-local-storage
        PRODUCT_NAME "Umicom Local Storage Laboratory"
        INTERNAL_NAME "umicom-local-storage" NO_RUNTIME_DEPLOYMENT)
    foreach(_case automatic static owners)
        add_test(NAME lessons.native_language_boundary.local-storage.${_case}
            COMMAND umicom-local-storage ${_case})
        set_tests_properties(lessons.native_language_boundary.local-storage.${_case} PROPERTIES
            TIMEOUT 20 LABELS "lesson;native;storage;ownership")
    endforeach()
endif()

option(UMICOM_BUILD_BOOLEAN_WIRE_LAB "Build the branded C Boolean wire lesson" OFF)
if(UMICOM_BUILD_BOOLEAN_WIRE_LAB)
    if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
        message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE for the Boolean wire laboratory branding.")
    endif()
    add_executable(umicom-boolean-wire boolean_wire.c)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(umicom-boolean-wire PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
    endif()
    if(WIN32)
        enable_language(RC)
    endif()
    include("${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
    set(UMICOM_FRAMEWORK_RESOURCE_ROOT "${UMICOM_FRAMEWORK_SOURCE}/resources")
    umicom_apply_application_branding(TARGET umicom-boolean-wire
        PRODUCT_NAME "Umicom Boolean Wire Laboratory"
        INTERNAL_NAME "umicom-boolean-wire" NO_RUNTIME_DEPLOYMENT)
    add_test(NAME lessons.native_language_boundary.boolean-wire COMMAND umicom-boolean-wire)
    set_tests_properties(lessons.native_language_boundary.boolean-wire PROPERTIES
        TIMEOUT 20 LABELS "lesson;native;boolean;serialization")
endif()
